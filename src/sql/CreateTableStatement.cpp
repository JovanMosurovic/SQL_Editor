
#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(const string &query) : Statement(query) {}

void CreateTableStatement::execute(Database& db) {
    if (!parse()) {
        return;
    }
    // converting column names to Column objects
    vector<Column> columns;
    columns.reserve(columnNames.size());
    for (const auto& columnName : columnNames) {
        columns.emplace_back(columnName);
    }
    db.createTable(tableName, columns);
}

bool CreateTableStatement::parse() {
    regex createTableRegex(R"(CREATE\s+TABLE\s+(['"`]?\w+['"`]?)\s*\(((?:\s*(?:\w+|['"`][^'"`]+['"`])\s*,?\s*)+)\))", regex_constants::icase);
    smatch matches;
    if (regex_search(query, matches, createTableRegex) && matches.size() == 3) {

        tableName = matches[1].str();
        if (tableName.front() == '\'' || tableName.front() == '\"' || tableName.front() == '`') {
            tableName = tableName.substr(1, tableName.size() - 2);
        }

        string columns = matches[2].str();
        regex columnRegex(R"(\w+|['"`]([^'"`]+)['"`])");
        sregex_iterator it(columns.begin(), columns.end(), columnRegex);
        sregex_iterator end;
        while (it != end) {
            string column = it->str();
            if(column.front() == '\'' || column.front() == '\"' || column.front() == '`') {
                column = column.substr(1, column.size() - 2);
            }
            columnNames.push_back(column);
            it++;
        }
        return true;
    }
    return false;
}
