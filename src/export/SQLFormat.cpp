
#include "SQLFormat.h"

string SQLFormat::formatTable(const Table& table) const {
    stringstream sql;
    sql << "CREATE TABLE " << table.getName() << " (";
    const auto& columns = table.getColumns();
    for (size_t i = 0; i < columns.size(); i++) {
        sql << columns[i].getName();
        if (i < columns.size() - 1) {
            sql << ", ";
        }
    }
    sql << ");";
    return sql.str();
}

string SQLFormat::formatRow(const Table& table, const Row& row) const {
    std::stringstream sql;
    sql << "INSERT INTO " << table.getName() << " (";
    const auto& columns = table.getColumns();
    for (size_t i = 0; i < columns.size(); ++i) {
        sql << columns[i].getName();
        if (i < columns.size() - 1) sql << ", ";
    }
    sql << ") VALUES (";
    const auto& data = row.getData();
    for (size_t i = 0; i < data.size(); ++i) {
        sql << "\"" << data[i] << "\"";
        if (i < data.size() - 1) sql << ", ";
    }
    sql << ");";
    return sql.str();
}
