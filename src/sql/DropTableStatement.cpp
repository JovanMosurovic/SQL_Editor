
#include "DropTableStatement.h"

DropTableStatement::DropTableStatement(const string &query) : Statement(query) {}

bool DropTableStatement::parse() {
    regex dropTableRegex(R"(^\s*DROP\s+TABLE\s+(\S+)\s*$)", regex_constants::icase);
    smatch matches;
    if(!regex_search(query, matches, dropTableRegex) && matches.size() == 2) {
        return false;
    }
    table_name = matches[1];
    if (table_name.front() == '\'' || table_name.front() == '\"' || table_name.front() == '`') {
        table_name = table_name.substr(1, table_name.size() - 2);
    }
    return true;
}

void DropTableStatement::execute(Database &db) {
    if(!parse()) {
        return;
    }
    db.dropTable(table_name);
}
