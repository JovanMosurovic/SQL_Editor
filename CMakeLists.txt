cmake_minimum_required(VERSION 3.17)
project(Elemental_SQL_Implementation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Elemental_SQL_Implementation src/main.cpp
        src/menu/Menu.cpp
        src/database/table/Table.cpp
        src/database/table/Row.cpp
        src/database/table/Column.cpp
        src/database/Database.cpp
        src/sql/Statement.cpp
        src/sql/SelectStatement.cpp
        src/sql/CreateTableStatement.cpp
        src/sql/DropTableStatement.cpp
        src/sql/InnerJoinStatement.cpp
        src/sql/InsertIntoStatement.cpp
        src/sql/UpdateStatement.cpp
        src/sql/DeleteFromStatement.cpp
        src/sql/ShowTablesStatement.cpp
        src/menu/ConsoleUtils.cpp
        src/export/SQLFormat.cpp
        src/export/CustomFormat.cpp
        src/export/CustomFormat.h
        src/utils/SyntaxRegexPatterns.h
        src/sql/filter/IFilter.h
        src/sql/filter/EqualityFilter.cpp
        src/sql/filter/EqualityFilter.h
        src/sql/filter/InequalityFilter.cpp
        src/sql/filter/InequalityFilter.h
)
