
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H
#define ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H

#include <unordered_map>
#include <fstream>
#include "table/Table.h"
#include "../exceptions/DatabaseExceptions.h"
#include "../export/CustomFormat.h"
#include "../export/SQLFormat.h"
#include "../sql/filter/EqualityFilter.h"
#include "../sql/filter/InequalityFilter.h"

class Database {
    string name;
    unordered_map<string, Table> tables;

public:
    Database(const string& name);

    void addTable(const Table& table);

    void createTable(const string& tableName, const vector<Column>& columns);

    void dropTable(const string& tableName);

    void addRowToTable(const string& tableName, const vector<string>& rowData);

    void insertIntoTable(const string& tableName, const vector<string>& columnNames, const vector<string>& rowData);

    void updateRowInTable(const string& tableName, long long rowIndex, const vector<string>& rowData);

    void removeRowFromTable(const string& tableName, long long rowIndex);

    void clearTable(const string& tableName);

    void selectFromTable(const string &tableName, const string &tableAlias, const vector<string> &columnNames,
                         const vector<shared_ptr<IFilter>> &filters, const string &joinTableName = "",
                         const string &joinColumn = "", const string &joinColumn2 = "");

    shared_ptr<Table> innerJoinTables(const string &table1Name, const string &table2Name, const string &column1, const string &column2);

    void importDatabase(const Format& format, const string& filePath);
    void exportDatabase(const Format& format, const string& filePath);

    void printDatabase();

    void updateTableInFile(const string& tableName);

    //<editor-fold desc="Getters">

    const string &getName() const;

    Table& getTable(const string& tableName);

    //</editor-fold>


};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H
