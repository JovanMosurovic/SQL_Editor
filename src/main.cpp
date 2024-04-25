#include <iostream>
#include <cstdlib>
#include "menu/Menu.h"
#include "table/Table.h"

using namespace std;


int main() {
 //   Menu::importDatabaseMenu();

    Table table("Table1", {Column("Column1"), Column("Column2")});

    table.addRow({"1", "2"});
    table.addRow({"3", "4"});

    table.printTable();

    table.updateRow(0, {"5", "6"});

    table.printTable();

    table.removeRow(1);

    table.printTable();

    return 0;
}
