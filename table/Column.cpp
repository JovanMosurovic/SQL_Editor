
#include "Column.h"

#include <utility>

Column::Column(string name) : name(std::move(name)) {}

const string &Column::getName() const {
    return name;
}
