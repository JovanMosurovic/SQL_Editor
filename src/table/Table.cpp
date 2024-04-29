
#include "Table.h"

Table::Table(const string& name, const vector<Column> &columns) {
    try {
        regex tableName_pattern("^[A-Za-z]+$");
        if (!(regex_match(name, tableName_pattern))) {
            throw InvalidTableNameException(name);
        }
        this->name = name;
        this->columns = columns;
    } catch(const InvalidTableNameException& e) {
        cout << e.what() << endl;
    } catch(const exception& e) {
        cout << red << "Unexpected exception caught: " << e.what() << resetColor << endl;
    }
}

void Table::addRow(const vector<string> &rowData) {
    rows.emplace_back(rowData);
}

void Table::removeRow(size_t rowIndex) {
    try {
        if (rowIndex >= rows.size()) {
            throw RowOutOfBoundsException(rowIndex, rows.size());
        }
        rows.erase(rows.begin() + rowIndex);
    } catch (const RowOutOfBoundsException &e) {
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << red << "Unexpected exception caught: " << e.what() << resetColor << endl;
    }
}

void Table::updateRow(size_t rowIndex, const vector<string> &newData) {
    try {
        if (rowIndex >= rows.size()) {
            throw RowOutOfBoundsException(rowIndex, rows.size());
        }
        if (newData.size() != columns.size()) {
            //todo throw "Invalid number of columns in new data"
        }
        rows[rowIndex].setData(newData);
    } catch (const RowOutOfBoundsException &e) { //todo dodaj ovde exception za invalid number of columns
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << red << "Unexpected exception caught: " << e.what() << resetColor << endl;
    }
}

void Table::printTable() const {

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
//    for (const auto &row : rows) {
//        cout << "Usao sam";
//        for (int i = 0; i < columns.size(); i++) {
//            stringstream ss;
//            ss << row.getData()[i];
//            cout << setw(columnWidths[i]) << ss.str() << " ";
//        }
//        cout << endl;
//    }
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
