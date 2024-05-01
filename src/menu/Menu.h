
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
#define ELEMENTAL_SQL_IMPLEMENTATION_MENU_H

#include "../database/Database.h"
#include "../sql/Statement.h"

class Menu {

public:
    static void importDatabaseMenu();
    static void mainMenu(Database& database);

private:
    static void cleanConsole();
    static void finishProgram();
    static string readSQLQuery();
    static Statement* parseSQLQuery(const string& query);

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
