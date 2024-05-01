
#include "Database.h"

Database::Database(string name) : name(std::move(name)) {}

void Database::addTable(const Table &table) {
    try {
        if (tables.find(table.getName()) != tables.end()) {
            throw TableAlreadyExistsException(table.getName());
        }
        tables.emplace(table.getName(), table);
    } catch (const TableAlreadyExistsException& e) {
        cout << e.what() << endl;
    } catch(const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }

}

void Database::createTable(const string &tableName, const vector<Column> &columns) {
    try {
        regex tableName_pattern("^[A-Za-z]+$");
        if (!(regex_match(tableName, tableName_pattern))) {
            throw InvalidTableNameException(tableName);
        }
        auto it = tables.find(tableName);
        if (it != tables.end()) {
            throw TableAlreadyExistsException(tableName);
        }
        tables.emplace(tableName, Table(tableName, columns));
    } catch (const InvalidTableNameException& e) {
        cout << e.what() << endl;
    } catch (const TableAlreadyExistsException& e) {
        cout << e.what() << endl;
    } catch(const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Database::dropTable(const string &tableName) {
    try {
        auto it = tables.find(tableName);
        if (it == tables.end()) {
            throw TableDoesNotExistException(tableName);
        }
        tables.erase(it);
    } catch(const TableDoesNotExistException& e) {
        cout << e.what() << endl;
    } catch(const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Database::addRowToTable(const string &tableName, const vector<string> &rowData) {
    try {
        auto it = tables.find(tableName);
        if (it == tables.end()) {
            throw TableDoesNotExistException(tableName);
        }
        if (rowData.size() != it->second.getColumns().size()) {
            throw InvalidDataForAddRowException(rowData.size(), it->second.getColumns().size());
        }
        it->second.addRow(rowData);
    } catch (const TableDoesNotExistException& e) {
        cout << e.what() << endl;
    } catch (const InvalidDataForAddRowException& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Database::updateRowInTable(const string &tableName, const long long rowIndex, const vector<string> &rowData) {
    try {
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
    } catch (const TableDoesNotExistException& e) {
        cout << e.what() << endl;
    } catch (const RowOutOfBoundsException& e) {
        cout << e.what() << endl;
    } catch (const InvalidDataForUpdateException& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Database::removeRowFromTable(const string &tableName, const long long rowIndex) {
    try {
        auto it = tables.find(tableName);
        if (it == tables.end()) {
            throw TableDoesNotExistException(tableName);
        }
        if (rowIndex > it->second.getRows().size()) {
            throw RowOutOfBoundsException(rowIndex, it->second.getRows().size());
        }
        it->second.removeRow(rowIndex);
    } catch (const TableDoesNotExistException& e) {
        cout << e.what() << endl;
    } catch (const RowOutOfBoundsException& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Database::printDatabase() { // helper function, not needed in the project
    cout << "Database: " << name << endl;
    cout << "Tables: " << endl;
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

