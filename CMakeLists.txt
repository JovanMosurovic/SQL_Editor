cmake_minimum_required(VERSION 3.28)
project(Elemental_SQL_Implementation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Elemental_SQL_Implementation src/main.cpp
        src/menu/Colors.h
        src/menu/Menu.cpp
        src/menu/Menu.h
        src/table/Table.cpp
        src/table/Table.h
        src/table/Row.cpp
        src/table/Row.h
        src/table/Column.cpp
        src/table/Column.h
        src/Database.cpp
        src/Database.h
        src/exceptions/DatabaseExceptions.h
        src/exceptions/TableExceptions.h
        src/exceptions/SyntaxExceptions.h
        src/exceptions/MenuExceptions.h
)
