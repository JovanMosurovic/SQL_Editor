
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_TABLEEXCEPTIONS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_TABLEEXCEPTIONS_H

#include <iostream>
#include <string>

using namespace std;

class InvalidTableNameException : public exception {
    string message;

public:
    InvalidTableNameException(const string& tableName)
            : message("\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Table name\033[0m " + tableName + " \033[1;31mis not typed in corrected format.\033[0m\n"
                      "\033[1;31m\033[4mFormat\033[0m\033[1;31m:\033[0m "
                      "Only English letters are allowed without spaces or special characters.\n") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class TableAlreadyExistsException : public exception {
    string message;

public:
    TableAlreadyExistsException(const string& tableName)
            : message("\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Table\033[0m " + tableName + " \033[1;31malready exists in database\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class TableDoesNotExistException : public exception {
    string message;

public:
    TableDoesNotExistException(const string& tableName)
            : message("\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Table\033[0m " + tableName + " \033[1;31mdoes not exist in database\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};







#endif //ELEMENTAL_SQL_IMPLEMENTATION_TABLEEXCEPTIONS_H
