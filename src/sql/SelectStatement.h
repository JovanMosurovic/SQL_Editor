
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H

#include <string>
#include <vector>
#include "Statement.h"

using namespace std;

class SelectStatement : public Statement {

public:
    SelectStatement(const string &query);

    bool parse() override;
    void execute(Database &db) override;
    bool errors() override;


};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_SELECTSTATEMENT_H
