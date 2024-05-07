
#include "SelectStatement.h"

SelectStatement::SelectStatement(const string &query) : Statement(query) {}

bool SelectStatement::parse() {
    return false;
}

void SelectStatement::execute(Database &db) {

}

bool SelectStatement::errors() {
    return false;
}
