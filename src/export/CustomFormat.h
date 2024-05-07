
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_CUSTOMFORMAT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_CUSTOMFORMAT_H

#include "Format.h"

class CustomFormat : public Format {

public:
    string formatTable(const Table &table) const override;

    string formatRow(const Table& table, const Row &row) const override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_CUSTOMFORMAT_H
