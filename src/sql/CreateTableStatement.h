
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H

#include "Statement.h"

class CreateTableStatement : public Statement {
    string tableName;
    vector<string> columns;

public:
    CreateTableStatement(const string &query);

    void execute(Database &db) override;
    bool parse() override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H
