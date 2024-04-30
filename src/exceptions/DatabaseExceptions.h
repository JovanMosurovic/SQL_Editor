
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_DATABASEEXCEPTIONS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_DATABASEEXCEPTIONS_H

#include "TableExceptions.h"

class TableAlreadyExistsException : public exception {
    string message;

public:
    TableAlreadyExistsException(const string& tableName)
            : message("\033[1;31m[TABLE CREATION FAILED]\033[0m Cannot create table with the provided name.\n"
                      "\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Table \033[0m" + tableName + "\033[1;31m already exists in the database.\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class TableDoesNotExistException : public exception {
    string message;

public:
    TableDoesNotExistException(const string& tableName)
            : message("\033[1;31m[TABLE OPERATION FAILED]\033[0m Cannot perform the requested operation.\n"
                      "\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Table \033[0m" + tableName + "\033[1;31m does not exist in the database.\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_DATABASEEXCEPTIONS_H
