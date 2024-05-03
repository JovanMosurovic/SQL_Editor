
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H
#define ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H

#include <utility>
#include <iomanip>
#include <sstream>
#include <regex>
#include "Column.h"
#include "Row.h"
#include "../../menu/Colors.h"
#include "../../menu/ConsoleUtils.h"
#include "../../exceptions/TableExceptions.h"

using namespace std;

class Table {

    string name;
    vector<Column> columns;
    vector<Row> rows;

public:
    Table(const string& name, const vector<Column> &columns);

    void addRow(const vector<string>& rowData);

    void removeRow(long long rowIndex);

    void updateRow(long long rowIndex, const vector<string>& newData);

    void printTable() const;


    //<editor-fold desc="Getters">

    const vector<Column> &getColumns() const;

    const string &getName() const;

    const vector<Row> &getRows() const;

    //</editor-fold>

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_TABLE_H
