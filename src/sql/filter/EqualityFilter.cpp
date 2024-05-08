
#include "EqualityFilter.h"

bool EqualityFilter::applyFilter(const Row &row) const {
    try {
        return row.getColumnValue(columnName) == value;
    } catch (const ColumnDoesNotExistException& e) {
        return false;
    }
}
