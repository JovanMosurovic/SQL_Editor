
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H
#define ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H

#include <iostream>
#include "Column.h"
#include "Row.h"

using namespace std;

class Table {

    string name;
    vector<Column> columns;
    vector<Row> rows;

public:
    Table(string name, const vector<Column> &columns);

    void addRow(const vector<string>& rowData);

    void removeRow(size_t rowIndex);

    void updateRow(size_t rowIndex, const vector<string>& newData);

    void printTable() const;



    //<editor-fold desc="Getters">

    const vector<Column> &getColumns() const;

    const string &getName() const;

    const vector<Row> &getRows() const;

    //</editor-fold>

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H
