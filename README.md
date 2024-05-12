# Elemental SQL Implementation

This project encapsulates a command-line Database Management System (DBMS) developed in C++. It offers an interactive interface for users to manipulate databases, tables, and records. The system is designed to interpret and execute SQL-like commands, enabling a comprehensive suite of operations such as creating, reading, updating, and deleting (CRUD) data.
<br />


> The primary motivation behind this project was to delve deeper into the intricacies of database systems, with a particular focus on implementing operations like table creation, record insertion and deletion, and data querying.
>
> This project was developed as the [first university assignment](instructions.pdf) for "Practicum of Object-Oriented Programming" at the University of Belgrade School of Electrical Engineering majoring in Software Engineering. Please refer to the file for detailed assignment instructions.

## Table of Contents

- [Features](#features)
  - /
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Usage](#usage)
- [SQL Command Format](#sql-command-format)
- [Notes](#notes)

## Features

This project offers a wide range of features that simulate a real-world Database Management System (DBMS). Here are some of the key features:

- **Command-Line Interface**: The project provides a user-friendly command-line interface for interacting with the database. This allows users to execute SQL-like commands directly from the terminal.

- **Database Operations**: Users can create, read, update, and delete databases. This includes the ability to create new databases, list all existing databases, select a database for use, and delete a database.

- **Table Operations**: The system supports a variety of table operations such as creating new tables, listing all tables in a database, and deleting tables.

- **Record Operations**: Users can perform CRUD operations on records within a table. This includes inserting new records, querying records, updating records, and deleting records.

- **SQL-Like Syntax**: The system interprets and executes commands that are similar to SQL syntax. This includes commands like `CREATE TABLE`, `INSERT INTO`, `DELETE FROM`, `UPDATE`, `SELECT`, and `DROP TABLE`.

- **Join Operations**: The system supports `INNER JOIN` operations between two tables, allowing users to combine rows from two or more tables based on a related column.

- **Error Handling**: The system is equipped with robust error handling capabilities. It can handle and report syntax errors, missing arguments, and invalid operations.

- **C++ Implementation**: The entire system is implemented in C++, demonstrating the application of object-oriented programming principles and C++ features in building a complex system.

Please refer to the [SQL Command Format](#sql-command-format) section for more details on how to use these features.


## Getting Started

### Prerequisites

Before you begin, ensure you have the following prerequisites:

- C++ Compiler: Make sure you have a C++ compiler installed on your system.
- Ensure that your terminal supports ASCII escape codes to view the colorized and formatted output correctly.

### Usage

Upon execution, the program presents a menu with various options, as explained in [Features](#features) section, to interact with the user. Follow the on-screen prompts to perform operations.


## SQL Command Format 
All commands are case-insensitive. The wildcard character * can be used in any `SELECT` query and contexts where a `SELECT` query is utilized, to represent all possible values. Here are the formats for the SQL commands:
- Creating a table:
  ```
  create table <table_name> (<column1>, <column2>, ..., <columnN>);
  ```
- Inserting a record:
  ```
  insert into <table_name> (<column1>, <column2>, ..., <columnN>) values (<value1>, <value2>, ..., <valueN>);
  ```
- Deleting records:
  ```
  delete from <table_name> where <condition>;
  ```
- Updating records:
  ```
  update <table_name> set <column> = <value> where <condition>;
  ```
- Displaying tables:
  ```
  show tables;
  ```
- Deleting a table:
  ```
  drop table <table_name>;
  ```
- Selecting all columns from a table:
  ```
  select * from <table_name>;
  ```
- Selecting specific columns from a table:  
  ```
  select <column1>, <column2>, ..., <columnN>
  from <table_name> <br>
  where <condition>;
  ```
- Selecting with inner join between two tables with aliases:
  ```
  select <column1>, <column2>, ..., <columnN>
  from <table1> as <alias1>
  inner join <table2> as <alias2> on <alias1>.<column> = <alias2>.<column>
  where <condition>;
  ```
  
## Notes

In the SQL commands listed above, `<table_name>`, `<columnN>`, `<valueN>`, `<condition>`, and `<aliasN>` are placeholders. You should replace them with the actual table names, column names, values, conditions, and aliases that you use in your project. Here's what each placeholder represents:

- `<table_name>`: The name of the table on which you want to perform the operation.
- `<columnN>`: The name of the column in the table on which you want to perform the operation.
- `<valueN>`: The value that you want to insert or compare in the operation.
- `<condition>`: The condition that you want to apply to the operation.
- `<aliasN>`: The alias that you want to use for the table in the operation.

Please replace these placeholders with actual values before executing the SQL commands.
