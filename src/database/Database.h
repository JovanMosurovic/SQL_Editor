
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

    void selectFromTable(const string& tableName, const string& tableAlias, const vector<string>& columnNames, const vector<shared_ptr<IFilter>>& filters);

    shared_ptr<Table> innerJoinTables(const string &table1Name, const string &table2Name, const string &column1, const string &column2) {
        Table &table1 = getTable(table1Name);
        Table &table2 = getTable(table2Name);

//        if (!table1.hasColumn(column1) || !table2.hasColumn(column2)) {
//            throw ColumnDoesNotExistException("Column does not exist in one of the tables.");
//        }

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

    void importDatabase(const Format& format, const string& filePath);
    void exportDatabase(const Format& format, const string& filePath);

    void printDatabase();

    //<editor-fold desc="Getters">

    const string &getName() const;

    Table& getTable(const string& tableName);

    //</editor-fold>

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DATABASE_H
