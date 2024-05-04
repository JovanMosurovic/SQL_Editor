
#include "DropTableStatement.h"

DropTableStatement::DropTableStatement(const string &query) : Statement(query) {}

bool DropTableStatement::parse() {
    return true;
}

void DropTableStatement::execute(Database &db) {
    if(!parse()) {
        cout << red << "Syntax error in SQL query." << resetColor << endl;
        return;
    }
    db.dropTable(query);

}
