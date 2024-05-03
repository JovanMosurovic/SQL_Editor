
#include "InsertIntoStatement.h"

InsertIntoStatement::InsertIntoStatement(const string &query) : Statement(query) {}

bool InsertIntoStatement::parse() {
    return false;
}

void InsertIntoStatement::execute(Database &db) {

}
