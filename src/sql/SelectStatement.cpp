
#include "SelectStatement.h"

SelectStatement::SelectStatement(const string &query) : Statement(query) {}

bool SelectStatement::parse() {
    // errors();
    regex selectRegex(
            R"(^\s*SELECT\s+(.*?)\s+FROM\s+(\S+)(?:\s+(\S+))?(?:\s+(?:INNER\s+)?JOIN\s+(\S+)\s+(\S+)\s+ON\s+(\S+\.\S+)\s*=\s*(\S+\.\S+))?\s*(?:WHERE\s+(.+))?\s*;?\s*$)",
            regex_constants::icase);
    smatch matches;
    if (!regex_search(query, matches, selectRegex) || matches.size() < 4) {
        return false;
    }
    bool innerJoin = matches[4].matched;

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

    if (innerJoin) {
        join_table_name = matches[4];
        join_table_alias = matches[5];
        join_column = matches[6];
        join_column2 = matches[7];
    }

    if (matches.size() == 9) {
        parseWhereClause(matches[8]);
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
        for (const auto &column: db.getTable(table_name).getColumns()) {
            allColumns.push_back(column.getName());
        }
    }

    vector<string> selectedColumns;
    for (const auto &columnName: column_names) {
        if (columnName == "*") {
            selectedColumns.insert(selectedColumns.end(), allColumns.begin(), allColumns.end());
        } else {
            selectedColumns.push_back(columnName);
        }
    }

    if (!join_table_name.empty()) {
        // Entering JOIN
        shared_ptr<Table> fullMergedTable = Table::mergeTwoTables(db.getTable(table_name),
                                                                  db.getTable(join_table_name));
        fullMergedTable->printTable();
    } else {
        db.selectFromTable(table_name, table_alias, selectedColumns, filters);
    }
}


void SelectStatement::errors() {
    if (regex_match(query, regex(R"(^\s*SELECT(?:\s+FROM.*|\s*))", regex_constants::icase))) {
        throw MissingArgumentsException("SELECT has no arguments.");
    } else if (!regex_match(query, regex(".*\\s+FROM\\s*.*", regex_constants::icase))) {
        throw MissingArgumentsException("No FROM keyword specified.");
    } else if (!regex_search(query, regex(R"(.*\s+FROM\s+\w+\s*)", regex_constants::icase))) {
        throw MissingArgumentsException("FROM has no arguments.");
    }

}
