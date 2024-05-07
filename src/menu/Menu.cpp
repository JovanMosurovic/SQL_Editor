#include "Menu.h"

using namespace std;

void Menu::importDatabaseMenu() {
    string choice;
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

        if (choice == "1") {
            try {
                cout << "You have selected the option \"CREATE DATABASE\"" << endl;
                string databaseName;
                cout << "Enter the name of the database you want to create: " << endl << "\xC4>";
                cin >> databaseName;
                if (databaseName.empty()) {
                    throw DatabaseNameException(databaseName);
                }
                shared_ptr<Database> database = make_shared<Database>(databaseName);
                cout << "Database \"" << databaseName << "\" has been " << green << "successfully" << resetColor
                     << " created!" << endl;
                mainMenu(*database);
            } catch (const DatabaseNameException &e) {
                cout << e.what() << endl;
            } catch (const exception &e) {
                cout << red << "Unexpected exception caught:\n" << e.what() << resetColor << endl;
            }
            break;
        } else if (choice == "2") {
            cout << "You have selected the option \"IMPORT DATABASE FROM FILE\"" << endl;
            cout << "Enter the file path and name (e.g., C:/exports/mydatabase.sql): " << endl << "\xC4>";
            string file_path;
            cin >> file_path;
            if (file_path[0] == '\"' && file_path[file_path.size() - 1] == '\"') {
                file_path = file_path.substr(1, file_path.size() - 2);
            } else if (file_path[0] == '\'' && file_path[file_path.size() - 1] == '\'') {
                file_path = file_path.substr(1, file_path.size() - 2);
            }
            regex validPathRegex(".*\\.(sql|dbexp)$");
            if (!regex_match(file_path, validPathRegex)) {
                cout << "Invalid file type. Please provide a valid file with .sql or .dbexp extension." << endl;
                break;
            }
            break;
        } else if (choice == "0") {
            finishProgram();
            break;
        } else {
            cout << "Wrong choice, please enter the numbers 1, 2 or 0 to exit." << endl;
        }

    } while (choice != "0");
}

void Menu::mainMenu(Database &database) {
    string choice;
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

        if (choice == "1") {
            cout << "You have selected the option \"EXECUTE SQL QUERY \"" << endl;
            cleanConsole();
            int currLine = 0;
            vector<pair<string, int>> queries = readSQLQuery();
            try {
                for (const auto &[query, line]: queries) {
                    currLine = line;
                    if (!query.empty()) {
                        shared_ptr<Statement> statement = parseSQLQuery(query);
                        statement->execute(database);
                    }
                }
                cout << endl << bgGray << green << "All queries have been successfully executed!" << resetColor << endl;
                cout << bgGray << "Press ENTER to continue..." << resetColor << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cleanConsole();
            } catch (const exception &e) {
                cout << "\033[1mLine " << currLine << " \033[0m\xC4\033[1m>\033[0m ";
                cout << e.what() << endl;
                cout << bgGray << "Press ENTER to continue..." << resetColor << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cleanConsole();
            }
        } else if (choice == "2") {
            cout << "You have selected the option \"EXPORT DATABASE\"" << endl;
            try {
                exportDatabaseMenu(database);
            } catch (const exception &e) {
                cout << e.what() << endl;
            }
        } else if (choice == "0") {
            finishProgram();
        } else {
            cout << "Wrong choice, please enter the numbers 1, 2 or 0 to exit." << endl;
        }

    } while (choice != "0");
}

void Menu::exportDatabaseMenu(Database &database) {
    string choice;
    do {
        ConsoleUtils::printLine({40}, '\xDA', '\xC4', '\xBF');
        ConsoleUtils::printRow({"MENU"}, {40});
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"1. CUSTOM FORMAT EXPORT"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"2. SQL FORMAT EXPORT"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC3', '\xC5', '\xB4');
        ConsoleUtils::printRow({"0. GO BACK <\xC4"}, {40}, ConsoleUtils::TextAlignment::LEFT);
        ConsoleUtils::printLine({40}, '\xC0', '\xC4', '\xD9');
        cout << "\xB3" << "Enter a number to select your desired option: " << endl << "\xC4>";
        cin >> choice;

        if (choice == "1" || choice == "2") {
            cout << "\xB3" << "Enter file path and name (e.g., C:/exports/mydatabase.sql): " << endl << "\xC4>";
            string file_path;
            cin >> file_path;
            if (file_path[0] == '\"' && file_path[file_path.size() - 1] == '\"') {
                file_path = file_path.substr(1, file_path.size() - 2);
            } else if (file_path[0] == '\'' && file_path[file_path.size() - 1] == '\'') {
                file_path = file_path.substr(1, file_path.size() - 2);
            }
            shared_ptr<Format> format;
            try {
                if (choice == "1") {
                    regex validPathRegex(".*\\.dbexp$");
                    if (!regex_match(file_path, validPathRegex)) {
                        throw InvalidFileExportException(
                                "Invalid file path for exporting database. Please provide a valid path with .\033[1mdbexp\033[0m extension.");
                    }
                    format = make_shared<CustomFormat>();
                } else {
                    regex validPathRegex(".*\\.sql$");
                    if (!regex_match(file_path, validPathRegex)) {
                        throw InvalidFileExportException(
                                "Invalid file path for exporting database. Please provide a valid path with .\033[1msql\033[0m extension.");
                    }
                    format = make_shared<SQLFormat>();
                }

                database.exportDatabase(*format, file_path);
                cout << green << "Database exported successfully to " << resetColor << "\"" << file_path << "\"" << endl
                     << endl;
            } catch (const InvalidFileExportException &e) {
                cout << e.what() << endl;
            }

        } else if (choice == "0") {
            return;
        } else {
            cout << "Wrong choice, please enter the numbers 1, 2 or 0 to exit." << endl;
        }
    } while (choice != "0");
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

            if (query.empty()) {
                commandStartLine = lineCounter;
            }
            query += originalLine + " ";

            if (originalLine.find(';') != string::npos) {
                stringstream ss(query);
                string segment;
                while (getline(ss, segment, ';')) {
                    string trimmedSegment = regex_replace(segment, regex("^\\s+|\\s+$"), "");
                    if (!trimmedSegment.empty()) {
                        queries.emplace_back(trimmedSegment, commandStartLine);
                    }
                }
                query.clear();
            }
        } else {
            if (wasPreviousLineEmpty && hasTextBeenEntered) {
                if (!query.empty()) {
                    queries.emplace_back(regex_replace(query, regex("^\\s+|\\s+$"), ""), commandStartLine);
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
        queries.emplace_back(regex_replace(query, regex("^\\s+|\\s+$"), ""), commandStartLine);
    }
    return queries;
}

shared_ptr<Statement> Menu::parseSQLQuery(const string &query) { //fixme MissingSemicolonException
    // old create table // regex create_table_basic_pattern(R"(^\s*CREATE\s+TABLE\s+(\S+)?\s+(?:\(([^)]+)\))?\s*$)", regex_constants::icase);
    // regex create_table_basic_pattern(R"(^\s*CREATE\s+TABLE\s+(\S+)?\s+(?:\(?([^)]+)\)?)?\s*$)", regex_constants::icase);
    regex create_table_basic_pattern(R"(^\s*CREATE\s+TABLE\s+(\S+)?\s+(\(?([^)]+)\)?)?\s*$)", regex_constants::icase);
    regex columns_syntax_regex(R"(^([^,()]+(?:,[^,()]+)*)$)", regex_constants::icase);



    regex drop_table_regex(R"(^\s*DROP\s+TABLE\s+(\S+)\s*$)", regex_constants::icase);
    regex select_regex("^SELECT (.*) FROM ([a-zA-Z]+)( WHERE (.*) (AND (.*) )*)?$", regex_constants::icase);

    // old insert into // regex insert_into_regex(R"(^\s*INSERT\s+INTO\s+(\S+)?\s*(?:\(([^)]+)\))?\s*VALUES\s*\(?\s*(['"]([^'"]+)['"]\s*(?:,\s*['"]([^'"]+)['"]\s*)*)?\)?\s*$)",regex_constants::icase);
    regex insert_into_regex(R"(^\s*INSERT\s+INTO\s+(\S+)?\s+(\(?([^)]+)\)?)?\s*VALUES\s*(\(?\s*([^)]*)\)?)?\s*$)",
                            regex_constants::icase);
    regex insert_into_values_syntax_regex(R"(\s*\((\S+)\s*(?:,\s*(\S+)\s*)*\s*\))", regex_constants::icase);
    regex insert_into_values_with_quotes_regex(R"(^(['"].*['"](,\s*['"].*['"])*$))");

    regex update_regex("^UPDATE.*SET.*", regex_constants::icase);
    regex delete_regex("^DELETE FROM.*", regex_constants::icase);
    regex show_tables_regex("^SHOW TABLES", regex_constants::icase);
    regex join_regex("^SELECT.*FROM.*INNER JOIN.*ON.*", regex_constants::icase);

    regex multipleKeywordsRegex(".*create.*create.*|.*select.*select.*|.*insert.*insert.*|.*drop.*drop.*|.*update.*update.*",regex_constants::icase);

    regex invalidArgumentsSelect(R"(SELECT\s+FROM\s+([a-zA-Z]+)\s*)",regex_constants::icase); // ovde sam ti uradio select
    regex invalidArgumentsFrom("\\s*FROM(?:\\s*| WHERE.*)", regex_constants::icase);

    smatch matches;
    if (regex_match(query, matches, create_table_basic_pattern)) {
        string table_name = matches[1].str();
        string column_definitions_with_brackets = matches[2].str();
        string column_definitions = matches[3].str();

        if (!matches[1].matched && !matches[2].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing table name and column definitions.");
        } else if (!matches[1].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing table name.");
        } else if (!matches[2].matched) {
            throw MissingArgumentsException("CREATE TABLE is missing column definitions.");
        }
        // quotes check
        if (!regex_match(table_name, SyntaxRegexpatterns::VALID_QUOTE_REGEX) && !regex_match(column_definitions, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in table name and column definitions.");
        } else if (!regex_match(table_name, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in table name.");
        } else if (!regex_match(column_definitions, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in column definitions.");
        }
        // brackets check
        if (!regex_match(column_definitions_with_brackets, SyntaxRegexpatterns::PAIRED_BRACKETS_REGEX) ||
            !regex_match(column_definitions_with_brackets, SyntaxRegexpatterns::MUST_CONTAIN_PARENTHESES)) {
            throw SyntaxException("Mismatched parentheses in column definitions.");
        }
        // invalid column definitions
        if (!regex_match(column_definitions, columns_syntax_regex)) {
            throw InvalidArgumentsException(
                    "Invalid or improperly formatted column definitions in CREATE TABLE statement.");
        }
        return make_shared<CreateTableStatement>(query);
    } else if (regex_match(query, drop_table_regex)) {
        string table_name = matches[1].str();
        if (!matches[1].matched) {
            throw MissingArgumentsException("DROP TABLE is missing table name.");
        }
        if (!regex_match(table_name, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in table name.");
        }
        return make_shared<DropTableStatement>(query);
    } else if (regex_match(query, select_regex)) {
        return make_shared<SelectStatement>(query);
    } else if (regex_match(query, matches, insert_into_regex)) {
        string table_name = matches[1].str();
        string column_list_with_brackets = matches[2].str();
        string column_list = matches[3].str();
        string values_list_with_brackets = matches[4].str();
        string values_list = matches[5].str();

        if (!matches[1].matched && !matches[2].matched && !matches[3].matched) {
            throw MissingArgumentsException("INSERT INTO is missing table name, column list and values list.");
        } else if (!matches[1].matched && !matches[2].matched) {
            throw MissingArgumentsException("INSERT INTO is missing table name and column list.");
        } else if (!matches[1].matched && !matches[3].matched) {
            throw MissingArgumentsException("INSERT INTO is missing table name and values list.");
        } else if (!matches[2].matched && !matches[3].matched) {
            throw MissingArgumentsException("INSERT INTO is missing column list and values list.");
        } else if (!matches[1].matched) {
            throw MissingArgumentsException("INSERT INTO is missing table name.");
        } else if (!matches[2].matched) {
            throw MissingArgumentsException("INSERT INTO is missing column list.");
        } else if (!matches[3].matched) {
            throw MissingArgumentsException("INSERT INTO is missing values list.");
        }
        // quotes check
        if (!regex_match(values_list, insert_into_values_with_quotes_regex)) {
            throw SyntaxException("Values must be surrounded by quotes.");
        }
        if (!regex_match(table_name, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in table name.");
        } else if (!regex_match(column_list, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
            throw SyntaxException("Mismatched or mixed quotes in column list.");
        } else if (!regex_match(values_list, insert_into_values_syntax_regex)) {
            if (!regex_match(values_list, SyntaxRegexpatterns::VALID_QUOTE_REGEX)) {
                throw SyntaxException("Mismatched or mixed quotes in values list.");
            }
        }
        //brackets check
        if (!regex_match(column_list_with_brackets, SyntaxRegexpatterns::PAIRED_BRACKETS_REGEX)) {
            throw SyntaxException("Mismatched parentheses in column list.");
        } else if (!regex_match(values_list_with_brackets, SyntaxRegexpatterns::PAIRED_BRACKETS_REGEX)) {
            throw SyntaxException("Mismatched parentheses in values list.");
        } else if (!regex_match(column_list_with_brackets, SyntaxRegexpatterns::MUST_CONTAIN_PARENTHESES)) {
            throw SyntaxException("Missing parentheses in column list.");
        } else if (!regex_match(values_list_with_brackets, SyntaxRegexpatterns::MUST_CONTAIN_PARENTHESES)) {
            throw SyntaxException("Missing parentheses in values list.");
        }

        if (matches[2].matched && !regex_match(column_list, columns_syntax_regex)) {
            throw SyntaxException("Invalid or improperly formatted column list in INSERT INTO statement.");
        }
        return make_shared<InsertIntoStatement>(query);

    } else if (regex_match(query, update_regex)) {
        return make_shared<UpdateStatement>(query);
    } else if (regex_match(query, delete_regex)) {
        return make_shared<DeleteFromStatement>(query);
    } else if (regex_match(query, show_tables_regex)) {
        return make_shared<ShowTablesStatement>(query);
    } else if (regex_match(query, join_regex)) {
        return make_shared<InnerJoinStatement>(query);
    } else if (regex_match(query, multipleKeywordsRegex)) {
        throw SyntaxException("Multiple keywords detected");
    } else if (regex_search(query, invalidArgumentsSelect)) {
        throw InvalidArgumentsException("Invalid SELECT Arguments");
    } else if (regex_search(query, invalidArgumentsFrom)) {
        throw InvalidArgumentsException("Invalid FROM Arguments");
    } else {
        throw SyntaxException("Invalid SQL syntax.");
    }
}

//<editor-fold desc="Utility functions">

void Menu::highlightKeywords(string &line) {
    map<string, string> keywords = {
            {"SELECT", red},
            {"FROM",   red},
            {"WHERE",  red},
            {"INNER",  red},
            {"JOIN",   red},
            {"ON",     red},
            {"CREATE", yellow},
            {"TABLE",  yellow},
            {"DROP",   yellow},
            {"INSERT", yellow},
            {"INTO",   yellow},
            {"VALUES", yellow},
            {"UPDATE", cyan},
            {"SET",    cyan},
            {"DELETE", cyan},
            {"SHOW",   magenta},
            {"TABLES", magenta}
    };

    for (const auto &[keyword, color]: keywords) {
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

