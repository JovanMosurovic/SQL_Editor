
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_FORMAT_H
#define ELEMENTAL_SQL_IMPLEMENTATION_FORMAT_H

#include <string>
#include "../database/table/Table.h"

class Format {
public:
    virtual string formatTable(const Table& table) const = 0;
    virtual string formatRow(const Table& table, const Row& row) const = 0;
    virtual ~Format() = default;
};

#endif //ELEMENTAL_SQL_IMPLEMENTATION_FORMAT_H
