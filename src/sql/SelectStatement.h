
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H

#include <string>
#include <vector>
#include "Statement.h"
#include "filter/AndFilter.h"
#include "filter/OrFilter.h"

using namespace std;

class SelectStatement : public Statement {
    string table_name;
    string table_alias;
    vector<string> column_names;
    vector<shared_ptr<IFilter>> filters;

public:
    SelectStatement(const string &query);

    bool parse() override;
    void parseWhereClause(const string &whereClause);
    void execute(Database &db) override;
    void errors() override;


};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H
