
#ifndef PROJECT_OF_Registration_H
#define PROJECT_OF_Registration_H

typedef struct Date{ //Date structure for date
    int day;
    int month;
    int year;
}Date;

typedef struct ExpenseNode{ //Date structure for student expenses
    Date day;
    double amount;
    char description[50];

}ExpenseNode;

typedef struct Expense{ //Date structure for list of student expenses
    ExpenseNode StudentExpense;
    struct Expense *next;
}Expense;

typedef struct Expense *ExpenseList; //Creating a variable with a pointer that points to the list of expenses;

typedef struct Registration{ //Date structure for student registration
    char name[50];
    Date birthday;
    char class;
    char year[20];
    char registration[20];
    char balance[50];
    Expense *ptr;
}Registration;

typedef struct Students{ //Date structure for list of students
    Registration student;
    struct Students *next;
}Students;

typedef Students *aList; //Creating a variable with a pointer that points to the list of students;

typedef struct Balances{ //Date structure for auxiliary list of balances below a certain value
    Registration student;
    struct Balances *next;
}Balances;

typedef Balances *lBalances; //Creating a variable with a pointer that points to the list of balances;

aList create ();
void insert(aList list,Registration a1);
int isEmpty(aList list);
aList destroy(aList list);
void search(aList list,Registration key,aList *prev, aList *current);
void print_student(aList list);
void find_student(aList list,Registration key,aList *prev, aList *current);
void delete (aList list, Registration key);
int menu();
aList present(aList list, Registration key);
int validate_year(Registration *student);
void insert_year(Registration *student);
void balance_below(aList list);
void load(aList list);
void insert_date(Registration *key);
void insert_name(Registration *key);
ExpenseList create_expense();
void load_expense(aList list);
void insert_expense(ExpenseList list,ExpenseNode a1);
void print_expense(ExpenseList list);
void insert_date_expense(ExpenseNode *key);
void insert_description(ExpenseNode *key);
void insert_amount_expense(ExpenseNode *key);
void write_student(aList list);
void write_expense(aList list);
void traverse_students(aList list);
void insert_registration(Registration *key);
void sort_class(aList list);
void insert_class(Registration *key);
void insert_balance(Registration *key);
void traverse_expenses(aList list);
lBalances create_balance();
void sort_balance_below(lBalances list, aList student_list);
void print_balance_list(lBalances list);
lBalances destroy_balances(lBalances list);


#endif //PROJECT_OF_Registration_H
