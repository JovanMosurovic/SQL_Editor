#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H

#include "DatabaseExceptions.h"

class MissingArgumentsException : public exception {
    string message;

public:
    MissingArgumentsException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m \033[1mMissing required arguments:\033[0m " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidArgumentsException : public exception {
    string message;

public:
    InvalidArgumentsException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR] Invalid arguments:\033[0m " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class SyntaxException : public exception {
    string message;

public:
    SyntaxException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m \033[1mSyntax error:\033[0m " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MissingSemicolonException : public exception {
    string message;

public:
    MissingSemicolonException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m \033[1mMissing semicolon:\033[0m " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidColumnReferenceException : public exception {
    string message;

public:
    InvalidColumnReferenceException(const string& details)
            : message("\033[1;31m[SYNTAX ERROR]\033[0m \033[1mInvalid column reference:\033[0m " + details) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif //ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXEXCEPTIONS_H
