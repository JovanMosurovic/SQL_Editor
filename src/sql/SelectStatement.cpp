
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

    regex whereRegex(R"(WHERE\s+(.*?)\s*(=|!=)\s*(\".*?\"|.*?)(?:\s*(AND|OR))?)", regex_constants::icase);
    sregex_iterator whereIt(query.begin(), query.end(), whereRegex);
    sregex_iterator whereEnd;
    shared_ptr<IFilter> lastFilter;
    string lastOperator;
    while (whereIt != whereEnd) {
        smatch match = *whereIt;
        string columnName = match.str(1);
        string operatorSymbol = match.str(2);
        string value = match.str(3);
        string logicalOperator = match.str(4);

        if (value.front() == '\"' && value.back() == '\"') {
            value = value.substr(1, value.size() - 2);
        }

        shared_ptr<IFilter> filter;
        if (operatorSymbol == "=") {
            filter = make_shared<EqualityFilter>(columnName, value);
        } else if (operatorSymbol == "!=") {
            filter = make_shared<InequalityFilter>(columnName, value);
        }

        if (lastFilter) {
            if (lastOperator == "AND") {
                filter = make_shared<AndFilter>(lastFilter, filter);
            } else if (lastOperator == "OR") {
                filter = make_shared<OrFilter>(lastFilter, filter);
            }
        }

        if(logicalOperator.empty() || logicalOperator == "AND") {
            filters.push_back(filter);
            lastFilter = nullptr;
        } else {
            lastFilter = filter;
        }

        lastOperator = logicalOperator;
        whereIt++;
    }

    if (lastFilter) {
        filters.push_back(lastFilter);
    }

    return true;
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
        cout << filter << " ";
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
