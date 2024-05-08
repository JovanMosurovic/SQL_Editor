
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_INEQUALITYFILTER_H
#define ELEMENTAL_SQL_IMPLEMENTATION_INEQUALITYFILTER_H

#include "IFilter.h"

class InequalityFilter : public IFilter {
    string columnName;
    string value;

public:
    InequalityFilter(std::string columnName, std::string value)
            : columnName(std::move(columnName)), value(std::move(value)) {}

    bool applyFilter(const Row& row) const override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_INEQUALITYFILTER_H
