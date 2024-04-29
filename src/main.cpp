#include <cstdlib>
#include "menu/Menu.h"
#include "Database.h"

using namespace std;

int main() {
   // Menu::importDatabaseMenu();

    Table table("Table1", {Column("Column1"), Column("Column2")});
    table.addRow({"1", "2"});
    table.addRow({"3", "4"});
    table.addRow({"5", "6"});
    Table table2("TableTwo", {Column("Column123"), Column("Column234")});
    table2.addRow({"aa", "bb"});
    table2.addRow({"cc", "dd"});
    table2.addRow({"ee", "ff"});

    table.printTable();

//    table.removeRow(1);

//    table.printTable();
//
    table.removeRow(13);

//    Database database("Database1");
//    database.addTable(table);
//    database.addTable(table2);
//
//    database.dropTable(table2.getName());
//
//    database.createTable("TableC", {Column("Column1"), Column("Column2")});
//    database.createTable("TableC", {Column("Column2"), Column("Column4")});
//
//    database.printDatabase();
//
//    database.dropTable("TableM");

    return 0;
}
