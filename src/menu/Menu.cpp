#include <iostream>
#include <limits>
#include "Colors.h"
#include "Menu.h"
#include "../exceptions/SyntaxExceptions.h"
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
        ConsoleUtils::printLine({40}, '\xDA', '\xC4', '\xBF');
        ConsoleUtils::printRow({"MENU"}, {40});
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"1. CREATE DATABASE"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"2. IMPORT DATABASE FROM FILE"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"0. EXIT"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC0', '\xC4', '\xD9');
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
        ConsoleUtils::printLine({40}, '\xDA', '\xC4', '\xBF');
        ConsoleUtils::printRow({"MENU"}, {40});
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"1. EXECUTE SQL QUERY"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"2. EXPORT DATABASE"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"0. EXIT"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC0', '\xC4', '\xD9');
        cout << "\xB3" << "Enter a number to select your desired option: " << endl << "\xC4>";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "You have selected the option \"EXECUTE SQL QUERY \"" << endl;
                cleanConsole();
                vector<pair<string, int>> queries = readSQLQuery();
                bool hadError = false;
                for (const auto& [query, line] : queries) {
                    if (!query.empty()) {
                        try {
                            shared_ptr<Statement> statement = parseSQLQuery(query, line);
                            statement->execute(database);
                        } catch (const MissingArgumentsException& e) {
                            cout << e.what() << endl;
                            hadError = true;
                        } catch (const InvalidArgumentsException& e) {
                            cout << e.what() << endl;
                            hadError = true;
                        } catch (const SyntaxException& e) {
                            cout << e.what() << endl;
                            hadError = true;
                        } catch (const std::exception& e) {
                            cout << red << "General SQL Error: " << e.what() << resetColor << endl;
                            hadError = true;
                        }
                    }
                }
                if(hadError) {
                    cout << bgGray << "Press ENTER to continue..." << resetColor << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cleanConsole();
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

vector<pair<string, int>> Menu::readSQLQuery() {
    string query;
    string line;
    vector<pair<string, int>> queries;
    bool firstLine = true;
    int lineCounter = 0;
    bool wasPreviousLineEmpty = false;
    bool hasTextBeenEntered = false;
    int commandStartLine = 0;
    bool expectSemicolon = false;

    cout << bgGray << "Enter your SQL query. Type \"EXIT\" to exit the console." << resetColor << endl;
    do {
        if (!firstLine) {
            cout << bgGray << lineCounter << "." << resetColor << " ";
        }
        getline(cin, line);
        if (line == "exit" || line == "EXIT") {
            break;
        }
        if (!line.empty()) {
            hasTextBeenEntered = true;
            wasPreviousLineEmpty = false;
            string originalLine = line;
            highlightKeywords(line);
            cout << "\033[A\033[2K";  // Clear the current line
            cout << bgGray << lineCounter << "." << resetColor << " " << line << endl;
            if (originalLine.find(';') != string::npos) {
                stringstream ss(originalLine);
                string segment;
                while (getline(ss, segment, ';')) {
                    string trimmedSegment = regex_replace(segment, regex("^\\s+|\\s+$"), "");
                    if (!trimmedSegment.empty()) {
                        queries.emplace_back(trimmedSegment, commandStartLine + 1);
                    }
                    expectSemicolon = false;
                }
                commandStartLine = lineCounter + 1;
            } else {
                query += originalLine + " ";
                expectSemicolon = true;
            }
        } else {
            if (wasPreviousLineEmpty && hasTextBeenEntered) {
                if (!query.empty()) {
                    queries.emplace_back(regex_replace(query, regex("^\\s+|\\s+$"), ""), commandStartLine + 1);
                    query.clear();
                }
                break;
            }
            wasPreviousLineEmpty = true;
        }
        lineCounter++;
        firstLine = false;
    } while (true);

    if (!query.empty()) {  // Handle any remaining query part after the last non-empty line
        queries.emplace_back(regex_replace(query, regex("^\\s+|\\s+$"), ""), commandStartLine + 1);
        if(expectSemicolon) {
            throw MissingSemicolonException("Missing semicolon at the end of the statement.", lineCounter);
        }
    }
    return queries;
}


shared_ptr<Statement> Menu::parseSQLQuery(const string &query, int line) { //todo InvalidArgumentsException i MissingSemicolonException
    regex create_table_complete_regex(R"(^\s*CREATE\s+TABLE\s+([a-zA-Z0-9_]+)\s*\(([^)]+)\)\s*$)", regex_constants::icase);
    regex create_table_basic_pattern(R"(^\s*CREATE\s+TABLE\s*(?:([a-zA-Z0-9_]+)?\s*(\((.*)\))?)\s*$)", regex_constants::icase);
    regex columns_syntax_regex(R"(^\(([^,()]+(?:,[^,()]+)*)\)$)", regex_constants::icase);

    regex drop_table_regex("^DROP TABLE.*", regex_constants::icase);
    regex select_regex("^SELECT (.*) FROM ([a-zA-Z]+)( WHERE (.*) (AND (.*) )*)?$", regex_constants::icase);
    regex insert_regex("^INSERT INTO.*", regex_constants::icase);
    regex update_regex("^UPDATE.*SET.*", regex_constants::icase);
    regex delete_regex("^DELETE FROM.*", regex_constants::icase);
    regex show_tables_regex("^SHOW TABLES", regex_constants::icase);
    regex join_regex("^SELECT.*FROM.*INNER JOIN.*ON.*", regex_constants::icase);

    smatch matches;
    if (regex_match(query, matches, create_table_basic_pattern)) {
        if (matches[1].matched && matches[2].matched) {
            string column_definitions = matches[2];
            if (!regex_match(column_definitions, columns_syntax_regex)) {
                throw InvalidArgumentsException("Invalid or improperly formatted column definitions in CREATE TABLE statement.", line); //fixme
            }
            return make_shared<CreateTableStatement>(query);
        } else if (!matches[1].matched && !matches[2].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing table name and column definitions.", line);
        } else if (!matches[1].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing table name.", line);
        } else if (!matches[2].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing column definitions.", line);
        }
    }
    else if (regex_match(query, drop_table_regex)) {
        return make_shared<DropTableStatement>(query);
    } else if (regex_match(query, select_regex)) {
        return make_shared<SelectStatement>(query);
    } else if (regex_match(query, insert_regex)) {
        return make_shared<InsertIntoStatement>(query);
    } else if (regex_match(query, update_regex)) {
        return make_shared<UpdateStatement>(query);
    } else if (regex_match(query, delete_regex)) {
        return make_shared<DeleteFromStatement>(query);
    } else if (regex_match(query, show_tables_regex)) {
        return make_shared<ShowTablesStatement>(query);
    } else if (regex_match(query, join_regex)) {
        return make_shared<InnerJoinStatement>(query);
    } else {
        throw SyntaxException("Unrecognized or unsupported SQL query.", line);
    }
    return nullptr;
}

//<editor-fold desc="Utility functions">

void Menu::highlightKeywords(string& line) {
    map<string, string> keywords = {
            {"SELECT", red},
            {"FROM", red},
            {"WHERE", red},
            {"INNER", red},
            {"JOIN", red},
            {"ON", red},
            {"CREATE", yellow},
            {"TABLE", yellow},
            {"DROP", yellow},
            {"INSERT", yellow},
            {"INTO", yellow},
            {"UPDATE", cyan},
            {"SET", cyan},
            {"DELETE", cyan},
            {"SHOW", magenta},
            {"TABLES", magenta}
    };

    for (const auto& [keyword, color] : keywords) {
        regex keywordPattern("\\b" + keyword + "\\b", regex_constants::icase);
        string replacement;
        replacement.reserve(color.length() + keyword.length() + resetColor.length());
        replacement.append(color).append(keyword).append(resetColor);
        line = regex_replace(line, keywordPattern, replacement);
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
    ConsoleUtils::printLine({40}, '\xDA', '\xC4', '\xBF');
    ConsoleUtils::printRow({"Exiting the program..."}, {40});
    ConsoleUtils::printLine({40}, '\xC0', '\xC4', '\xD9');
    cout << "----------------------------------------" << endl;
    ConsoleUtils::printLine({40}, '\xDA', '\xC4', '\xBF', green);
    ConsoleUtils::printRow({"Program successfully completed!"}, {40}, ConsoleUtils::TextAlignment::CENTER, green);
    ConsoleUtils::printLine({40}, '\xC0', '\xC4', '\xD9', green);
    exit(0);
}

//</editor-fold>

