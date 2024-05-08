
#include "InequalityFilter.h"

bool InequalityFilter::applyFilter(const Row &row) const {
    try {
        return row.getColumnValue(columnName) != value;
    } catch (const ColumnDoesNotExistException& e) {
        return false;
    }
}
