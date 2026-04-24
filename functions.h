#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>

typedef struct {


    char modelo[50];
    int ano;
    char placa[15];
    int trocaoleo;
    int km_ultimarev;
    int km_atual;
}Veiculo;


void maiusculo(char str[]);
void lerplaca(char placateste[]);
void lermodelo(char str[]);
void mostrarveiculo(Veiculo v);
int scanveiculos(FILE* F,Veiculo *v);
void salvarveiculo(FILE* F, Veiculo v);
void entrada();
int menu();
void adicionarveiculo();
void pesquisarveiculo();
void removerveiculo();
void editarveiculo();
void listarveiculos();




#endif