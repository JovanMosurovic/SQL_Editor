
#ifndef ELEMENTAL_SQL_IMPLEMENTATION_CONSOLEUTILS_H
#define ELEMENTAL_SQL_IMPLEMENTATION_CONSOLEUTILS_H

#include <vector>
#include <string>

namespace ConsoleUtils {
    void printLine(const std::vector<int>& columnWidths, char left, char middle, char right);
    void printRow(const std::vector<std::string>& rowData, const std::vector<int>& columnWidths);
    std::vector<int> calculateColumnWidths(const std::vector<std::string>& columns, const std::vector<std::vector<std::string>>& rows);
};


#endif //ELEMENTAL_SQL_IMPLEMENTATION_CONSOLEUTILS_H
