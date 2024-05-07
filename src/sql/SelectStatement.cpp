
#include "SelectStatement.h"

SelectStatement::SelectStatement(const string &query) : Statement(query) {}

bool SelectStatement::parse() {
    regex selectRegex(R"(^\s*SELECT\s+(.*?)\s+FROM\s+(\S+)\s*(\S*)\s*$)", regex_constants::icase);
    smatch matches;
    if (!regex_search(query, matches, selectRegex) || matches.size() < 4) {
        return false;
    }

    table_name = matches[2];
    table_alias = matches[3].length() > 0 ? matches[3] : table_name;

    string columns = matches[1];
    regex columnRegex(R"((\w+)\.(\w+)|(\w+)|(\*))");
    sregex_iterator it(columns.begin(), columns.end(), columnRegex);
    sregex_iterator end;

    if (columns.find('*') != string::npos && columns.size() == 1) {
        column_names.emplace_back("*");
    } else {
        while (it != end) {
            smatch match = *it;
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
            it++;
        }
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

    db.selectFromTable(table_name, table_alias, selectedColumns);
}


void SelectStatement::errors() {
}
