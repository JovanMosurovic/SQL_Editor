
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SQLFORMAT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SQLFORMAT_H

#include "Format.h"

class SQLFormat : public Format {
public:

    string formatTable(const Table &table) const override;

    string formatRow(const Row &row) const override;
};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_SQLFORMAT_H
