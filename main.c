#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


int main(){

    int opcao;

    entrada();

    do {
        
        opcao = menu();

        switch (opcao)
        {
        case 1:
            pesquisarveiculo();
            break;
        case 2:
            editarveiculo();
            break;
        case 3:
            adicionarveiculo();
            break;
        case 4:
            removerveiculo();
            break;
        case 5:
            listarveiculos();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        
        
        default:
            printf("Opcao invalida\n");
        }

        printf("Pressione ENTER para continuar\n");

        getchar();
        getchar();
        printf("\n");

    } while(opcao != 0);

    return 0;
}