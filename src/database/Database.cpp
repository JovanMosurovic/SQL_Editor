
#include "Database.h"

Database::Database(const string& name) : name(name) {}

void Database::addTable(const Table &table) {
    if (tables.find(table.getName()) != tables.end()) {
        throw TableAlreadyExistsException(table.getName());
    }
    tables.emplace(table.getName(), table);
}

void Database::createTable(const string &tableName, const vector<Column> &columns) {
    regex tableName_pattern("^[A-Za-z_]+$");
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
    Table &table = getTable(tableName);
    if(rowData.size() != table.getColumns().size()) {
        throw InvalidDataForAddRowException(rowData.size(), table.getColumns().size());
    }
    table.addRow(rowData);
}

void Database::insertIntoTable(const string &tableName, const vector<string> &columnNames, const vector<string> &rowData) {
    Table &table = getTable(tableName);
    if(columnNames.size() != rowData.size()) {
        throw InvalidDataForAddRowException(rowData.size(), columnNames.size());
    }

    vector<string> actualColumnOrder;
    for (const auto &column : table.getColumns()) {
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
    table.addRow(reorderedData);
}

void Database::updateRowInTable(const string &tableName, const long long rowIndex, const vector<string> &rowData) {
    Table &table = getTable(tableName);
    if(rowIndex >= table.getRows().size()) {
        throw RowOutOfBoundsException(rowIndex, table.getRows().size());
    }
    if(rowData.size() != table.getColumns().size()) {
        throw InvalidDataForUpdateException(rowData.size(), table.getColumns().size());
    }
    table.updateRow(rowIndex, rowData);

    updateTableInFile(tableName);
}

void Database::removeRowFromTable(const string &tableName, const long long rowIndex) {
    Table &table = getTable(tableName);
    if(rowIndex >= table.getRows().size()) {
        throw RowOutOfBoundsException(rowIndex, table.getRows().size());
    }
    table.removeRow(rowIndex);
}

void Database::clearTable(const string &tableName) {
    Table &table = getTable(tableName);
    table.clearRows();
}

void Database::selectFromTable(const string &tableName, const string &tableAlias,
                               const vector<string> &columnNames,
                               const vector<shared_ptr<IFilter>>& filters,
                               const string &joinTableName,
                               const string &joinColumn,
                               const string &joinColumn2) {
    Table &table = getTable(tableName);
    Table *joinTable = nullptr;
    bool isJoin = !joinTableName.empty();

    if (isJoin) {
        joinTable = &getTable(joinTableName);
    }

    vector<Column> selectedColumns;
    vector<string> actualColumnNames = columnNames;

    if (columnNames.size() == 1 && columnNames[0] == "*") {
        actualColumnNames.clear();
        for (const auto &column : table.getColumns()) {
            actualColumnNames.push_back(column.getName());
        }
        if (isJoin) {
            for (const auto &column : joinTable->getColumns()) {
                actualColumnNames.push_back(column.getName());
            }
        }
    }

    for (const auto &columnName : actualColumnNames) {
        if (table.hasColumn(columnName)) {
            selectedColumns.push_back(table.getColumns()[table.getColumnIndex(columnName)]);
        } else if (isJoin && joinTable->hasColumn(columnName)) {
            selectedColumns.push_back(joinTable->getColumns()[joinTable->getColumnIndex(columnName)]);
        } else {
            throw ColumnDoesNotExistException(columnName);
        }
    }

    Table resultTable(tableAlias, selectedColumns);

    for (const auto &row1 : table.getRows()) {
        if (isJoin) {
            for (const auto &row2 : joinTable->getRows()) {
                if (row1.getColumnValue(joinColumn) == row2.getColumnValue(joinColumn2)) {
                    vector<string> combinedRowData;
                    bool shouldAddRow = true;

                    for (const auto &columnName : actualColumnNames) {
                        if (table.hasColumn(columnName)) {
                            combinedRowData.push_back(row1.getColumnValue(columnName));
                        } else {
                            combinedRowData.push_back(row2.getColumnValue(columnName));
                        }
                    }

                    for (const auto &filter : filters) {
                        if (filter && !filter->applyFilter(Row(actualColumnNames, combinedRowData))) {
                            shouldAddRow = false;
                            break;
                        }
                    }

                    if (shouldAddRow) {
                        resultTable.addRow(combinedRowData);
                    }
                }
            }
        } else {
            bool shouldAddRow = true;
            for (const auto &filter : filters) {
                if (filter && !filter->applyFilter(row1)) {
                    shouldAddRow = false;
                    break;
                }
            }
            if (shouldAddRow) {
                vector<string> selectedRow;
                selectedRow.reserve(actualColumnNames.size());
                for (const auto &columnName : actualColumnNames) {
                    selectedRow.push_back(row1.getColumnValue(columnName));
                }
                resultTable.addRow(selectedRow);
            }
        }
    }

    if (resultTable.getRows().empty()) {
        cout << "\xC4> Query did not return any results." << endl;
    } else {
        resultTable.printTable();
    }
}

shared_ptr<Table> Database::innerJoinTables(const string &table1Name, const string &table2Name, const string &column1,
                                            const string &column2) {
    Table &table1 = getTable(table1Name);
    Table &table2 = getTable(table2Name);

    if (!table1.hasColumn(column1) || !table2.hasColumn(column2)) {
        throw ColumnDoesNotExistException("Column does not exist in one of the tables.");
    }

    vector<Column> newColumns = table1.getColumns();
    newColumns.insert(newColumns.end(), table2.getColumns().begin(), table2.getColumns().end());

    Table resultTable("Result", newColumns);

    for (const auto &row1 : table1.getRows()) {
        for (const auto &row2 : table2.getRows()) {
            if (row1.getColumnValue(column1) == row2.getColumnValue(column2)) {
                vector<string> rowData = row1.getData();
                rowData.insert(rowData.end(), row2.getData().begin(), row2.getData().end());
                resultTable.addRow(rowData);
            }
        }
    }

    return make_shared<Table>(resultTable);
}

void Database::importDatabase(const Format& format, const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw FileNotOpenedException(filePath);
    }

    string line;
    unique_ptr<Table> currentTable = nullptr;
    bool isTableInitialized = false;
    bool isSQLFormat = filePath.substr(filePath.find_last_of('.') + 1) == "sql";
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
        } else {  // Custom format
            if (line.substr(0, 6) == "Table:") {
                if (currentTable) {
                    tables.emplace(currentTable->getName(), std::move(*currentTable));
                }
                string tableName = line.substr(6).substr(0, line.find('(') - 6);
                trim(tableName);
                currentTable = make_unique<Table>(tableName, vector<Column>());
                expectingColumnHeaders = true;
            } else if (expectingColumnHeaders) {
                vector<string> columnNames = format.parseRow(line);
                vector<Column> columns;
                columns.reserve(columnNames.size());
                for (const auto& columnName : columnNames) {
                    columns.emplace_back(columnName);
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

void Database::updateTableInFile(const string &tableName) { // for native format
    ifstream inFile("output.txt");
    ofstream outFile("output_temp.txt");
    string line;
    bool isUpdatingTable = false;

    while (getline(inFile, line)) {
        if (line == "\t" + tableName) {
            isUpdatingTable = true;
            outFile << line << endl;
            auto it = tables.find(tableName);
            if (it != tables.end()) {
                it->second.printTableInFile(outFile);
            }
        } else if (line == "#" && isUpdatingTable) {
            isUpdatingTable = false;
            outFile << line << endl;
        } else if (!isUpdatingTable) {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("output.txt");
    rename("output_temp.txt", "output.txt");
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
