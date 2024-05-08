
#include "SelectStatement.h"

SelectStatement::SelectStatement(const string &query) : Statement(query) {}

bool SelectStatement::parse() {
    // errors();
    //  regex selectRegex(R"(^\s*SELECT\s+(.*?)\s+FROM\s+(\S+)\s*(\S*)\s*$)", regex_constants::icase);
    regex selectRegex(R"(^\s*SELECT\s+(.*?)\s+FROM\s+(\S+)(?:\s+(\S+))?\s*(?:WHERE\s+(.+))?\s*$)", regex_constants::icase);
    smatch matches;
    if (!regex_search(query, matches, selectRegex) || matches.size() < 4) {
        return false;
    }

    table_name = matches[2];
    table_alias = matches[3].length() > 0 ? matches[3] : table_name;

    string columns = matches[1];
    regex columnRegex(R"((\w+)\.(\w+)|(\w+)|(\*))");
    sregex_iterator columnIt(columns.begin(), columns.end(), columnRegex);
    sregex_iterator columnEnd;

    if (columns.find('*') != string::npos && columns.size() == 1) {
        column_names.emplace_back("*");
    } else {
        while (columnIt != columnEnd) {
            smatch match = *columnIt;
            string tableNamePart = match.str(1);
            string columnNamePart = match.str(2);
            string column = match.str(3);
            string star = match.str(4);

            if (!star.empty()) {
                column_names.emplace_back("*");
            } else {
                if (!tableNamePart.empty() && tableNamePart != table_alias) {
                    throw InvalidColumnReferenceException("Column reference does not match table alias or name.");
                }
                column_names.push_back(columnNamePart.empty() ? column : columnNamePart);
            }
            columnIt++;
        }
    }

    cout << "Where Clause: " << matches[4] << "\n";

    if (matches.size() == 5) {
        parseWhereClause(matches[4]);
    }


    return true;
}

void SelectStatement::parseWhereClause(const string &whereClause) {
    regex whereRegex(R"(\s*(\w+)\s*(=|!=|<>|<|>)\s*(\"[^"]*\"|'[^']*'|\w+)(?:\s*(AND|OR))?)", regex_constants::icase);
    sregex_iterator whereIt(whereClause.begin(), whereClause.end(), whereRegex);
    sregex_iterator whereEnd;

    while (whereIt != whereEnd) {
        smatch match = *whereIt;
        string columnName = match.str(1);
        string operatorSymbol = match.str(2);
        string value = match.str(3);

        // Remove quotes if they exist
        if ((value.front() == '\"' && value.back() == '\"') || (value.front() == '\'' && value.back() == '\'')) {
            value = value.substr(1, value.size() - 2);
        }

        // Create appropriate filter
        shared_ptr<IFilter> currentFilter;
        if (operatorSymbol == "=") {
            currentFilter = make_shared<EqualityFilter>(columnName, value);
        } else if (operatorSymbol == "!=" || operatorSymbol == "<>") {
            currentFilter = make_shared<InequalityFilter>(columnName, value);
        } else {
            currentFilter = nullptr;  // Handle other operators if needed
        }

        // Add the filter to the filters list
        if (currentFilter) {
            filters.push_back(currentFilter);
        }

        whereIt++;
    }
}




void SelectStatement::execute(Database &db) {
    if (!parse()) {
        return;
    }

    vector<string> allColumns;
    if (find(column_names.begin(), column_names.end(), "*") != column_names.end()) {
        for (const auto &column : db.getTable(table_name).getColumns()) {
            allColumns.push_back(column.getName());
        }
    }

    vector<string> selectedColumns;
    for (const auto &columnName : column_names) {
        if (columnName == "*") {
            selectedColumns.insert(selectedColumns.end(), allColumns.begin(), allColumns.end());
        } else {
            selectedColumns.push_back(columnName);
        }
    }

    cout << "Table Name: " << table_name << endl;
    cout << "Table Alias: " << table_alias << endl;
    cout << "Selected Columns: ";
    for (const auto &column : selectedColumns) {
        cout << column << " ";
    }
    cout << endl;
    cout << "Filters: ";
    for (const auto &filter : filters) {
        cout << filter->toString() << " : next filter : ";
    }
    cout << endl;

    db.selectFromTable(table_name, table_alias, selectedColumns, filters);
}


void SelectStatement::errors() {
    regex invalidArgumentsSelect(R"(SELECT\s+FROM\s+([a-zA-Z]+)\s*)",regex_constants::icase);
    regex invalidArgumentsFrom("\\s*FROM(?:\\s*| WHERE.*)", regex_constants::icase);

    if (regex_search(query, invalidArgumentsSelect)) {
        throw InvalidArgumentsException("Invalid SELECT Arguments");
    } else if (regex_search(query, invalidArgumentsFrom)) {
        throw InvalidArgumentsException("Invalid FROM Arguments");
    }

}
