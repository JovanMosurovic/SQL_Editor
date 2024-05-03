
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_INSERTINTOSTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_INSERTINTOSTATEMENT_H

#include "Statement.h"

class InsertIntoStatement : public Statement {

public:
    InsertIntoStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_INSERTINTOSTATEMENT_H
