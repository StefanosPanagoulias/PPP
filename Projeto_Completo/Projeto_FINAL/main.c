//
// Created by Kevin Dourado on 04/05/22.
//
#include <stdio.h>
#include "Cadastro.h"
int main(){
    aLista lista;
    Cadastro aluno;
    lista=cria();
    int option;int x;
    percorre_alunos(lista); //Chama a função percorre já para carregar a lista dos alunos com os dados dos ficheiros
    percorre_despesas(lista);
    option=menu();
    while(option!=10){
        if(option==1){ //Função para intruzir um aluno na lista
            aLista atual,ant;
            insere_nome(&aluno);
            insere_data(&aluno);
            insere_ano(&aluno);
            insere_turma(&aluno);
            insere_matricula(&aluno);
            procura_ma(lista,aluno,&ant,&atual);
            insere_saldo(&aluno);
            aluno.ptr=cria_despesa();
            if(atual!=NULL){
                printf("Aluno ja foi adicionado!\n");
            }
            else {
                insere(lista, aluno);
                escreve_aluno(lista);
            }
        }
        if(option==2){ //Função para eliminar um aluno
            insere_matricula(&aluno);
            elimina(lista,aluno);
            escreve_despesa(lista);
            escreve_aluno(lista);
        }
        if(option==3){ //Imprimir a lista em ordem alfabética
            imprime_aluno(lista);

        }
        if(option==4){ //Imprimir a lista em ordem decrescente a partir de um determinado saldo
            lSaldos lista_abaixo=cria_saldo();
            ordena_saldo_abaixo(lista_abaixo,lista);
            imprime_lista_saldos(lista_abaixo);
            lista_abaixo=destroi_saldos(lista_abaixo);
        }
        if(option==5){ //Apresenta os dados de um determinado aluno
            insere_matricula(&aluno);
            apresenta(lista,aluno);
        }
        if(option==6){ //EFETUAR UMA DESPESA POR UM DETERMINADO ALUNO.
            carrega_despesa(lista);
            escreve_despesa(lista);
            escreve_aluno(lista);
        }
        if (option == 7) { //CARREGAR A CONTA DE UM ALUNO COM UM VALOR.
            carrega(lista);
            escreve_aluno(lista);
        }
        if (option == 8) { //LISTAR DE ACORDO COM A TURMA.
            ordenar_turma(lista);
        }
        option=menu();
    }
    lista=destroi(lista); //destroi todos as listas
    printf("Obrigado por acessar o sistema BahiaSP. Volte sempre! <3 <3 \n");
}