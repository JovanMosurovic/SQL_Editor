
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_ANDFILTER_H
#define ELEMENTAL_SQL_IMPLEMENTATION_ANDFILTER_H

#include "IFilter.h"

class AndFilter : public IFilter {
    shared_ptr<IFilter> filter1;
    shared_ptr<IFilter> filter2;

public:
    AndFilter(shared_ptr<IFilter> filter1, shared_ptr<IFilter> filter2);

    bool applyFilter(const Row& row) const override;

};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_ANDFILTER_H
