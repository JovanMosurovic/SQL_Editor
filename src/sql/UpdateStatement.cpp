
#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(const string &query) : Statement(query) {}

bool UpdateStatement::parse() {
    return false;
}

void UpdateStatement::execute(Database &db) {

}

bool UpdateStatement::errors() {
    return false;
}
