#include <iostream>
#include "ConsoleUtils.h"

namespace ConsoleUtils {
    void printLine(const std::vector<int>& columnWidths, char left, char middle, char right) {
        std::cout << left;
        for (int i = 0; i < columnWidths.size(); ++i) {
            for (int j = 0; j < columnWidths[i]; ++j) {
                std::cout << "\xC4";
            }
            if (i < columnWidths.size() - 1) {
                std::cout << middle;
            }
        }
        std::cout << right << std::endl;
    }

    void printRow(const std::vector<std::string>& rowData, const std::vector<int>& columnWidths) {
        auto centerText = [](const std::string& text, int width) {
            int leftPadding = (width - text.size()) / 2;
            int rightPadding = width - text.size() - leftPadding;
            return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
        };

        for (int i = 0; i < rowData.size(); ++i) {
            std::cout << "\xB3" << centerText(rowData[i], columnWidths[i]);
        }
        std::cout << "\xB3" << std::endl;
    }

    std::vector<int> calculateColumnWidths(const std::vector<std::string>& columns, const std::vector<std::vector<std::string>>& rows) {
        std::vector<int> columnWidths;
        for (const auto& column : columns) {
            int maxWidth = column.length();
            int columnIndex = &column - &columns[0];
            for (const auto& row : rows) {
                int cellWidth = 0;
                if (columnIndex < row.size()) {
                    const std::string& cellValue = row[columnIndex];
                    cellWidth = cellValue.empty() ? 0 : cellValue.length();
                }
                maxWidth = std::max(maxWidth, cellWidth);
            }
            columnWidths.push_back(maxWidth + 2);
        }
        return columnWidths;
    }
}