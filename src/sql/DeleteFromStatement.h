
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_DELETEFROMSTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_DELETEFROMSTATEMENT_H

#include "Statement.h"

class DeleteFromStatement : public Statement {

public:
    DeleteFromStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DELETEFROMSTATEMENT_H
