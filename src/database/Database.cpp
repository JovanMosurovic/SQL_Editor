
#include "Database.h"

Database::Database(const string& name) : name(name) {}

void Database::addTable(const Table &table) {
    if (tables.find(table.getName()) != tables.end()) {
        throw TableAlreadyExistsException(table.getName());
    }
    tables.emplace(table.getName(), table);
}

void Database::createTable(const string &tableName, const vector<Column> &columns) {
    regex tableName_pattern("^[A-Za-z]+$");
    if (!(regex_match(tableName, tableName_pattern))) {
        throw InvalidTableNameException(tableName);
    }
    auto it = tables.find(tableName);
    if (it != tables.end()) {
        throw TableAlreadyExistsException(tableName);
    }
    tables.emplace(tableName, Table(tableName, columns));
}

void Database::dropTable(const string &tableName) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    tables.erase(it);
}

void Database::addRowToTable(const string &tableName, const vector<string> &rowData) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    if (rowData.size() != it->second.getColumns().size()) {
        throw InvalidDataForAddRowException(rowData.size(), it->second.getColumns().size());
    }
    it->second.addRow(rowData);
}

void Database::insertIntoTable(const string &tableName, const vector<string> &columnNames, const vector<string> &rowData) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    if (columnNames.size() != rowData.size()) {
        throw InvalidDataForAddRowException(rowData.size(), columnNames.size());
    }

    vector<string> actualColumnOrder;
    for (const auto &column : it->second.getColumns()) {
        actualColumnOrder.push_back(column.getName());
    }

    vector<string> reorderedData(actualColumnOrder.size());
    for(size_t i = 0; i< columnNames.size(); i++) {
        auto pos = find(actualColumnOrder.begin(), actualColumnOrder.end(), columnNames[i]);
        if(pos != actualColumnOrder.end()) {
            int index = distance(actualColumnOrder.begin(), pos);
            reorderedData[index] = rowData[i];
        } else {
            throw ColumnDoesNotExistException(columnNames[i]);
        }
    }
    it->second.addRow(reorderedData);
}

void Database::updateRowInTable(const string &tableName, const long long rowIndex, const vector<string> &rowData) {
    auto it = tables.find(tableName);
    if(it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    if(rowIndex >= it->second.getRows().size()) {
        throw RowOutOfBoundsException(rowIndex, it->second.getRows().size());
    }
    if(rowData.size() != it->second.getColumns().size()) {
        throw InvalidDataForUpdateException(rowData.size(), it->second.getColumns().size());
    }
    it->second.updateRow(rowIndex, rowData);
}

void Database::removeRowFromTable(const string &tableName, const long long rowIndex) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    if (rowIndex > it->second.getRows().size()) {
        throw RowOutOfBoundsException(rowIndex, it->second.getRows().size());
    }
    it->second.removeRow(rowIndex);
}

void Database::clearTable(const string &tableName) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    it->second.clearRows();
}

void Database::selectFromTable(const string &tableName, const string &tableAlias, const vector<string> &columnNames) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    Table &table = it->second;

    for(const auto &columnName : columnNames) {
        if(!table.hasColumn(columnName)) {
            throw ColumnDoesNotExistException(columnName);
        }
    }

    vector<Column> selectedColumns;
    for(const auto &columnName : columnNames) {
        int columnIndex = table.getColumnIndex(columnName);
        selectedColumns.push_back(table.getColumns()[columnIndex]);
    }
    Table selectedTable(tableAlias, selectedColumns);

    for (const auto &row : table.getRows()) {
        vector<string> selectedRow;
        selectedRow.reserve(columnNames.size());
        for (const auto &columnName : columnNames) {
            selectedRow.push_back(row.getData()[table.getColumnIndex(columnName)]);
        }
        selectedTable.addRow(selectedRow);
    }

    selectedTable.printTable();
}

void Database::importDatabase(const Format& format, const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw FileNotOpenedException(filePath);
    }

    string line;
    unique_ptr<Table> currentTable = nullptr;
    bool isTableInitialized = false;
    bool isSQLFormat = filePath.substr(filePath.find_last_of(".") + 1) == "sql";
    bool expectingColumnHeaders = false;  // Only used for custom format

    auto trim = [](string& s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) { return !isspace(ch); }));
        s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
    };

    while (getline(file, line)) {
        trim(line);
        if (line.empty()) continue;

        if (isSQLFormat) {
            if (line.substr(0, 13) == "CREATE TABLE ") {
                if (currentTable) {
                    tables.emplace(currentTable->getName(), std::move(*currentTable));
                }
                Table newTable = format.parseTable(line);
                currentTable = make_unique<Table>(newTable.getName(), newTable.getColumns());
                isTableInitialized = true;
            } else if (line.substr(0, 11) == "INSERT INTO" && isTableInitialized) {
                vector<string> rowData = format.parseRow(line);
                currentTable->addRow(rowData);
            }
        } else {  // Handling custom format
            if (line.substr(0, 6) == "Table:") {
                if (currentTable) {
                    tables.emplace(currentTable->getName(), std::move(*currentTable));
                }
                string tableName = line.substr(6).substr(0, line.find('(') - 6);
                trim(tableName);
                currentTable = make_unique<Table>(tableName, vector<Column>());
                expectingColumnHeaders = true;
            } else if (expectingColumnHeaders) {
                vector<string> columnNames = format.parseRow(line);  // Parses column names
                vector<Column> columns;
                columns.reserve(columnNames.size());
                for (const auto& columnName : columnNames) {
                    columns.emplace_back(columnName);  // Assuming Column constructor takes a columnName
                }
                currentTable = make_unique<Table>(currentTable->getName(), columns);
                expectingColumnHeaders = false;
                isTableInitialized = true;
            } else if (isTableInitialized) {
                vector<string> rowData = format.parseRow(line);
                currentTable->addRow(rowData);
            }
        }
    }

    if (currentTable) {
        tables.emplace(currentTable->getName(), std::move(*currentTable));
    }

    file.close();
}


void Database::exportDatabase(const Format& format, const string& filePath) {
    ofstream file(filePath);
    if (!file.is_open()) {
        throw FileNotOpenedException(filePath);
    }

    if (const auto* customFormat = dynamic_cast<const CustomFormat*>(&format)) {
        file << customFormat->formatDatabaseName(name) << endl;
    }

    for (const auto& pair : tables) {
        const Table& table = pair.second;
        file << format.formatTable(table) << endl;
        for (const auto& row : table.getRows()) {
            file << format.formatRow(table, row) << endl;
        }
    }
    file.close();
}

void Database::printDatabase() {
    cout << endl << "Database: " << name << endl;
    cout << "Tables: " << endl;
    if(tables.empty()) {
        cout << " - No tables in database" << endl;
    }
    for(auto it = tables.begin(); it != tables.end(); ++it) {
        cout << " - " << it->first << endl;
        it->second.printTable();
        if (next(it) != tables.end()) {
            cout << endl;
        }
    }
}

const string &Database::getName() const {
    return name;
}

Table &Database::getTable(const string &tableName) {
    auto it = tables.find(tableName);
    if (it == tables.end()) {
        throw TableDoesNotExistException(tableName);
    }
    return it->second;
}
