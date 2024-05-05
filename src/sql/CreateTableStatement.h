
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H

#include "Statement.h"

class CreateTableStatement : public Statement {
    string tableName;
    vector<string> columnNames;

public:
    CreateTableStatement(const string &query);

    void execute(Database &db) override;
    bool parse() override;
 //   bool errors() override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_CREATETABLESTATEMENT_H
