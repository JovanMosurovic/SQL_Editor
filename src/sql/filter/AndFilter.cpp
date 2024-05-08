
#include "AndFilter.h"

AndFilter::AndFilter(shared_ptr<IFilter> filter1, shared_ptr<IFilter> filter2)
        : filter1(std::move(filter1)), filter2(std::move(filter2)) {}

bool AndFilter::applyFilter(const Row &row) const {
    return filter1->applyFilter(row) && filter2->applyFilter(row);
}
