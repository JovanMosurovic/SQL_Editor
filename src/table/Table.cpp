
#include "Table.h"

Table::Table(const string& name, const vector<Column> &columns) {
    regex tableName_pattern("^[A-Za-z]+$");
    if (regex_match(name, tableName_pattern)) {
        this->name = name;
        this->columns = columns;
    } else {
        throw InvalidTableNameException(name);
    }
}

void Table::addRow(const vector<string> &rowData) {
    try {
        if (rowData.size() != columns.size()) {
            throw InvalidDataForAddRowException(rowData.size(), columns.size());
        }
        rows.emplace_back(rowData);
    } catch (const InvalidDataForAddRowException &e) {
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
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
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Table::updateRow(size_t rowIndex, const vector<string> &newData) {
    try {
        if (rowIndex >= rows.size()) {
            throw RowOutOfBoundsException(rowIndex, rows.size());
        }
        if (newData.size() != columns.size()) {
            throw InvalidDataForUpdateException(newData.size(), columns.size());
        }
        rows[rowIndex].setData(newData);
    } catch (const RowOutOfBoundsException &e) {
        cout << e.what() << endl;
    } catch (const InvalidDataForUpdateException &e) {
        cout << e.what() << endl;
    } catch (const exception &e) {
        cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
    }
}

void Table::printTable() const {

    vector<int> columnWidths;
    for (const auto& column : columns) {
        int maxWidth = column.getName().length();
        int columnIndex = &column - &columns[0];
        for (const auto& row : rows) {
            int cellWidth = 0;
            if (columnIndex < row.getData().size()) {
                const string& cellValue = row.getData()[columnIndex];
                cellWidth = cellValue.empty() ? 0 : cellValue.length();
            }
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
            stringstream ss;
            ss << row.getData()[i];
            cout << setw(columnWidths[i]) << ss.str() << " ";
        }
        cout << endl;
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
