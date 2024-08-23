//
// Created by Kevin Dourado on 04/05/22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Cadastro.h"
void imprime_despesa(Ldespesas lista){ //Imprime a lista de despesa
    Ldespesas aux = lista->prox;
    while(aux!=NULL){
        printf("DATA: %d/%d/%d - DES: %s - VALOR: %lf \n",aux->DespesaAluno.dia.dia,aux->DespesaAluno.dia.mes,aux->DespesaAluno.dia.ano,aux->DespesaAluno.descricao,aux->DespesaAluno.valor);
        aux=aux->prox;
    }
}
Ldespesas cria_despesa() { //Cria a lista de despesa
    Ldespesas aux;
    Nodespesa a1={0,0,0,0," "};
    aux = (Ldespesas ) malloc(sizeof(despesa));
    if (aux != NULL) {
        aux->DespesaAluno=a1;
        aux->prox = NULL;
    }
    return aux;
}

void procura_despesa(Ldespesas lista,Nodespesa chave,Ldespesas *ant, Ldespesas *atual){ //Função feita para ordenar a lista de despesa por ordem crescente
    *ant=lista;
    *atual=lista->prox;
    while ((*atual)!= NULL && (*atual)->DespesaAluno.valor-chave.valor<0){
        *ant = *atual;
        *atual=(*atual)->prox;
    }
}
void insere_despesa(Ldespesas lista,Nodespesa a1){ //Insere as despesas na lista de despesas
    Ldespesas no, ant, atual;
    no=(Ldespesas) malloc(sizeof(despesa));
    if(no!=NULL){
        no->DespesaAluno=a1;
        procura_despesa(lista,a1,&ant,&atual);
        no->prox=ant->prox;
        ant->prox=no;
    }
}

void carrega_despesa(aLista lista){ //Carrega os dados inserido pelo console e suas determinadas variáveis
    Nodespesa chave;
    aLista ant, atual;
    Cadastro aux;
    int func=1;
    while(func) {
        insere_matricula(&aux);
        procura_ma(lista, aux, &ant, &atual);
        if (atual != NULL) {
            insere_data_despesa(&chave);
            insere_descricao(&chave);
            insere_valor_despesa(&chave);
            if(chave.valor<= strtod(atual->aluno.saldo,NULL)) {
                insere_despesa(atual->aluno.ptr, chave);
                double x=strtod(atual->aluno.saldo,NULL);
                x-=chave.valor;
                snprintf(atual->aluno.saldo,50,"%lf",x);
                func = 0;
            }
            else{
                printf("saldo insuficiente\n");
                func=0;
            }
        }
        else {
            printf("Aluno nao encontrado! \n");
            func=1;
        }
    }
}
int prot_saldo(Cadastro *chave){ //Função feita para proteger os dados inseridos no console
    int x=0;
    for(int i=0;chave->saldo[i]!='\0';i++){
        if(isdigit(chave->saldo[i]) && strtod(chave->saldo,NULL)>=0){
            x=1;
        }
    }
    return x;
}
aLista cria() { // Cria a lista dos alunos
    aLista aux;
    Cadastro a1={" ",0,0,0,' '," "};
    aux = (aLista ) malloc(sizeof(alunos));
    if (aux != NULL) {
        aux->aluno=a1;
        aux->prox = NULL;
    }
    return aux;
}
void procura_sal(lSaldos lista,Cadastro chave,lSaldos *ant, lSaldos *atual){ //Função feita para ordenar a lista dos saldos abaixo de forma decrescente
    *ant=lista;
    *atual=lista->prox;
    while ((*atual)!= NULL && strcmp((*atual)->aluno.saldo,chave.saldo)>0){
        *ant = *atual;
        *atual=(*atual)->prox;
    }
}
lSaldos cria_saldo() { //Cria a lista dos saldos abaixo
    lSaldos aux;
    Cadastro a1={" ",0,0,0,' '," "};
    aux = (lSaldos ) malloc(sizeof(alunos));
    if (aux != NULL) {
        aux->aluno=a1;
        aux->prox = NULL;
    }
    return aux;
}
void insere_saldo(Cadastro *chave){ //Função feita para inserir valor na variável saldo dentro da estrutura Cadastro
    int aux=1;
    while(aux){
        printf("Insira o saldo:");
        scanf(" %[^\n]s",chave->saldo);
        if(prot_saldo(chave)==0){
            printf("Tente novamente!\n");
        }
        else(aux=0);
    }
}
void imprime_lista_saldos(lSaldos lista){ //Função que imprime a lista dos saldos abaixos
    lSaldos aux = lista->prox;
    while(aux!=NULL){
        printf("%s - %d/%d/%d - %c - %s - %s - %s\n",aux->aluno.nome,aux->aluno.aniversario.dia,aux->aluno.aniversario.mes,aux->aluno.aniversario.ano,aux->aluno.turma,aux->aluno.ano,aux->aluno.matricula,aux->aluno.saldo);
        printf("Despesas do aluno:\n");
        imprime_despesa(aux->aluno.ptr);
        aux=aux->prox;
    }
}
void insere_saldo_abaixo(lSaldos lista,Cadastro a1){ //Função feita para inserir dados na lista dos saldos abaixo
    lSaldos no, ant, atual;
    no=(lSaldos) malloc(sizeof(saldos));
    if(no!=NULL){
        no->aluno=a1;
        procura_sal(lista,a1,&ant,&atual);
        no->prox=ant->prox;
        ant->prox=no;
    }
}
void ordena_saldo_abaixo(lSaldos lista, aLista lista_alunos){ //Função feita para chamar as subfunções e ordenar a lista dos saldos a partir de um determinado valor
    aLista aux = lista_alunos->prox;
    Cadastro saldo;
    int x;
    double valor;
    insere_saldo(&saldo);
    valor= strtod(saldo.saldo,NULL);
    while(aux!=NULL){
        if(strtod(aux->aluno.saldo,NULL)<valor){
            insere_saldo_abaixo(lista,aux->aluno);
            x=1;
        }
        aux=aux->prox;
    }
    if(x==0){
        printf("Nenhuma conta possui saldo abaixo de %s",saldo.saldo);
    }
}

void insere(aLista lista,Cadastro a1){ //Função feita para inserir alunos na lista dos alunos
    aLista no, ant, atual;
    no=(aLista) malloc(sizeof(alunos));
    if(no!=NULL){
        no->aluno=a1;
        procura(lista,a1,&ant,&atual);
        no->prox=ant->prox;
        ant->prox=no;
    }
}
int vazia(aLista lista){
    if(lista->prox==NULL){
        return 1;
    }
    else return 0;
}
int vazia_saldos(lSaldos lista){
    if(lista->prox==NULL){
        return 1;
    }
    else return 0;
}
int vazia_despesas(Ldespesas lista){
    if(lista->prox==NULL){
        return 1;
    }
    else return 0;
}
Ldespesas destroi_despesa(Ldespesas lista){
    Ldespesas temp_ptr;
    while (!vazia_despesas(lista)) {
        temp_ptr=lista;
        lista = lista->prox;
        free(temp_ptr);
    }
    free(lista);
    return NULL;
}
aLista destroi(aLista lista){
    aLista temp_ptr;
    while (!vazia(lista)) {
        temp_ptr=lista->prox;
        temp_ptr->aluno.ptr=destroi_despesa(temp_ptr->aluno.ptr);
        free(lista);
        lista=lista->prox;
    }
    free(lista);
    return NULL;
}

lSaldos destroi_saldos (lSaldos lista){
    lSaldos temp_ptr;
    while (!vazia_saldos (lista)) {
        temp_ptr = lista;
        lista = lista->prox;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

void procura(aLista lista,Cadastro chave,aLista *ant, aLista *atual){ //função feita para ordenar a lista dos alunos de ordem alfabética
    *ant=lista;
    *atual=lista->prox;
    while ((*atual)!= NULL && strcmp((*atual)->aluno.nome,chave.nome)<0){
        *ant = *atual;
        *atual=(*atual)->prox;
    }
    if ((*atual)!=NULL && strcmp((*atual)->aluno.nome,chave.nome)!=0){
        *atual=NULL;
    }
}
void imprime_aluno(aLista lista){ //Função que imprime a lista dos alunos
    aLista aux = lista->prox;
    while(aux!=NULL){
        printf("%s - %d/%d/%d - %c - %s - %s - %s\n",aux->aluno.nome,aux->aluno.aniversario.dia,aux->aluno.aniversario.mes,aux->aluno.aniversario.ano,aux->aluno.turma,aux->aluno.ano,aux->aluno.matricula,aux->aluno.saldo);
        printf("Despesas do aluno:\n");
        imprime_despesa(aux->aluno.ptr);
        aux=aux->prox;
    }
}
int menu(){ //Menu principal do programa
    int x;
    char aux[20];
    printf("\t\t\t\t MENU PRINCIPAL:\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("|[OPCAO 01] = INTRODUZIR DADOS DE UM NOVO ALUNO.\n");
    printf("|[OPCAO 02] = ELIMINAR UM ALUNO EXISTENTE.\n");
    printf("|[OPCAO 03] = LISTAR TODOS OS ALUNOS POR ORDEM ALFABETICA.\n");
    printf("|[OPCAO 04] = LISTAR ALUNOS OS ALUNOS COM SALDO ABAIXO DE UM DETERMINADO VALOR.\n");
    printf("|[OPCAO 05] = APRESENTAR TODA A INFORMACAO DE UM DETERMINADO ALUNO.\n");
    printf("|[OPCAO 06] = EFETUAR UMA DESPESA POR UM DETERMINADO ALUNO.\n");
    printf("|[OPCAO 07] = CARREGAR A CONTA DE UM ALUNO COM UM VALOR.\n");
    printf("|[OPCAO 08] = LISTAR DE ACORDO COM A TURMA.\n");
    printf("|[OPCAO 10] = FINALIZAR EXECUCAO DO PROGRAMA.\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("\t\t\tINSIRA A FUNCAO QUE DESEJA: ");scanf("%s",aux);
    if(strlen(aux)<2 ){
        for(int i=0;i< strlen(aux)-1;i++){
            if(!isdigit(aux[i])){
                printf("Opcao foi invalida! \n");
                return x=0;
            }
        }
    }
    if(atoi(aux)>=1 && atoi(aux)<=10) {
        x = atoi(aux);
        return x;
    }
    else
        printf("Opcao foi invalida! \n");
    return x=0;
}
void procura_ma(aLista lista,Cadastro chave,aLista *ant, aLista *atual){ //Função que procura o aluno de acordo com a sua matrícula
    *ant=lista;
    *atual=lista->prox;
    while ((*atual)!= NULL && strcmp(chave.matricula,(*atual)->aluno.matricula)!=0){
        *ant = *atual;
        *atual=(*atual)->prox;
    }
    if ((*atual)!=NULL && strcmp(chave.matricula,(*atual)->aluno.matricula)!=0){
        *atual=NULL;
    }
}
void elimina (aLista lista, Cadastro chave){ //Função feita para eliminar um aluno da lista
    aLista ant, actual;
    procura_ma (lista, chave, &ant, &actual);
    if (actual != NULL) {
        ant->prox = actual->prox;
        free (actual);
        actual->aluno.ptr=destroi_despesa(actual->aluno.ptr);
    }
    else{
        printf("Aluno nao encontrado");
    }
}

aLista apresenta(aLista lista, Cadastro chave){ // Função feita para mostrar um aluno no console de acordo com a sua matrícula
    aLista ant, atual;
    procura_ma (lista, chave, &ant, &atual);
    if(atual==NULL){
        printf("Aluno nao encontrado!\n");
    }
    else{
        printf("%s - %d/%d/%d - %c - %s - %s - %s\n",atual->aluno.nome,atual->aluno.aniversario.dia,atual->aluno.aniversario.mes,atual->aluno.aniversario.ano,atual->aluno.turma,atual->aluno.ano,atual->aluno.matricula,atual->aluno.saldo);
        printf("Despesas do aluno:\n");
        imprime_despesa(atual->aluno.ptr);
    }
    return atual;
}
int prot_ano(Cadastro *aluno){ //Função feita para proteger os dados inseridos no console
    char ano[10];
    int x;
    strcpy(ano,aluno->ano);
    for (int i=0; ano[i]!='\0';i++){
        if (!isdigit(ano[i])) {
            return 0;
        }
    }
    if(atoi(ano)>=1 && atoi(ano)<=12) {
        return 1;
    }
    else return 0;
}
void insere_ano(Cadastro *aluno){ //Função feita para inserir valor na variável ano dentro da estrutura Cadastro
    int aux=1;
    while(aux) {
        printf("Insira o ano letivo: \n");
        scanf(" %[^\n]s", aluno->ano);
        if (prot_ano(aluno) == 0) {
            printf("Tente novamente!\n");
        }
        else aux=0;
    }
}
int prot_nome(Cadastro *chave){ //Função feita para proteger os dados inseridos no console
    int x = 0;
    char alfabeto_maisculas[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q','R', 'S','T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alfabeto_minusculas[26] = {'a','b', 'c', 'd','e','f','g','h','i','j', 'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<26;i++){
        if(chave->nome[0]==alfabeto_maisculas[i]){
            x=1;
        }
    }
    if(x==1) {
        for (int i = 1; chave->nome[i] != '\0'; i++) {
            for (int k = 0; k < 26; k++) {
                if (strlen(chave->nome) > 1 && (chave->nome[i]) == (alfabeto_minusculas[k])) {
                    x = 1;
                }
                if(chave->nome[i]==' ')return 0;
            }
        }
    }
    return x;
}
int prot_sobrenome(char str[]) { //Função feita para proteger os dados inseridos no console
    int x = 0;
    char alfabeto_maisculas[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q','R', 'S','T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char alfabeto_minusculas[26] = {'a','b', 'c', 'd','e','f','g','h','i','j', 'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    for(int i=0;i<26;i++){
        if(str[0]==alfabeto_maisculas[i]){
            x=1;
        }
    }
    if(x==1) {
        for (int i = 1; str[i] != '\0'; i++) {
            for (int k = 0; k < 26; k++) {
                if (strlen(str) > 1 && (str[i]) == (alfabeto_minusculas[k])) {
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
void insere_nome(Cadastro *chave){ //Função feita para inserir valor na variável nome dentro da estrutura Cadastro
    int aux=1;
    char sobrenome[20];
    while(aux){
        printf("Insira o nome: \n");
        scanf(" %[^\n]s",chave->nome);
        printf("Insira o seu sobrenome: \n");
        scanf(" %[^\n]s",sobrenome);
        if((prot_nome(chave))==0 || (prot_sobrenome(sobrenome))==0){
            printf("Tente novamente!\n");
            aux=1;
        }
        else {
            strcat(chave->nome, " ");
            strcat(chave->nome, sobrenome);
            aux = 0;
        }
    }
}
int prot_matricula(Cadastro *aluno){ //Função feita para proteger os dados inseridos no console
    int x = 0;
    for (int i = 0; aluno->matricula[i] != '\0'; i++) {
        if (isdigit(aluno->matricula[i]) && strlen(aluno->matricula)==10){
            x=1;
        }
    }
    return x;
}
void insere_matricula(Cadastro *chave){ //Função feita para inserir valor na variável matricula dentro da estrutura Cadastro
    int aux=1;
    while(aux){
        printf("Insira a matricula:\n");
        scanf(" %[^\n]s",chave->matricula);
        if(prot_matricula(chave)==0){
            printf("Tente novamente!\n");
            aux=1;
        }
        else(aux=0);
    }
}

void carrega(aLista lista){ //Função feita para carregar saldo na conta de um determinado aluno
    Cadastro chave;
    aLista ant, atual;
    double aux,aux2=-1;
    while(aux2<0) {
        insere_matricula(&chave);
        insere_saldo(&chave);
        procura_ma(lista, chave, &ant, &atual);
        if (atual != NULL && strtod(chave.saldo, NULL)>0) {
            aux = strtod(atual->aluno.saldo, NULL) + strtod(chave.saldo, NULL);
            snprintf(atual->aluno.saldo, 50, "%.2lf", aux);
            aux2=1;
        } else if(atual==NULL){
            printf("Aluno nao encontrado! \n");
        }
        else{
            printf("O saldo nao foi inserido corretamente\n");
        }
    }
}
int prot_data(Data aniversario){ //Função feita para proteger os dados inseridos no console
    if ((aniversario.mes==1|| aniversario.mes==3||aniversario.mes==5||aniversario.mes==7||aniversario.mes==8||aniversario.mes==10||aniversario.mes==12) && aniversario.dia>=1 && aniversario.dia<=31){
        return 1;
    }
    if(((aniversario.mes==2 && aniversario.ano % 100!=0 && aniversario.ano%4==0) || aniversario.ano%400==0) && aniversario.dia>=1 && aniversario.dia<=29) {
        return 1;
    }
    else if(aniversario.mes==2 && (aniversario.dia>=1 && aniversario.dia<=28)){
        return 1;
    }

    if (((aniversario.mes==4|| aniversario.mes==6||aniversario.mes==9||aniversario.mes==11)&& aniversario.dia>=1 && aniversario.dia<=30)){
        return 1;
    }
    return 0;
}
int prot_data_aluno(char chave[]){ //Função feita para proteger os dados inseridos no console
    int x;
    int i=0;
    for(i;chave[i]!='\0';i++){
        if(isdigit(chave[i]) && strtod(chave,NULL)>=1){
            x=1;
        }
        else if(chave[i]!='\0'){
            x=0;
        }
    }
    return x;
}
void insere_data(Cadastro *chave) { //Função feita para inserir valor na variável aniversario dentro da estrutura Cadastro/Data
    int aux = 1;
    char dia[3];
    char mes[3];
    char ano[5];
    while (aux) {
        printf("Insira o dia: \n");
        scanf(" %[^\n]s", dia);
        printf("Insira o mes: \n");
        scanf(" %[^\n]s", mes);
        printf("Insira o ano: \n");
        scanf(" %[^\n]s", ano);
        if (prot_data_aluno(ano) && prot_data_aluno(dia) && prot_data_aluno(mes)) {
            chave->aniversario.mes = atoi(mes);
            chave->aniversario.dia = atoi(dia);
            chave->aniversario.ano = atoi(ano);
            if (prot_data(chave->aniversario) == 1) {
                aux = 0;
            }
            else {
                printf("Tente novamente!\n");
                aux=1;
            }
        }
        else {
            printf("Tente novamente!\n");
            aux=1;
        }
    }
}
void insere_data_despesa(Nodespesa *chave){ //Função feita para inserir valor na variável dia dentro da estrutura Nodespesa/Data
    int aux = 1;
    char dia[3];
    char mes[3];
    char ano[5];
    while (aux==1) {
        printf("Insira o dia: \n");
        scanf(" %[^\n]s", dia);
        printf("Insira o mes: \n");
        scanf(" %[^\n]s", mes);
        printf("Insira o ano: \n");
        scanf(" %[^\n]s", ano);
        if (prot_data_aluno(ano) && prot_data_aluno(dia) && prot_data_aluno(mes)) {
            chave->dia.mes = atoi(mes);
            chave->dia.dia = atoi(dia);
            chave->dia.ano = atoi(ano);
            if (prot_data(chave->dia) == 1) {
                aux = 0;
            } else {
                printf("Tente novamente!\n");
                aux=1;
            }
        }
        else {
            printf("Tente novamente!\n");
            aux=1;
        }
    }
}
int prot_descricao(Nodespesa *chave){ //Função feita para proteger os dados inseridos no console
    int x = 0;
    char alfabeto[53] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J',
                         'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's',
                         'T', 't', 'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z',' '};
    for (int i = 0; chave->descricao[i] != '\0'; i++) {
        for (int k = 0; k < 53; k++) {
            if (strlen(chave->descricao)>1 && (chave->descricao[i]) == (alfabeto[k])) {
                x = 1;
            }
        }
    }
    return x;
}

void insere_descricao(Nodespesa *chave){ //Função feita para inserir valor na variável descrição dentro da estrutura Nodespesa
    int aux=1;
    while(aux){
        printf("Insira a descricao da compra: ");
        scanf(" %[^\n]s",chave->descricao);
        if(prot_descricao(chave)==0){
            printf("Tente novamente!\n");
            aux=1;
        }
        else(aux=0);
    }
}
int prot_valor_despesa(char aux[]){ //Função feita para proteger os dados inseridos no console
    int x=0;
    for(int i=0;aux[i]!='\0';i++){
        if(isdigit(aux[i]) && strtod(aux,NULL)>=0){
            x=1;
        }
    }
    return x;
}
void insere_valor_despesa(Nodespesa *chave){ //Função feita para inserir valor na variável valor dentro da estrutura Nodespesa
    int aux=1;
    char aux2[50];
    while(aux){
        printf("Insira o valor da compra:");
        scanf(" %[^\n]s",aux2);
        if(prot_valor_despesa(aux2)==0){
            printf("Tente novamente!\n");
            aux=1;
        }
        else{
            chave->valor= strtod(aux2,NULL);
            aux=0;
        }
    }
}
void escreve_aluno(aLista lista){ //Função feita para escrever a lista dos alunos no ficheiro
    FILE *f;
    f=fopen("AlunosCadastrados.txt", "w");
    aLista aux = lista->prox;
    while(aux!=NULL){
        fprintf(f,"%s - %d/%d/%d - %c - %s - %s - %s",aux->aluno.nome,aux->aluno.aniversario.dia,aux->aluno.aniversario.mes,aux->aluno.aniversario.ano,aux->aluno.turma,aux->aluno.ano,aux->aluno.matricula,aux->aluno.saldo);
        fprintf(f,"\n");
        aux=aux->prox;
    }
    fclose(f);
}

void escreve_despesa(aLista lista){ //Função feita para escrever a lista das despesas no ficheiro
    FILE *f;
    f= fopen("Despesas.txt", "w");
    aLista aux = lista->prox;
    while(aux!=NULL){
        Ldespesas despesa= aux->aluno.ptr->prox;
        while(despesa!=NULL) {
            fprintf(f, "%s - %d/%d/%d - %s - %.2lf",despesa->DespesaAluno.descricao ,despesa->DespesaAluno.dia.dia, despesa->DespesaAluno.dia.mes,despesa->DespesaAluno.dia.ano,aux->aluno.matricula, despesa->DespesaAluno.valor);
            fprintf(f,"\n");
            despesa=despesa->prox;
        }
        aux = aux->prox;
    }
    fclose(f);
}
void percorre_data(aLista lista, Cadastro *aluno, const char linha[]){ //Percorre o ficheiro e carrega os valores da data na lista dos alunos
    int contador=0;
    int aux=0;
    int aux2=0;
    int aux3=0;
    int aux4=0;
    char dia[3];
    char mes[3];
    char ano[5];
    for(int i=0;linha[i]!='\0';i++) {
        if (linha[i] == '-'){
            contador++;
        }
        if (linha[i] == '/'){
            aux2++;

        }
        if(contador==1){
            if(aux2==1 && linha[i]!='/'){
                mes[aux3]=linha[i];
                aux3++;
            }
            if(aux2==2 && linha[i]!= '/' && linha[i]!= ' ' && linha[i]!= '\n'){
                ano[aux4]=linha[i];
                aux4++;
            }
            if(linha[i]!='-' && linha[i]!=' ' && linha[i]!='/' && aux2==0) {
                dia[aux] = linha[i];
                aux++;
            }
        }
    }
    aluno->aniversario.dia= atoi(dia);
    aluno->aniversario.mes= atoi(mes);
    aluno->aniversario.ano= atoi(ano);
}
void percorre_nome(aLista lista, Cadastro *aluno,const char linha[]){ ////Percorre o ficheiro e carrega os valores do nome na lista dos alunos
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
            aluno->nome[i]=linha[i];
        }
    }
    aluno->nome[i]='\0';
    //printf("%s\n",aluno->nome);
}

void percorre_turma(aLista lista, Cadastro *aluno, const char linha[]){ //Percorre o ficheiro e carrega os valores da turma na lista dos alunos
    int contador=0;
    for(int i=0; linha[i]!='\0';i++) {
        if(linha[i]=='-'){
            contador++;
        }
        if(contador==2 && linha[i]!= '-' && linha[i]!=' ' && linha[i]!= '\n'){
            aluno->turma=linha[i];
        }
    }
}
void percorre_ano(aLista lista, Cadastro *aluno, const char linha[]){ //Percorre o ficheiro e carrega os valores da ano na lista dos alunos
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
    strcpy(aluno->ano, aux);
}
void percorre_matricula(aLista lista, Cadastro *aluno, const char linha[]) { //Percorre o ficheiro e carrega os valores da matricula na lista dos alunos
    int contador = 0;
    int x=0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==4 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            aluno->matricula[x] = linha[i];
            x++;
        }
    }
    aluno->matricula[x]='\0';
}
void percorre_saldo(aLista lista, Cadastro *aluno, const char linha[]) { //Percorre o ficheiro e carrega os valores da data na lista dos alunos
    int contador = 0;
    int x=0;
    char saldo[20];
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==5 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            saldo[x] = linha[i];
            x++;
        }
    }
    saldo[x]='\0';
    strcpy(aluno->saldo, saldo);
}
void percorre_matricula_despesa(Cadastro *aluno, const char linha[]) { ////Percorre o ficheiro para encontrar a matricula do aluno que vai ser inserido as despesas
    int contador = 0;
    int x=0;
    for (int i = 0; linha[i] != '\0'; i++) {
        if (linha[i] == '-') {
            contador++;
        }
        if(contador==2 && linha[i]!='-' && linha[i]!=' ' && linha[i]!= '\n') {
            aluno->matricula[x] = linha[i];
            x++;
        }
    }
}
void percorre_data_despesa(Nodespesa *aluno, const char linha[]){ //Percorre o ficheiro e carrega os valores da data na lista das despesas
    int contador=0;
    int aux=0;
    int aux2=0;
    int aux3=0;
    int aux4=0;
    char dia[3];
    char mes[3];
    char ano[5];
    for(int i=0;linha[i]!='\0';i++) {
        if (linha[i] == '-'){
            contador++;
        }
        if (linha[i] == '/'){
            aux2++;

        }
        if(contador==1){
            if(aux2==1 && linha[i]!='/'){
                mes[aux3]=linha[i];
                aux3++;
            }
            if(aux2==2 && linha[i]!= '/' && linha[i]!= ' ' && linha[i]!= '\n'){
                ano[aux4]=linha[i];
                aux4++;
            }
            if(linha[i]!='-' && linha[i]!=' ' && linha[i]!='/' && aux2==0) {
                dia[aux] = linha[i];
                aux++;
            }
        }
    }
    aluno->dia.dia= atoi(dia);
    aluno->dia.mes= atoi(mes);
    aluno->dia.ano= atoi(ano);
}
void percorre_descricao_despesa(Nodespesa *aluno,const char linha[]){ //Percorre o ficheiro e carrega os valores da descrição na lista das despesas
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
    strcpy(aluno->descricao,aux);
}
void percorre_valor_despesa(Nodespesa *aluno, const char linha[]) { //Percorre o ficheiro e carrega os valores do valor na lista das despesas
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
    aluno->valor= strtod(aux,NULL);
}
void percorre_despesas(aLista lista){ //Chama todas as subfunções e com resultado final adiciona todos os dados na lista das despesas
    FILE *file;
    aLista ant, atual;
    file= fopen("Despesas.txt", "r");
    char linha[150];
    while( fgets (linha, 150, file)!=NULL ) {
        Nodespesa chave={0,0,0,0," "};
        Cadastro aluno={"",0,0,0,' '," "," "};
        percorre_matricula_despesa(&aluno, linha);
        percorre_data_despesa(&chave, linha);
        percorre_descricao_despesa(&chave, linha);
        percorre_valor_despesa(&chave, linha);
        procura_ma(lista, aluno, &ant, &atual);
        if (atual != NULL) {
            insere_despesa(atual->aluno.ptr, chave);
        }
    }
    fclose(file);
}
void percorre_alunos(aLista lista){ ////Chama todas as subfunções e com resultado final adiciona todos os dados na lista dos alunos
    FILE *file;
    file= fopen("AlunosCadastrados.txt", "r");
    char linha[200];
    while( fgets (linha, 200, file)!=NULL ) {
        Cadastro aluno={"",0,0,0,' '," "," "};
        percorre_nome(lista,&aluno, linha);
        percorre_data(lista,&aluno,linha);
        percorre_turma(lista, &aluno, linha);
        percorre_ano(lista, &aluno, linha);
        percorre_matricula(lista, &aluno, linha);
        percorre_saldo(lista, &aluno, linha);
        aluno.ptr=cria_despesa();
        insere(lista, aluno);
    }
    fclose(file);
}

int prot_turma(char str[]) { //Função feita para proteger os dados inseridos no console
    int x = 0;
    char alfabeto[26] = {'A', 'B', 'C','D','E','F','G','H','I', 'J', 'K','L','M','N','O','P','Q','R','S',
                         'T','U','V','W','X','Y','Z'};
    for (int i = 0; i < 25; i++) {
        if ((strlen(str) == 1) && (str[0]) == (alfabeto[i])) {
            x = 1;
        }
    }
    return x;
}
void insere_turma(Cadastro *chave){ //Função feita para inserir valor na variável turma dentro da estrutura Cadastro
    int aux=1;
    char aux2[20];
    while(aux){
        printf("Turma:\n");
        scanf(" %[^\n]s",aux2);
        if(prot_turma(aux2)==0){
            printf("Tente novamente!\n");
        }
        else{
            chave->turma=aux2[0];
            (aux=0);
        }
    }
}
void ordenar_turma(aLista lista){ //Função extra para imprimir todos os alunos de uma determinada turma
    Cadastro aluno;
    insere_turma(&aluno);
    aLista aux = lista->prox;
    int x=0;
    while(aux!=NULL){
        if (aux->aluno.turma==aluno.turma){
            printf("%s - %d/%d/%d - %c - %s - %s - %s\n", aux->aluno.nome, aux->aluno.aniversario.dia,aux->aluno.aniversario.mes,aux->aluno.aniversario.ano, aux->aluno.turma,aux->aluno.ano, aux->aluno.matricula, aux->aluno.saldo);
            x=1;
        }
        aux = aux->prox;
    }
    if(x==0) {
        printf("Nenhum aluno dessa turma no sistema! \n");
    }
}