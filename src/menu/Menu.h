
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
#define ELEMENTAL_SQL_IMPLEMENTATION_MENU_H

#include "../Database.h"

class Menu {

public:
    static void importDatabaseMenu();
    static void mainMenu(Database& database);

private:
    static unordered_map<string, Database> databases; // dal treba static
    static void cleanConsole();
    static void finishProgram();

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_MENU_H
