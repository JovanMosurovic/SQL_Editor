
#include "Table.h"

Table::Table(const string &name, const vector<Column> &columns) {
    regex tableName_pattern("^[A-Za-z_]+$");
    if (!regex_match(name, tableName_pattern))
        throw InvalidTableNameException(name);
    this->name = name;
    this->columns = columns;
}

Table::Table(Table&& other) noexcept : name(std::move(other.name)), columns(std::move(other.columns)), rows(std::move(other.rows)) {}

Table::Table(const Table &other) : name(other.name), columns(other.columns), rows(other.rows) {}

void Table::addRow(const vector<string> &rowData) {
    if (rowData.size() != columns.size()) {
        throw InvalidDataForAddRowException(rowData.size(), columns.size());
    }
    vector<string> columnNames;
    columnNames.reserve(columns.size());
    for (const auto &column: columns) {
        columnNames.push_back(column.getName());
    }
    rows.emplace_back(columnNames, rowData);
}

void Table::removeRow(const long long rowIndex) {
    if (rowIndex >= rows.size()) {
        throw RowOutOfBoundsException(rowIndex, rows.size());
    }
    rows.erase(rows.begin() + rowIndex);
}

vector<Row>::iterator Table::removeRow(vector<Row>::iterator rowIt) {
    if(rowIt == rows.end())
        throw RowDoesNotExistException();
    return rows.erase(rowIt);
}

void Table::clearRows() {
    rows.clear();
}

void Table::updateRow(const long long rowIndex, const vector<string> &newData) {
    if (rowIndex >= rows.size()) {
        throw RowOutOfBoundsException(rowIndex, rows.size());
    }
    if (newData.size() != columns.size()) {
        throw InvalidDataForUpdateException(newData.size(), columns.size());
    }
    rows[rowIndex].setData(newData);
}

bool Table::hasColumn(const string &columnName) const {
    return any_of(columns.begin(), columns.end(), [&columnName](const Column &column) {
        return column.getName() == columnName;
    });
}

void Table::printTable() const {
    vector<string> columnNames;
    columnNames.reserve(columns.size());
    for (const auto &column: columns) {
        columnNames.push_back(column.getName());
    }

    vector<vector<string>> rowData;
    rowData.reserve(rows.size());
    for (const auto &row: rows) {
        rowData.push_back(row.getData());
    }

    vector<int> columnWidths = ConsoleUtils::calculateColumnWidths(columnNames, rowData);

    ConsoleUtils::printLine(columnWidths, '\xDA', '\xC2', '\xBF');
    ConsoleUtils::printRow(columnNames, columnWidths);

    for (const auto &row: rows) {
        ConsoleUtils::printLine(columnWidths, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow(row.getData(), columnWidths);
    }

    ConsoleUtils::printLine(columnWidths, '\xC0', '\xC1', '\xD9');
}

//<editor-fold desc="Getters">

const vector<Column> &Table::getColumns() const {
    return columns;
}

int Table::getColumnIndex(const string& columnName) const {
    auto it = find_if(columns.begin(), columns.end(), [&columnName](const Column& column) {
        return column.getName() == columnName;
    });
    if (it == columns.end()) {
        throw ColumnDoesNotExistException(columnName);
    }
    return distance(columns.begin(), it);
}

const string &Table::getName() const {
    return name;
}

const vector<Row> &Table::getRows() const {
    return rows;
}

vector<Row> &Table::getRows() {
    return rows;
}

//</editor-fold>
