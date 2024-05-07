
#include "DeleteFromStatement.h"

DeleteFromStatement::DeleteFromStatement(const string &query) : Statement(query) {}

bool DeleteFromStatement::parse() {
    errors();
    regex delete_regex(R"(^\s*DELETE\s+FROM\s+(\S+)(?:\s+WHERE\s+(.+))?\s*$)", regex_constants::icase);
    smatch matches;

    if (!regex_search(query, matches, delete_regex) || matches.size() != 3) {
        return false;
    }

    table_name = matches[1];
    if (table_name.front() == '\'' || table_name.front() == '\"' || table_name.front() == '`') {
        table_name = table_name.substr(1, table_name.size() - 2);
    }
    if(matches[2].matched) {
        where_condition = matches[2];
    }
    return true;
}

void DeleteFromStatement::execute(Database &db) {
    if (!parse()) {
        return;
    }
    db.clearTable(table_name);
}


void DeleteFromStatement::errors() {
    regex delete_from_regex(R"(^\s*DELETE\s+FROM(?:\s+(\S+))?(?:\s+WHERE\s*(.*))?\s*$)", regex_constants::icase);
    smatch matches;

    if (!regex_match(query, matches, delete_from_regex)) {
        throw SyntaxException("Invalid syntax for DELETE FROM statement.");
    }

    if (!matches[1].matched) {
        throw MissingArgumentsException("DELETE FROM is missing table name.");
    }

    if (matches[2].matched && matches[2].str().empty()) {
        throw MissingArgumentsException("WHERE clause requires conditions. None provided.");
    }
}


