
#include "DropTableStatement.h"

DropTableStatement::DropTableStatement(const string &query) : Statement(query) {}

bool DropTableStatement::parse() {
    return false;
}

void DropTableStatement::execute(Database &db) {

}
