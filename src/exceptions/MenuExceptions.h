
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_MENUEXCEPTIONS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_MENUEXCEPTIONS_H

#include <exception>
#include <string>

using namespace std;

class InvalidFileTypeException : public exception {
    string message;

public:
    InvalidFileTypeException(const string& details)
            : message("\033[1;31m[INVALID FILE TYPE ERROR]\033[0m Cannot export database to the provided file path.\n"
                      "\033[1;31m\033[4mERROR\033[0m: " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_MENUEXCEPTIONS_H
