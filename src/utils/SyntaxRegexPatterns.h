
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXREGEXPATTERNS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXREGEXPATTERNS_H

#include <regex>

using namespace std;

namespace SyntaxRegexpatterns {
    // general regex
    const regex MUST_CONTAIN_PARENTHESES(R"(^.*\(.*\).*$)", regex_constants::icase);
    const regex MUST_CONTAIN_QUOTES(R"(^.*['"].*['"].*$)", regex_constants::icase);
    const regex VALID_QUOTE_REGEX(R"((?:[^'"]*('[^']*'|"[^"]*"))*[^'"]*$)");
    const regex PAIRED_BRACKETS_REGEX(R"(^([^()]*\([^()]*\))*[^()]*$)");
}

#endif //ELEMENTAL_SQL_IMPLEMENTATION_SYNTAXREGEXPATTERNS_H
