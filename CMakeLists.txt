cmake_minimum_required(VERSION 3.28)
project(Elemental_SQL_Implementation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Elemental_SQL_Implementation src/main.cpp
        src/menu/Colors.h
        src/menu/Menu.cpp
        src/menu/Menu.h
        src/database/table/Table.cpp
        src/database/table/Table.h
        src/database/table/Row.cpp
        src/database/table/Row.h
        src/database/table/Column.cpp
        src/database/table/Column.h
        src/database/Database.cpp
        src/database/Database.h
        src/exceptions/DatabaseExceptions.h
        src/exceptions/TableExceptions.h
        src/exceptions/SyntaxExceptions.h
        src/exceptions/MenuExceptions.h
        src/sql/Statement.cpp
        src/sql/Statement.h
)
