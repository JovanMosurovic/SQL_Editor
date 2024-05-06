
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
#define ELEMENTAL_SQL_IMPLEMENTATION_MENU_H

#include <iostream>
#include <limits>
#include "Colors.h"
#include "Menu.h"
#include "ConsoleUtils.h"
#include "../database/Database.h"
#include "../exceptions/SyntaxExceptions.h"
#include "../sql/CreateTableStatement.h"
#include "../sql/DropTableStatement.h"
#include "../sql/SelectStatement.h"
#include "../sql/InnerJoinStatement.h"
#include "../sql/InsertIntoStatement.h"
#include "../sql/UpdateStatement.h"
#include "../sql/DeleteFromStatement.h"
#include "../sql/ShowTablesStatement.h"
#include "../export/SQLFormat.h"
#include "../export/CustomFormat.h"


class Menu {

public:
    static void importDatabaseMenu();
    static void mainMenu(Database& database);
    static void exportDatabaseMenu(Database& database);

private:
    static void cleanConsole();
    static void finishProgram();
    static vector<pair<string, int>> readSQLQuery();
    static shared_ptr<Statement> parseSQLQuery(const string& query);
    static void highlightKeywords(string& line);

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
