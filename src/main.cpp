#include "menu/Menu.h"

using namespace std;

int main() {


    try {
        Menu::importDatabaseMenu();
    } catch (const InvalidTableNameException& e) {
        cout << e.what() << endl;
    }




    return 0;
}
