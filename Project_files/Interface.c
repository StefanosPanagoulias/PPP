#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registration.h"


void print_expense(ExpenseList list){
    ExpenseList aux = list->next;
    while(aux!=NULL){
        printf("Date: %d/%d/%d - DES: %s - Amount: %lf \n",aux->StudentExpense.day.day,aux->StudentExpense.day.month,aux->StudentExpense.day.year,aux->StudentExpense.description,aux->StudentExpense.amount);
        aux=aux->next;
    }
}

ExpenseList create_expense() {

    ExpenseList aux;
    ExpenseNode a1={0,0,0,0," "};
    aux = (ExpenseList ) malloc(sizeof(Expense));
    if (aux != NULL) {
        aux->StudentExpense=a1;
        aux->next = NULL;
    }
    return aux;
}

void search_expense(ExpenseList list,ExpenseNode key,ExpenseList *previous, ExpenseList *current){
    *previous=list;
    *current=list->next;
    while ((*current)!= NULL && (*current)->StudentExpense.amount-key.amount<0){
        *previous = *current;
        *current=(*current)->next;
    }
}

void insert_expense(ExpenseList list,ExpenseNode a1){
    ExpenseList no, previous, current;
    no=(ExpenseList) malloc(sizeof(Expense));
    if(no!=NULL){
        no->StudentExpense=a1;
        search_expense(list,a1,&previous,&current);
        no->next=previous->next;
        previous->next=no;
    }
}

void load_expense(aList list){
    ExpenseNode key;
    aList previous, current;
    Registration aux;
    int func=1;
    while(func) {
        insert_registration(&aux);
        find_student(list, aux, &previous, &current);
        if (current != NULL) {
            insert_date_expense(&key);
            insert_description(&key);
            insert_amount_expense(&key);
            if(key.amount<= strtod(current->student.balance,NULL)) {
                insert_expense(current->student.ptr, key);
                double x=strtod(current->student.balance,NULL);
                x-=key.amount;
                snprintf(current->student.balance,50,"%lf",x);
                func = 0;
                printf("\nExpense made with success!\n");
            }
            else{
                printf("insufficient balance\n");
                func=0;
            }
        }
        else {
            printf("student not found! \n");
            func=1;
        }
    }
}

int validate_balance(Registration *key){
    int x=0;
    for(int i=0;key->balance[i]!='\0';i++){
        if(isdigit(key->balance[i]) && strtod(key->balance,NULL)>=0){
            x=1;
        }
    }
    return x;
}

aList create() {
    aList aux;
    Registration a1={" ",0,0,0,' '," "};
    aux = (aList ) malloc(sizeof(Students));
    if (aux != NULL) {
        aux->student=a1;
        aux->next = NULL;
    }
    return aux;
}
void search_balance(lBalances list,Registration key,lBalances *previous, lBalances *current){
    *previous=list;
    *current=list->next;
    while ((*current)!= NULL && strcmp((*current)->student.balance,key.balance)>0){
        *previous = *current;
        *current=(*current)->next;
    }
}

lBalances create_balance() {
    lBalances aux;
    Registration a1={" ",0,0,0,' '," "};
    aux = (lBalances ) malloc(sizeof(Students));
    if (aux != NULL) {
        aux->student=a1;
        aux->next = NULL;
    }
    return aux;
}
void insert_balance(Registration *key){
    int aux=1;
    while(aux){
        printf("Enter the balance:");
        scanf(" %[^\n]s",key->balance);
        if(validate_balance(key)==0){
            printf("Try again!\n");
        }
        else(aux=0);
    }
}
void print_balance_list(lBalances list){
    lBalances aux = list->next;
    while(aux!=NULL){
        printf("\n%s - %d/%d/%d - %c - %s - %s - %s\n",aux->student.name,aux->student.birthday.day,aux->student.birthday.month,aux->student.birthday.year,aux->student.class,aux->student.year,aux->student.registration,aux->student.balance);
        printf("student expenses:\n");
        print_expense(aux->student.ptr);
        aux=aux->next;
    }
}
void insert_balance_below(lBalances list,Registration a1){
    lBalances no, previous, current;
    no=(lBalances) malloc(sizeof(Balances));
    if(no!=NULL){
        no->student=a1;
        search_balance(list,a1,&previous,&current);
        no->next=previous->next;
        previous->next=no;
    }
}
void sort_balance_below(lBalances list, aList list_students){
    aList aux = list_students->next;
    Registration balance;
    int x;
    double amount;
    insert_balance(&balance);
    amount= strtod(balance.balance,NULL);
    while(aux!=NULL){
        if(strtod(aux->student.balance,NULL)<amount){
            insert_balance_below(list,aux->student);
            x=1;
        }
        aux=aux->next;
    }
    if(x==0){
        printf("No account has a balance below %s",balance.balance);
    }
}

void insert(aList list,Registration a1){
    aList no, previous, current;
    no=(aList) malloc(sizeof(Students));
    if(no!=NULL){
        no->student=a1;
        search(list,a1,&previous,&current);
        no->next=previous->next;
        previous->next=no;
    }
}
int isEmpty(aList list){
    if(list->next==NULL){
        return 1;
    }
    else return 0;
}
int isEmpty_balances(lBalances list){
    if(list->next==NULL){
        return 1;
    }
    else return 0;
}
int isEmpty_expenses(ExpenseList list){
    if(list->next==NULL){
        return 1;
    }
    else return 0;
}
ExpenseList destroy_expense(ExpenseList list){
    ExpenseList temp_ptr;
    while (!isEmpty_expenses(list)) {
        temp_ptr=list;
        list = list->next;
        free(temp_ptr);
    }
    free(list);
    return NULL;
}
aList destroy(aList list){
    aList temp_ptr;
    while (!isEmpty(list)) {
        temp_ptr=list->next;
        temp_ptr->student.ptr=destroy_expense(temp_ptr->student.ptr);
        free(list);
        list=list->next;
    }
    free(list);
    return NULL;
}

lBalances destroy_balances (lBalances list){
    lBalances temp_ptr;
    while (!isEmpty_balances (list)) {
        temp_ptr = list;
        list = list->next;
        free (temp_ptr);
    }
    free(list);
    return NULL;
}

void search(aList list,Registration key,aList *previous, aList *current){
    *previous=list;
    *current=list->next;
    while ((*current)!= NULL && strcmp((*current)->student.name,key.name)<0){
        *previous = *current;
        *current=(*current)->next;
    }
    if ((*current)!=NULL && strcmp((*current)->student.name,key.name)!=0){
        *current=NULL;
    }
}
void print_student(aList list){
    aList aux = list->next;
    while(aux!=NULL){
        printf("\n%s - %d/%d/%d - %c - %s - %s - %s\n",aux->student.name,aux->student.birthday.day,aux->student.birthday.month,aux->student.birthday.year,aux->student.class,aux->student.year,aux->student.registration,aux->student.balance);
        printf("student expenses:\n");
        print_expense(aux->student.ptr);
        aux=aux->next;
    }
}

int menu(){ 
    int x;
    char aux[20];
    printf("\n\t\t\t\tMAIN MENU:\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("|[OPTION 01] = ENTER DATA FOR A NEW STUDENT.\n");
    printf("|[OPTION 02] = DELETE AN EXISTING STUDENT.\n");
    printf("|[OPTION 03] = LIST ALL STUDENTS IN ALPHABETICAL ORDER.\n");
    printf("|[OPTION 04] = LIST STUDENTS WITH BALANCE BELOW A CERTAIN AMOUNT.\n");
    printf("|[OPTION 05] = PRESENT ALL INFORMATION OF A SPECIFIC STUDENT.\n");
    printf("|[OPTION 06] = MAKE AN EXPENSE FOR A SPECIFIC STUDENT.\n");
    printf("|[OPTION 07] = LOAD THE ACCOUNT OF A STUDENT WITH AN AMOUNT.\n");
    printf("|[OPTION 08] = LIST STUDENTS ACCORDING TO CLASS.\n");
    printf("|[OPTION 10] = TERMINATE PROGRAM EXECUTION.\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("\t\t\tENTER THE FUNCTION YOU WANT: ");scanf("%s",aux);
    if(strlen(aux)<2 ){
        for(int i=0;i< strlen(aux)-1;i++){
            if(!isdigit(aux[i])){
                printf("Invalid Option! \n");
                return x=0;
            }
        }
    }
    if(atoi(aux)>=1 && atoi(aux)<=10) {
        x = atoi(aux);
        return x;
    }
    else
        printf("Invalid Option! \n");
    return x=0;
}
void find_student(aList list,Registration key,aList *previous, aList *current){
    *previous=list;
    *current=list->next;
    while ((*current)!= NULL && strcmp(key.registration,(*current)->student.registration)!=0){
        *previous = *current;
        *current=(*current)->next;
    }
    if ((*current)!=NULL && strcmp(key.registration,(*current)->student.registration)!=0){
        *current=NULL;
    }
}
void delete (aList list, Registration key){
    aList previous, actual;
    find_student (list, key, &previous, &actual);
    if (actual != NULL) {
        previous->next = actual->next;
        free (actual);
        actual->student.ptr=destroy_expense(actual->student.ptr);
        printf("\nStudent deleted successful!");
    }
    else{
        printf("student not found");
    }
}

aList present(aList list, Registration key){
    aList previous, current;
    find_student (list, key, &previous, &current);
    if(current==NULL){
        printf("student not found!\n");
    }
    else{
        printf("%s - %d/%d/%d - %c - %s - %s - %s\n",current->student.name,current->student.birthday.day,current->student.birthday.month,current->student.birthday.year,current->student.class,current->student.year,current->student.registration,current->student.balance);
        printf("student expenses:\n");
        print_expense(current->student.ptr);
    }
    return current;
}
int validate_year(Registration *student){
    char year[10];
    int x;
    strcpy(year,student->year);
    for (int i=0; year[i]!='\0';i++){
        if (!isdigit(year[i])) {
            return 0;
        }
    }
    if(atoi(year)>=1 && atoi(year)<=12) {
        return 1;
    }
    else return 0;
}
void insert_year(Registration *student){
    int aux=1;
    while(aux) {
        printf("Enter the academic year: \n");
        scanf(" %[^\n]s", student->year);
        if (validate_year(student) == 0) {
            printf("Try Again!\n");
        }
        else aux=0;
    }
}
int validate_name(Registration *key){
    int x = 0;
    char alphabet_uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q','R', 'S','T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alphabet_lowercase[26] = {'a','b', 'c', 'd','e','f','g','h','i','j', 'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<26;i++){
        if(key->name[0]==alphabet_uppercase[i]){
            x=1;
        }
    }
    if(x==1) {
        for (int i = 1; key->name[i] != '\0'; i++) {
            for (int k = 0; k < 26; k++) {
                if (strlen(key->name) > 1 && (key->name[i]) == (alphabet_lowercase[k])) {
                    x = 1;
                }
                if(key->name[i]==' ')return 0;
            }
        }
    }
    return x;
}
int validate_surname(char str[]) {
    int x = 0;
    char alphabet_uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q','R', 'S','T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alphabet_lowercase[26] = {'a','b', 'c', 'd','e','f','g','h','i','j', 'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<26;i++){
        if(str[0]==alphabet_uppercase[i]){
            x=1;
        }
    }
    if(x==1) {
        for (int i = 1; str[i] != '\0'; i++) {
            for (int k = 0; k < 26; k++) {
                if (strlen(str) > 1 && (str[i]) == (alphabet_lowercase[k])) {
                    x = 1;
                }
                if(str[i]==' '){
                    return 0;
                }
            }
        }
    }
    return x;
}
void insert_name(Registration *key){
    int aux=1;
    char surname[20];
    while(aux){
        printf("Enter the name: \n");
        scanf(" %[^\n]s",key->name);
        printf("Enter your surname: \n");
        scanf(" %[^\n]s",surname);
        if((validate_name(key))==0 || (validate_surname(surname))==0){
            printf("Try again!\n");
            aux=1;
        }
        else {
            strcat(key->name, " ");
            strcat(key->name, surname);
            aux = 0;
        }
    }
}
int validate_registration(Registration *student){
    int x = 0;
    for (int i = 0; student->registration[i] != '\0'; i++) {
        if (isdigit(student->registration[i]) && strlen(student->registration)==10){
            x=1;
        }
    }
    return x;
}
void insert_registration(Registration *key){
    int aux=1;
    while(aux){
        printf("Enter the registration:\n");
        scanf(" %[^\n]s",key->registration);
        if(validate_registration(key)==0){
            printf("Try again!\n");
            aux=1;
        }
        else(aux=0);
    }
}

void load(aList list){
    Registration key;
    aList previous, current;
    double aux,aux2=-1;
    while(aux2<0) {
        insert_registration(&key);
        insert_balance(&key);
        find_student(list, key, &previous, &current);
        if (current != NULL && strtod(key.balance, NULL)>0) {
            aux = strtod(current->student.balance, NULL) + strtod(key.balance, NULL);
            snprintf(current->student.balance, 50, "%.2lf", aux);
            aux2=1;
            printf("\nLoad made with success!\n");
        } else if(current==NULL){
            printf("Student not found! \n");
        }
        else{
            printf("The balance was not inserted correctly\n");
        }
    }
}
int validate_Date(Date birthday){
    if ((birthday.month==1|| birthday.month==3||birthday.month==5||birthday.month==7||birthday.month==8||birthday.month==10||birthday.month==12) && birthday.day>=1 && birthday.day<=31){
        return 1;
    }
    if(((birthday.month==2 && birthday.year % 100!=0 && birthday.year%4==0) || birthday.year%400==0) && birthday.day>=1 && birthday.day<=29) {
        return 1;
    }
    else if(birthday.month==2 && (birthday.day>=1 && birthday.day<=28)){
        return 1;
    }

    if (((birthday.month==4|| birthday.month==6||birthday.month==9||birthday.month==11)&& birthday.day>=1 && birthday.day<=30)){
        return 1;
    }
    return 0;
}
int validate_Date_student(char key[]){
    int x;
    int i=0;
    for(i;key[i]!='\0';i++){
        if(isdigit(key[i]) && strtod(key,NULL)>=1){
            x=1;
        }
        else if(key[i]!='\0'){
            x=0;
        }
    }
    return x;
}
void insert_date(Registration *key) {
    int aux = 1;
    char day[3];
    char month[3];
    char year[5];
    while (aux) {
        printf("Enter the day: \n");
        scanf(" %[^\n]s", day);
        printf("Enter the month: \n");
        scanf(" %[^\n]s", month);
        printf("Enter the year: \n");
        scanf(" %[^\n]s", year);
        if (validate_Date_student(year) && validate_Date_student(day) && validate_Date_student(month)) {
            key->birthday.month = atoi(month);
            key->birthday.day = atoi(day);
            key->birthday.year = atoi(year);
            if (validate_Date(key->birthday) == 1) {
                aux = 0;
            }
            else {
                printf("Try Again!\n");
                aux=1;
            }
        }
        else {
            printf("Try Again!\n");
            aux=1;
        }
    }
}
void insert_date_expense(ExpenseNode *key){
    int aux = 1;
    char day[3];
    char month[3];
    char year[5];
    while (aux==1) {
        printf("Enter the day: \n");
        scanf(" %[^\n]s", day);
        printf("Enter the month: \n");
        scanf(" %[^\n]s", month);
        printf("Enter the year: \n");
        scanf(" %[^\n]s", year);
        if (validate_Date_student(year) && validate_Date_student(day) && validate_Date_student(month)) {
            key->day.month = atoi(month);
            key->day.day = atoi(day);
            key->day.year = atoi(year);
            if (validate_Date(key->day) == 1) {
                aux = 0;
            } else {
                printf("Try Again!\n");
                aux=1;
            }
        }
        else {
            printf("Try Again!\n");
            aux=1;
        }
    }
}
int validate_description(ExpenseNode *key){
    int x = 0;
    char alphabet[53] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J',
                         'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's',
                         'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z',' '};
    for (int i = 0; key->description[i] != '\0'; i++) {
        for (int k = 0; k < 53; k++) {
            if (strlen(key->description)>1 && (key->description[i]) == (alphabet[k])) {
                x = 1;
            }
        }
    }
    return x;
}

void insert_description(ExpenseNode *key){
    int aux=1;
    while(aux){
        printf("Enter the description of the purchase: ");
        scanf(" %[^\n]s",key->description);
        if(validate_description(key)==0){
            printf("Try Again!\n");
            aux=1;
        }
        else(aux=0);
    }
}
int validate_amount_expense(char aux[]){
    int x=0;
    for(int i=0;aux[i]!='\0';i++){
        if(isdigit(aux[i]) && strtod(aux,NULL)>=0){
            x=1;
        }
    }
    return x;
}
void insert_amount_expense(ExpenseNode *key){
    int aux=1;
    char aux2[50];
    while(aux){
        printf("Enter the amount of the purchase: ");
        scanf(" %[^\n]s",aux2);
        if(validate_amount_expense(aux2)==0){
            printf("Try Again!\n");
            aux=1;
        }
        else{
            key->amount= strtod(aux2,NULL);
            aux=0;
        }
    }
}
void write_student(aList list){
    FILE *f;
    f=fopen("../Project_data/RegisteredStudents.txt", "w");
    aList aux = list->next;
    while(aux!=NULL){
        fprintf(f,"%s - %d/%d/%d - %c - %s - %s - %s",aux->student.name,aux->student.birthday.day,aux->student.birthday.month,aux->student.birthday.year,aux->student.class,aux->student.year,aux->student.registration,aux->student.balance);
        fprintf(f,"\n");
        aux=aux->next;
    }
    fclose(f);
}

void write_expense(aList list){
    FILE *f;
    f= fopen("../Project_data/expenses.txt", "w");
    aList aux = list->next;
    while(aux!=NULL){
        ExpenseList expense= aux->student.ptr->next;
        while(expense!=NULL) {
            fprintf(f, "%s - %d/%d/%d - %s - %.2lf",expense->StudentExpense.description ,expense->StudentExpense.day.day, expense->StudentExpense.day.month,expense->StudentExpense.day.year,aux->student.registration, expense->StudentExpense.amount);
            fprintf(f,"\n");
            expense=expense->next;
        }
        aux = aux->next;
    }
    fclose(f);
}
void iterate_Date(aList list, Registration *student, const char linha[]){
    int contador=0;
    int aux=0;
    int aux2=0;
    int aux3=0;
    int aux4=0;
    char day[3];
    char month[3];
    char year[5];
    for(int i=0;linha[i]!='\0';i++) {
        if (linha[i] == '-'){
            contador++;
        }
        if (linha[i] == '/'){
            aux2++;

        }
        if(contador==1){
            if(aux2==1 && linha[i]!='/'){
                month[aux3]=linha[i];
                aux3++;
            }
            if(aux2==2 && linha[i]!= '/' && linha[i]!= ' ' && linha[i]!= '\n'){
                year[aux4]=linha[i];
                aux4++;
            }
            if(linha[i]!='-' && linha[i]!=' ' && linha[i]!='/' && aux2==0) {
                day[aux] = linha[i];
                aux++;
            }
        }
    }
    student->birthday.day= atoi(day);
    student->birthday.month= atoi(month);
    student->birthday.year= atoi(year);
}
void iterate_name(aList list, Registration *student,const char linha[]){ 
    int contador=0;
    int espaco=0;
    int i=0;
    for(;linha[i]!='\0';i++){
        if(linha[i]=='-'){
            contador++;
        }
        if (linha[i]==' '){
            espaco++;
        }
        if(contador==0 && espaco!=2 && linha[i]!= '\n'){
            student->name[i]=linha[i];
        }
    }
    student->name[i]='\0';
    //printf("%s\n",student->name);
}

void iterate_class(aList list, Registration *student, const char linha[]){
    int contador=0;
    for(int i=0; linha[i]!='\0';i++) {
        if(linha[i]=='-'){
            contador++;
        }
        if(contador==2 && linha[i]!= '-' && linha[i]!=' ' && linha[i]!= '\n'){
            student->class=linha[i];
        }
    }
}
void iterate_year(aList list, Registration *student, const char linha[]){
    int contador=0;
    int x=0;
    char aux[5];
    int i=0;
    for(; linha[i]!='\0';i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if (contador == 3 && linha[i] != '-' && linha[i]!=' ' && linha[i]!= '\n' && isdigit(linha[i])) {
            aux[x]= linha[i];
            x++;
        }
    }
    aux[x]='\0';
    strcpy(student->year, aux);
}
void iterate_registration(aList list, Registration *student, const char linha[]) {
    int contador = 0;
    int x=0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==4 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            student->registration[x] = linha[i];
            x++;
        }
    }
    student->registration[x]='\0';
}
void iterate_balance(aList list, Registration *student, const char linha[]) {
    int contador = 0;
    int x=0;
    char balance[20];
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==5 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            balance[x] = linha[i];
            x++;
        }
    }
    balance[x]='\0';
    strcpy(student->balance, balance);
}
void iterate_registration_expense(Registration *student, const char linha[]) {
    int contador = 0;
    int x=0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==2 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            student->registration[x] = linha[i];
            x++;
        }
    }
}
void iterate_Date_expense(ExpenseNode *student, const char linha[]){
    int contador=0;
    int aux=0;
    int aux2=0;
    int aux3=0;
    int aux4=0;
    char day[3];
    char month[3];
    char year[5];
    for(int i=0;linha[i]!='\0';i++) {
        if (linha[i] == '-'){
            contador++;
        }
        if (linha[i] == '/'){
            aux2++;

        }
        if(contador==1){
            if(aux2==1 && linha[i]!='/'){
                month[aux3]=linha[i];
                aux3++;
            }
            if(aux2==2 && linha[i]!= '/' && linha[i]!= ' ' && linha[i]!= '\n'){
                year[aux4]=linha[i];
                aux4++;
            }
            if(linha[i]!='-' && linha[i]!=' ' && linha[i]!='/' && aux2==0) {
                day[aux] = linha[i];
                aux++;
            }
        }
    }
    student->day.day= atoi(day);
    student->day.month= atoi(month);
    student->day.year= atoi(year);
}
void iterate_description_expense(ExpenseNode *student,const char linha[]){
    int contador=0;
    int espaco=0;
    int x=0;
    char aux[20];
    for(int i=0; linha[i]!='\0';i++){
        if(linha[i]=='-'){
            contador++;
        }
        if (linha[i]==' '){
            espaco++;
        }
        if(contador==0 && linha[i]!= '-' && linha[i]!=' ' && linha[i]!= '\n'){
            aux[x]=linha[i];
            x++;
        }
    }
    aux[x]=0;
    strcpy(student->description,aux);
}
void iterate_amount_expense(ExpenseNode *student, const char linha[]) { 
    int contador = 0;
    int x=0;
    char aux[50];
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==3 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            aux[x] = linha[i];
            x++;
        }
    }
    aux[x]=0;
    student->amount= strtod(aux,NULL);
}
void traverse_expenses(aList list){
    FILE *file;
    aList previous, current;
    file= fopen("../Project_data/expenses.txt", "r");
    char linha[150];
    while( fgets (linha, 150, file)!=NULL ) {
        ExpenseNode key={0,0,0,0," "};
        Registration student={"",0,0,0,' '," "," "};
        iterate_registration_expense(&student, linha);
        iterate_Date_expense(&key, linha);
        iterate_description_expense(&key, linha);
        iterate_amount_expense(&key, linha);
        find_student(list, student, &previous, &current);
        if (current != NULL) {
            insert_expense(current->student.ptr, key);
        }
    }
    fclose(file);
}
void traverse_students(aList list){ 
    FILE *file;
    file= fopen("../Project_data/Registeredstudents.txt", "r");
    char linha[200];

    while( fgets (linha, 200, file)!=NULL ) {
        Registration student={"",0,0,0,' '," "," "};
        iterate_name(list,&student, linha);
        iterate_Date(list,&student,linha);
        iterate_class(list, &student, linha);
        iterate_year(list, &student, linha);
        iterate_registration(list, &student, linha);
        iterate_balance(list, &student, linha);
        student.ptr=create_expense();
        insert(list, student);
    }
    fclose(file);
}

int validate_class(char str[]) {
    int x = 0;
    char alphabet[26] = {'A', 'B', 'C','D','E','F','G','H','I', 'J', 'K','L','M','N','O','P','Q','R','S',
                         'T','U','V','W','X','Y','Z'};
    for (int i = 0; i < 25; i++) {
        if ((strlen(str) == 1) && (str[0]) == (alphabet[i])) {
            x = 1;
        }
    }
    return x;
}
void insert_class(Registration *key){
    int aux=1;
    char aux2[20];
    while(aux){
        printf("class:\n");
        scanf(" %[^\n]s",aux2);
        if(validate_class(aux2)==0){
            printf("Try Again!\n");
        }
        else{
            key->class=aux2[0];
            (aux=0);
        }
    }
}

void sort_class(aList list){ 
    Registration student;
    insert_class(&student);
    aList aux = list->next;
    int x=0;
    while(aux!=NULL){
        if (aux->student.class==student.class){
            printf("%s - %d/%d/%d - %c - %s - %s - %s\n", aux->student.name, aux->student.birthday.day,aux->student.birthday.month,aux->student.birthday.year, aux->student.class,aux->student.year, aux->student.registration, aux->student.balance);
            x=1;
        }
        aux = aux->next;
    }
    if(x==0) {
        printf("No students of this class in the system! \n");
    }
}