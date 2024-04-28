
#include "Database.h"

Database::Database(string name) : name(std::move(name)) {}

const string &Database::getName() const {
    return name;
}

