
#include "CreateTableStatement.h"

CreateTableStatement::CreateTableStatement(const string &query) : Statement(query) {


}

void CreateTableStatement::execute(Database &db) {

}

bool CreateTableStatement::parse() {
    return false;
}
