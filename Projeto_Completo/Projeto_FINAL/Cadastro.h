//
// Created by Kevin Dourado on 04/05/22.
//

#ifndef PROJECT_OF_CADASTRO_H
#define PROJECT_OF_CADASTRO_H

typedef struct Data{ //Estrutura de Dados para data
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Nodespesa{ //Estrutura de Dados para despesa dos alunos
    Data dia;
    double valor;
    char descricao[50];

}Nodespesa;

typedef struct despesa{ //Estrutura de Dados para lista de despesa dos alunos
    Nodespesa DespesaAluno;
    struct despesa *prox;
}despesa;

typedef struct despesa *Ldespesas; // Criando uma variável com ponteiro que aponta para a lista de despesa;

typedef struct Cadastro{ //Estrutura de Dados para cadastro dos alunos
    char nome[50];
    Data aniversario;
    char turma;
    char ano[20];
    char matricula[20];
    char saldo[50];
    despesa *ptr;
}Cadastro;
typedef struct alunos{ //Estrutura de Dados para lista dos alunos
    Cadastro aluno;
    struct alunos *prox;
}alunos;

typedef alunos *aLista; // Criando uma variável com ponteiro que aponta para a lista dos alunos;

typedef struct saldos{ //Estrutura de Dados para lista aux dos saldos abaixo de um desterminado valor
    Cadastro aluno;
    struct saldos *prox;
}saldos;
typedef saldos *lSaldos; // Criando uma variável com ponteiro que aponta para a lista dos saldos;

aLista cria ();
void insere(aLista lista,Cadastro a1);
int vazia(aLista lista);
aLista destroi(aLista lista);
void procura(aLista lista,Cadastro chave,aLista *ant, aLista *atual);
void imprime_aluno(aLista lista);
void procura_ma(aLista lista,Cadastro chave,aLista *ant, aLista *atual);
void elimina (aLista lista, Cadastro chave);
int menu();
aLista apresenta(aLista lista, Cadastro chave);
int prot_ano(Cadastro *aluno);
void insere_ano(Cadastro *aluno);
void saldo_abaixo(aLista lista);
void carrega(aLista lista);
void insere_data(Cadastro *chave);
void insere_nome(Cadastro *chave);
Ldespesas cria_despesa();
void carrega_despesa(aLista lista);
void insere_despesa(Ldespesas lista,Nodespesa a1);
void imprime_despesa(Ldespesas lista);
void insere_data_despesa(Nodespesa *chave);
void insere_descricao(Nodespesa *chave);
void insere_valor_despesa(Nodespesa *chave);
void escreve_aluno(aLista lista);
void escreve_despesa(aLista lista);
void percorre_alunos(aLista lista);
void insere_matricula(Cadastro *chave);
void ordenar_turma(aLista lista);
void insere_turma(Cadastro *chave);
void insere_saldo(Cadastro *chave);
void percorre_despesas(aLista lista);
lSaldos cria_saldo();
void ordena_saldo_abaixo(lSaldos lista, aLista lista_alunos);
void imprime_lista_saldos(lSaldos lista);
lSaldos destroi_saldos(lSaldos lista);


#endif //PROJECT_OF_CADASTRO_H
