
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
#define ELEMENTAL_SQL_IMPLEMENTATION_MENU_H

#include "../database/Database.h"
#include "../sql/Statement.h"
#include "ConsoleUtils.h"

class Menu {

public:
    static void importDatabaseMenu();
    static void mainMenu(Database& database);

private:
    static void cleanConsole();
    static void finishProgram();
    static vector<pair<string, int>> readSQLQuery();
    static shared_ptr<Statement> parseSQLQuery(const string& query, int line);
    static void highlightKeywords(string& line);

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
