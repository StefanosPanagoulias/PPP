#include <stdio.h>
#include "registration.h"

int main(){
    
    aList list;
    Registration student;
    list = create();
    int option;
    int x;
    traverse_students(list); // Calls the traverse function to load the list of students with data from files
    traverse_expenses(list);
    option = menu();

    while(option != 10){

        if(option == 1){ // Function to insert a student into the list
            aList current, previous;
            insert_name(&student);
            insert_date(&student);
            insert_year(&student);
            insert_class(&student);
            insert_registration(&student);
            find_student(list, student, &previous, &current);
            insert_balance(&student);
            student.ptr = create_expense();
            if(current != NULL){
                printf("Student has already been added!\n");
            }
            else {
                insert(list, student);
                write_student(list);
                printf("\nStudent added successful!\n");
            }
        }

        if(option == 2){ // Function to delete a student
            insert_registration(&student);
            delete(list, student);
            write_expense(list);
            write_student(list);
        }

        if(option == 3){ // Print the list in alphabetical order
            print_student(list);
        }

        if(option == 4){ // Print the list in descending order starting from a certain balance
            lBalances below_list = create_balance();
            sort_balance_below(below_list, list);
            print_balance_list(below_list);
            below_list = destroy_balances(below_list);
        }

        if(option == 5){ // Display the data of a specific student
            insert_registration(&student);
            present(list, student);
        }

        if(option == 6){ // MAKE AN EXPENSE FOR A SPECIFIC STUDENT.
            load_expense(list);
            write_expense(list);
            write_student(list);
        }

        if (option == 7) { // LOAD THE ACCOUNT OF A STUDENT WITH A VALUE.
            load(list);
            write_student(list);
        }

        if (option == 8) { // LIST ACCORDING TO CLASS.
            sort_class(list);
        }

        option = menu();
    }

    list = destroy(list); // destroy all lists
    printf("Thank you! Come back anytime!\n");
}