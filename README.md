# Student Bar Account Management System

## Overview

This project is designed to manage student accounts for the bar of a secondary school. The application maintains updated information about all students, including their personal details (name, birth date, grade, class, number, balance) and their expenses throughout a calendar year (amount, description, date) using linked lists. 

### Key Features

The application allows users to interactively perform the following operations:

- **Add a new student**
- **Remove an existing student**
- **List all students alphabetically**
- **List students with a balance below a specified amount**
- **Display all information for a specific student**
- **Record an expense for a specific student**
- **Load a student's account with a specified amount**

### Data Management

The data structures used are optimized for memory efficiency, particularly with sorting solutions that utilize auxiliary data structures with pointers to the actual records. All relevant information is stored in text files, which are loaded when the program starts and updated as needed to prevent data loss. The program is also appropriately secured.

## Compilation Instructions

To compile and run the application, follow these steps:

1. Copy the folders `Project_data` and `Project_files` to an IDE configured to compile C code.
2. Navigate to the `Project_files` directory.
3. Run the command `make` to compile the program.
4. Execute the program with `./main`.

Once the program is running, a menu will appear with various navigation options.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
