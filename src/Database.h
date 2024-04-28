
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H
#define ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H

#include <unordered_map>
#include <regex>
#include "table/Table.h"

class Database {
    string name;
    unordered_map<string, Table> tables;

public:
    Database(string name); //bez const?

    void addTable(const Table& table) { //da li treba dodati proveru u samu Table klasu za ime od velikih i malih slova
        if(tables.find(table.getName()) != tables.end()) {
            //todo throw "Table +tableName already exists in database"
            cout << "Usao u if" << endl;
            return;
        }
        tables.emplace(table.getName(), table);
    }

    void createTable(const string& tableName, const vector<Column>& columns) {
        regex tableName_pattern("^[A-Za-z]+$");
        if(!(regex_match(tableName, tableName_pattern))) {
            //todo throw "Table name is not typed in corrected format.\n
            // Format: Only English letters are allowed without spaces or special characters."
            cout << "Usao u if" << endl;
            return;
        }

        auto it = tables.find(tableName);
        if(it != tables.end()) {
            //todo throw "Table +tableName already exists in database"
            cout << "Usao u if" << endl;
            return;
        }
        tables.emplace(tableName, Table(tableName, columns));
    }

    void dropTable(const string& tableName) {
        auto it = tables.find(tableName);
        if(it == tables.end()) {
            //todo throw "Table +tableName does not exist in database"
            cout << "Usao u if" << endl;
            return;
        }
        tables.erase(it);
    }

    void printDatabase() {
        cout << "Database: " << name << endl;
        cout << "Tables: " << endl;
        for(const auto& table : tables) {
            cout << " - " << table.first << endl;
            table.second.printTable();
            cout << endl;
        }
    }

    //<editor-fold desc="Getters">

    const string &getName() const;

    //</editor-fold>

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H
