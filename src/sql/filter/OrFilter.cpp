
#include "OrFilter.h"

OrFilter::OrFilter(shared_ptr<IFilter> filter1, shared_ptr<IFilter> filter2)
        : filter1(std::move(filter1)), filter2(std::move(filter2)) {}

bool OrFilter::applyFilter(const Row &row) const {
    return filter1->applyFilter(row) || filter2->applyFilter(row);
}

string OrFilter::toString() const {
    return "(" + filter1->toString() + " OR " + filter2->toString() + ")";
}
