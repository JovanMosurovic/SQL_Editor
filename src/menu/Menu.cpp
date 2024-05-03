#include <iostream>
#include "Colors.h"
#include "Menu.h"
#include "../sql/CreateTableStatement.h"
#include "../sql/DropTableStatement.h"
#include "../sql/SelectStatement.h"
#include "../sql/InnerJoinStatement.h"
#include "../sql/InsertIntoStatement.h"
#include "../sql/UpdateStatement.h"
#include "../sql/DeleteFromStatement.h"
#include "../sql/ShowTablesStatement.h"

using namespace std;

void Menu::importDatabaseMenu() {
    int choice;
    do {
        cout << "\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF" << endl;
        cout << "\xB3                 MENU                 \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  1. CREATE DATABASE                  \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  2. IMPORT DATABASE FROM FILE        \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  0. EXIT                             \xB3\n";
        cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n";
        cout << "\xB3" << "Enter a number to select your desired option: " << endl << "\xC4>";
        cin >> choice;
     //   cleanConsole();

        switch (choice) {
            case 1: {
                try {
                    cout << "You have selected the option \"CREATE DATABASE\"" << endl;
                    string databaseName;
                    cout << "Enter the name of the database you want to create: " << endl << "\xC4>";
                    cin >> databaseName;
                    if (databaseName.empty()) {
                        throw DatabaseNameException(databaseName);
                    }
                    auto *database = new Database(databaseName);
                    cout << "Database \"" << databaseName << "\" has been " << green << "successfully" << resetColor << " created!" << endl;
                    mainMenu(*database);
                } catch (const DatabaseNameException& e) {
                    cout << e.what() << endl;
                } catch (const exception& e) {
                    cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
                }

                break;
            }

            case 2: {
                cout << "You have selected the option \"IMPORT DATABASE FROM FILE\"" << endl;
                getchar();
                getchar();
                //todo
                break;
            }

            case 0:
                finishProgram();
                break;

            default:
                cout << "Wrong choice, please enter the numbers 1, 2 or 0 to exit." << endl;
        }

    } while (choice != 0);
}

void Menu::mainMenu(Database &database) {
    int choice;
    do {
        cout << "\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF" << endl;
        cout << "\xB3                 MENU                 \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  1. EXECUTE SQL QUERY                \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  2. EXPORT DATABASE                  \xB3\n";
        cout << "\xC3\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xB4\n";
        cout << "\xB3  0. EXIT                             \xB3\n";
        cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n";
        cout << "\xB3" << "Enter a number to select your desired option: " << endl << "\xC4>";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "You have selected the option \"EXECUTE SQL QUERY \"" << endl;
                vector<string> queries = readSQLQuery(); // vector used in case there are multiple queries in one input

                for(const auto& query : queries) {
                    if(query.empty()) {
                        shared_ptr<Statement> statement = parseSQLQuery(query);
                    }
                }

                break;
            }

            case 2: {
                cout << "You have selected the option \"EXPORT DATABASE\"" << endl;
                //exportDatabase();
                //todo
                break;
            }

            case 0:
                finishProgram();
                break;

            default:
                cout << "Wrong choice, please enter the numbers 1, 2 or 0 to exit." << endl;
        }

    } while (choice != 0);
}

vector<string> Menu::readSQLQuery() {
    string query;
    string line;
    bool wasPreviousLineEmpty = false;
    bool hasTextBeenEntered = false;
    vector<string> queries;

    while (true) {
        getline(cin, line);
        if (line.empty()) {
            if (wasPreviousLineEmpty && hasTextBeenEntered) {
                queries.push_back(query);
                break;
            } else {
                wasPreviousLineEmpty = true;
                continue;
            }
        } else {
            wasPreviousLineEmpty = false;
            hasTextBeenEntered = true;
        }
        if (line.back() == ';') {
            query += line.substr(0, line.size() - 1);
            queries.push_back(query);
            query.clear();
        } else {
            query += line + "\n";
        }
    }
    return queries;
}

shared_ptr<Statement> Menu::parseSQLQuery(const string &query) {
    std::regex create_table_regex("^CREATE TABLE ([a-zA-Z]+) \\(([^)]+)\\)$", std::regex_constants::icase);
    regex drop_table_regex("^DROP TABLE.*", regex_constants::icase);
    regex select_regex("^SELECT.*FROM.*", regex_constants::icase);
    regex insert_regex("^INSERT INTO.*", regex_constants::icase);
    regex update_regex("^UPDATE.*SET.*", regex_constants::icase);
    regex delete_regex("^DELETE FROM.*", regex_constants::icase);
    regex show_tables_regex("^SHOW TABLES", regex_constants::icase);
    regex join_regex("^SELECT.*FROM.*INNER JOIN.*ON.*", regex_constants::icase);

    if (regex_match(query, create_table_regex)) {
        return make_shared<CreateTableStatement>(query);
    } else {
        throw invalid_argument("Invalid SQL query");
    }

}


void Menu::cleanConsole() {
    #ifdef _WIN32
            system("cls"); // For Windows
    #else
            system("clear"); // For Unix-based systems
    #endif
}

void Menu::finishProgram() {
    cout << "\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n";
    cout << "\xB3         Exiting the program...       \xB3\n";
    cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n";
    cout << "----------------------------------------";
    cout << "\n\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF\n";
    cout << "\xB3    Program successfully completed!   \xB3\n";
    cout << "\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9\n";
    exit(0);
}

