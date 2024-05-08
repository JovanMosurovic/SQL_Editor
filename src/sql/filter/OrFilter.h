
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_ORFILTER_H
#define ELEMENTAL_SQL_IMPLEMENTATION_ORFILTER_H

#include "IFilter.h"

class OrFilter : public IFilter {
    shared_ptr<IFilter> filter1;
    shared_ptr<IFilter> filter2;

public:
    OrFilter(shared_ptr<IFilter> filter1, shared_ptr<IFilter> filter2);

    bool applyFilter(const Row& row) const override;

    string toString() const override;
};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_ORFILTER_H
