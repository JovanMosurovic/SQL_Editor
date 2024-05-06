
#include "InsertIntoStatement.h"

InsertIntoStatement::InsertIntoStatement(const string &query) : Statement(query) {}

bool InsertIntoStatement::parse() {
    regex insertIntoRegex(R"(^\s*INSERT\s+INTO\s+(\S+)?\s+(?:\(([^)]+)\))?\s+VALUES\s+(?:\(([^)]+)\))?$)", regex_constants::icase);
    smatch matches;
    if (!regex_search(query, matches, insertIntoRegex) || matches.size() != 4) {
        return false;
    }
    table_name = matches[1];
    if (table_name.front() == '\'' || table_name.front() == '\"' || table_name.front() == '`') {
        table_name = table_name.substr(1, table_name.size() - 2);
    }
    string columns = matches[2];
    regex columnRegex(R"(\w+|['"`]([^'"`]+)['"`])");
    sregex_iterator it(columns.begin(), columns.end(), columnRegex);
    sregex_iterator end;
    while (it != end) {
        string column = it->str();
        if(column.front() == '\'' || column.front() == '\"' || column.front() == '`') {
            column = column.substr(1, column.size() - 2);
        }
        column_names.push_back(column);
        it++;
    }
    string valuesTemp = matches[3];
    regex valuesRegex(R"(\w+|['"`]([^'"`]+)['"`])");
    sregex_iterator it2(valuesTemp.begin(), valuesTemp.end(), valuesRegex);
    sregex_iterator end2;
    while (it2 != end2) {
        string value = it2->str();
        if(value.front() == '\'' || value.front() == '\"' || value.front() == '`') {
            value = value.substr(1, value.size() - 2);
        }
        values.push_back(value);
        it2++;
    }
    return true;
}

void InsertIntoStatement::execute(Database &db) {

    if(!parse()) {
        return;
    }
    db.insertIntoTable(table_name, column_names, values);

}
