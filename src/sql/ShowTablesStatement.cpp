
#include "ShowTablesStatement.h"

ShowTablesStatement::ShowTablesStatement(const string &query) : Statement(query) {

}

void ShowTablesStatement::execute(Database &db) {
    db.printDatabase();
}

bool ShowTablesStatement::parse() {
    return false;
}
