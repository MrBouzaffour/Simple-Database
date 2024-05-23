# Simple Database Project

This project is a simple database system implemented in C. It provides basic functionalities to manage rows and tables efficiently. The system allows operations like insertion, deletion, and querying of data structured in rows within tables.

## Features

- **Row Management**: Supports operations on individual data entries (rows).
- **Table Management**: Organize rows in a pageable table format.
- **Dynamic Row and Table Size Calculation**: Automatically calculates sizes based on row structures.
- **Data Serialization and Deserialization**: For storing and retrieving structured data.
- **Memory Management**: Includes functions for dynamic memory allocation and deallocation for tables.

## Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/yourusername/simple-database.git
cd simple-database
Usage

To compile the project, run the following command from the root of the project directory:
gcc -o db_program db.c command_processor.c input_management.c row_serialization.c statement_executor.c statement_preparer.c table.c -I.
This will create an executable named db_program which you can run to interact with the database.
