
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_DROPTABLESTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_DROPTABLESTATEMENT_H

#include "Statement.h"

class DropTableStatement : public Statement {

public:
    DropTableStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DROPTABLESTATEMENT_H
