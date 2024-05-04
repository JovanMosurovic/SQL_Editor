
#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(const string &query) : Statement(query) {}

void CreateTableStatement::execute(Database& db) {
    if (!parse()) {
        cout << "Syntax error in SQL query." << endl;
        return;
    }
    // converting column names to Column objects
    vector<Column> columns;
    columns.reserve(columnNames.size());
    for (const auto& columnName : columnNames) {
        columns.emplace_back(columnName);
    }
    try {
        db.createTable(tableName, columns);
    } catch (const std::exception& e) {
        cout << "Error executing CREATE TABLE: " << e.what() << endl;
    }
}

bool CreateTableStatement::parse() {
    regex createTableRegex(R"(CREATE\s+TABLE\s+(\w+)\s*\(([\w\s,]+)\))", regex_constants::icase);
    smatch matches;
    if (regex_search(query, matches, createTableRegex) && matches.size() == 3) {
        tableName = matches[1];
        string columns = matches[2];
        regex columnRegex(R"(\w+)");
        sregex_iterator it(columns.begin(), columns.end(), columnRegex);
        sregex_iterator end;
        while (it != end) {
            columnNames.push_back(it->str());
            it++;
        }
        return true;
    }
    return false;
}
