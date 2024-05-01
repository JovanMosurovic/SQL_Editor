#include "menu/Menu.h"

using namespace std;

int main() {

    try {
        // testiranje izuzetaka
        auto *table = new Table("tableA", {Column("column1"), Column("column2")});
        table->addRow({"data1", "data2"});

        table->printTable();

        auto *database = new Database("database");
        database->addTable(*table);

        database->createTable("tableB", {Column("column1"), Column("column2")});
        database->addRowToTable("tableB", {"data1", "data2"});
        database->addRowToTable("tableB", {"data1", "data2", "data3"});

        database->printDatabase();

        database->dropTable("tableA");
        database->dropTable("tableC");

        database->printDatabase();

        database->updateRowInTable("tableB", 0, {"data updated", "data updated"});

        database->printDatabase();

        database->removeRowFromTable("tableB", 0);

        database->printDatabase();

    //    Menu::importDatabaseMenu();
    } catch (const InvalidTableNameException& e) {
        cout << e.what() << endl;
    }

    return 0;
}
