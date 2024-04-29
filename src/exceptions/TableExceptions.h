
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

class RowOutOfBoundsException : public exception {
    string message;

public:
    RowOutOfBoundsException(size_t rowIndex, size_t rowsSize)
            : message("\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Row index\033[0m " + to_string(rowIndex) + " \033[1;31mis out of bounds.\033[0m\n"
                      "\033[1;31mMaximum row index is\033[0m\033[1;31m:\033[0m " + to_string(rowsSize) + "\n") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};







#endif //ELEMENTAL_SQL_IMPLEMENTATION_TABLEEXCEPTIONS_H
