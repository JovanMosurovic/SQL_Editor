
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
                      "Only English letters are allowed without spaces or special characters.") {}

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
                      "\033[1;31mMaximum row index is\033[0m\033[1;31m\033[0m " + to_string(rowsSize)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidDataForUpdateException : public exception {
    string message;

public:
    InvalidDataForUpdateException(size_t newDataSize, size_t columnsSize)
            : message("\033[1;31m[UPDATE FAILED]\033[0m Cannot update row with mismatching column count.\n"
                      "\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Number of new data elements \033[0m(" + to_string(newDataSize) + ")\033[1;31m does not match the number of columns \033[0m(" + to_string(columnsSize) + ")\033[1;31m in the table.\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidDataForAddRowException : public exception {
    string message;

public:
    InvalidDataForAddRowException(size_t rowDataSize, size_t columnsSize)
            : message("\033[1;31m[INSERT FAILED]\033[0m Cannot add a new row with mismatching column count.\n"
                      "\033[1;31m\033[4mERROR\033[0m\033[1;31m: "
                      "Number of row data elements \033[0m(" + to_string(rowDataSize) + ")\033[1;31m does not match the number of columns \033[0m(" + to_string(columnsSize) + ")\033[1;31m in the table.\033[0m") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};






#endif //ELEMENTAL_SQL_IMPLEMENTATION_TABLEEXCEPTIONS_H
