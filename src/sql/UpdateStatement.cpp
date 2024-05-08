
#include "UpdateStatement.h"

UpdateStatement::UpdateStatement(const string &query) : Statement(query) {}

bool UpdateStatement::parse() {
    regex update_regex(R"(^\s*UPDATE\s+(\S+)\s+SET\s+(.+?)(?:\s+WHERE\s+(.+))?\s*$)", regex_constants::icase);
    smatch matches;

    if (!regex_search(query, matches, update_regex) || matches.size() != 4) {
        return false;
    }

    table_name = matches[1];
    parseSetClause(matches[2]);
    if(matches[3].matched) {
        parseWhereClause(matches[3]);
    }
    return true;
}

void UpdateStatement::parseSetClause(const string &setClause) {
    regex setRegex(R"(\s*(\w+)\s*=\s*(\"[^"]*\"|'[^']*'|\w+)(?:\s*,)?)", regex_constants::icase);
    sregex_iterator setIt(setClause.begin(), setClause.end(), setRegex);
    sregex_iterator setEnd;

    while (setIt != setEnd) {
        smatch match = *setIt;
        string columnName = match.str(1);
        string value = match.str(2);

        // Remove quotes if they exist
        if ((value.front() == '\"' && value.back() == '\"') || (value.front() == '\'' && value.back() == '\'')) {
            value = value.substr(1, value.size() - 2);
        }

        // Add the change to the changes list
        changes[columnName] = value;

        setIt++;
    }
}

void UpdateStatement::parseWhereClause(const string &whereClause) {
    regex whereRegex(R"(\s*(\w+)\s*(=|!=)\s*(\"[^"]*\"|'[^']*'|\w+)(?:\s*(AND))?)", regex_constants::icase);
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
        } else if (operatorSymbol == "!=") {
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

void UpdateStatement::execute(Database &db) {
    if (!parse()) {
        return;
    }

    Table &table = db.getTable(table_name);
    for (Row& row : table.getRows()) {
        bool shouldUpdateRow = true;
        for (const auto &filter : filters) {
            if (filter && !filter->applyFilter(row)) {
                shouldUpdateRow = false;
                break;
            }
        }
        if (shouldUpdateRow) {
            for (const auto &change : changes) {
                row.updateColumnValue(change.first, change.second);
            }
        }
    }
}

void UpdateStatement::errors() {
    regex update_regex(R"(^\s*UPDATE\s+(\S+)(?:\s+SET\s*(.*))?(?:\s+WHERE\s*(.*))?\s*$)", regex_constants::icase);
    smatch matches;

    if (!regex_match(query, matches, update_regex)) {
        throw SyntaxException("Invalid syntax for UPDATE statement.");
    }

    if (!matches[1].matched) {
        throw MissingArgumentsException("UPDATE is missing table name.");
    }

    if (matches[2].matched && matches[2].str().empty()) {
        throw MissingArgumentsException("SET clause requires changes. None provided.");
    }

    if (matches[3].matched && matches[3].str().empty()) {
        throw MissingArgumentsException("WHERE clause requires conditions. None provided.");
    }
}
