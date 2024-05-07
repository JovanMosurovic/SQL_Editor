
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

void Database::exportDatabase(const Format& format, const string& filePath) {
    ofstream file(filePath);
    if (!file.is_open()) {
        throw FileNotOpenedException(filePath);
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

