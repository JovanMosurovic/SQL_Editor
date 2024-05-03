
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

void Table::removeRow(const long long rowIndex) {
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

void Table::updateRow(const long long rowIndex, const vector<string> &newData) {
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
    vector<string> columnNames;
    columnNames.reserve(columns.size());
    for (const auto& column : columns) {
        columnNames.push_back(column.getName());
    }

    vector<vector<string>> rowData;
    rowData.reserve(rows.size());
    for (const auto& row : rows) {
        rowData.push_back(row.getData());
    }

    vector<int> columnWidths = ConsoleUtils::calculateColumnWidths(columnNames, rowData);

    ConsoleUtils::printLine(columnWidths, '\xDA', '\xC2', '\xBF');
    ConsoleUtils::printRow(columnNames, columnWidths);

    for (const auto & row : rows) {
        ConsoleUtils::printLine(columnWidths, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow(row.getData(), columnWidths);
    }

    ConsoleUtils::printLine(columnWidths, '\xC0', '\xC1', '\xD9');
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
