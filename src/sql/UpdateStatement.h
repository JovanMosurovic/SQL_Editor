
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_UPDATESTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_UPDATESTATEMENT_H

#include "Statement.h"

class UpdateStatement : public Statement {

public:
    UpdateStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_UPDATESTATEMENT_H
