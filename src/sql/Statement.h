
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_STATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_STATEMENT_H

#include <string>
#include "../database/Database.h"

class Statement {
protected:
    string query;

public:
    Statement(string query);
    virtual ~Statement();

    virtual bool parse() = 0;
    virtual void execute(Database &db) = 0;
    virtual bool errors() = 0;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_STATEMENT_H
