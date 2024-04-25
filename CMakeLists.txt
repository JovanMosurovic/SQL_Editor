cmake_minimum_required(VERSION 3.28)
project(Elemental_SQL_Implementation)

set(CMAKE_CXX_STANDARD 17)

add_executable(Elemental_SQL_Implementation main.cpp
        menu/Colors.h
        menu/Menu.cpp
        menu/Menu.h
        table/Table.cpp
        table/Table.h
        table/Row.cpp
        table/Row.h
        table/Column.cpp
        table/Column.h
)
