
#include "DeleteFromStatement.h"

DeleteFromStatement::DeleteFromStatement(const string &query) : Statement(query) {}

bool DeleteFromStatement::parse() {
    return false;
}

void DeleteFromStatement::execute(Database &db) {

}

bool DeleteFromStatement::errors() {
    return false;
}
