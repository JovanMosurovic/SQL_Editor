
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_INNERJOINSTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_INNERJOINSTATEMENT_H

#include "Statement.h"

class InnerJoinStatement : public Statement {

public:
    InnerJoinStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;
    bool errors() override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_INNERJOINSTATEMENT_H
