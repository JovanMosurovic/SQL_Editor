#include <cstdlib>
#include "menu/Menu.h"
#include "Database.h"

using namespace std;

int main() {
   // Menu::importDatabaseMenu();

    try {
        auto *table = new Table("TableC", {Column("Column1"), Column("Column2")});
        table->addRow({"1", "2"});
        table->addRow({"3", "4"});
        table->addRow({"5", "6"});
        table->printTable();

        Table *table2 = new Table("TableTwo", {Column("Column1"), Column("Column2")});
        table2->addRow({"aa", "bb"});
        table2->addRow({"cc", "dd"});
        table2->addRow({"ee", "ff"});

        table2->printTable();

        table->removeRow(1);

        table->printTable();

        table->removeRow(13);


    } catch (const InvalidTableNameException& e) {
        cout << e.what() << endl;
    }


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
