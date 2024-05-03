
#include "InnerJoinStatement.h"

InnerJoinStatement::InnerJoinStatement(const string &query) : Statement(query) {}

bool InnerJoinStatement::parse() {
    return false;
}

void InnerJoinStatement::execute(Database &db) {

}
