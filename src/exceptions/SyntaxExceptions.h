#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H

#include "DatabaseExceptions.h"

class MissingArgumentsException : public exception {
    string message;

public:
    MissingArgumentsException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m: Missing required arguments in '" + details + "' statement.") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidArgumentsException : public exception {
    string message;

public:
    InvalidArgumentsException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m: Invalid arguments provided in the '" + details + "' statement.") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class SyntaxException : public exception {
    string message;

public:
    SyntaxException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m: The '" + details + "' statement has invalid syntax.") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H
