
#include "Table.h"

#include <utility>
#include <iomanip>
#include <sstream>

Table::Table(string name, const vector<Column> &columns) : name(std::move(name)), columns(columns) {}

void Table::addRow(const vector<string> &rowData) {
    rows.emplace_back(rowData); // proveri ovo
}

void Table::removeRow(size_t rowIndex) {
    if(rowIndex >= rows.size()) {
        //todo throw "Row index out of range"
    }
    rows.erase(rows.begin() + rowIndex);
}

void Table::updateRow(size_t rowIndex, const vector<string> &newData) {
    if(rowIndex >= rows.size()) {
        //todo throw "Row index out of range"
    }
    if(newData.size() != columns.size()) {
        //todo throw "Invalid number of columns in new data"
    }
    rows[rowIndex].setData(newData);
}

void Table::printTable() {

    vector<int> columnWidths;
    for (const auto& column : columns) {
        int maxWidth = column.getName().length();
        for (const auto& row : rows) {
            std::stringstream ss;
            ss << row.getData()[&column - &columns[0]];
            int cellWidth = ss.str().length();
            maxWidth = max(maxWidth, cellWidth);
        }
        columnWidths.push_back(maxWidth);
    }

    for (int i = 0; i < columns.size(); i++) {
        cout << setw(columnWidths[i]) << columns[i].getName() << " ";
    }
    putchar('\n');
    for (const auto &row : rows) {
        for (int i = 0; i < columns.size(); i++) {
            std::stringstream ss;
            ss << row.getData()[i];
            cout << setw(columnWidths[i]) << ss.str() << " ";
        }
        putchar('\n');
    }
}

//<editor-fold desc="Getters">

const vector<Column> &Table::getColumns() const {
    return columns;
}

const string &Table::getName() const {
    return name;
}

const vector<Row> &Table::getRows() const {
    return rows;
}

//</editor-fold>
