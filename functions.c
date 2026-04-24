#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


//TRANSFORMAR EM MAIUSCULO//

void maiusculo(char str[]){


    int Q = strlen(str);
    for (int i = 0; i < Q; i++)
    {

        str[i] = toupper(str[i]);
    }
}

//LER PLACA//

void lerplaca(char placateste[]){

    fgets(placateste,15,stdin);
    placateste[strcspn(placateste, "\n")] = '\0';
    maiusculo(placateste);
}

//LER MODELO//

void lermodelo(char str[]){
    fgets(str,50,stdin);
    str[strcspn(str, "\n")] = '\0';

    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ' '){
            str[i] = '_';
        }
    }
}


//MOSTRAR VEICULO//

void mostrarveiculo(Veiculo v){
    
    printf("\n");
    printf("Modelo: %s\n", v.modelo);
    printf("Ano: %d\n", v.ano);
    printf("Placa: %s\n", v.placa);
    if (v.trocaoleo == 1)
    {
        printf("Precisa trocar oleo\n");
    }else printf("Nao precisa trocar oleo\n");
    printf("KM ultima revisao: %d\n", v.km_ultimarev);
    printf("KM atual: %d\n", v.km_atual);
    if ((v.km_atual - v.km_ultimarev)> 10000)
    {
        printf("REVISAO RECOMENDADA!!\n");
    }
    
    printf("\n");
    
}

//SCANVEICULOS//

int scanveiculos(FILE* F,Veiculo *v){
    return fscanf(F,"%49s %d %14s %d %d %d",v->modelo, &v->ano, v->placa,&v->trocaoleo,&v->km_ultimarev,&v->km_atual);

}

//SALVAVEICULOS//

void salvarveiculo(FILE* F, Veiculo v){

    fprintf(F,"%s %d %s %d %d %d\n",v.modelo, v.ano, v.placa, v.trocaoleo , v.km_ultimarev , v.km_atual);


}

///CABECALHO///

void entrada()
{
    printf("*****************************\n");
    printf("Sistema de Gestão de veículos\n");
    printf("*****************************\n");

    time_t t;
    struct tm *info;
    time(&t);                
    info = localtime(&t);

    printf("\n");    
    printf("Hora: %02d:%02d:%02d\n",info->tm_hour,info->tm_min,info->tm_sec);
    printf("\n");
    printf("Data: %02d/%02d/%04d\n",info->tm_mday,info->tm_mon + 1,info->tm_year+1900);

}

///MENU///

int menu()
{
    int n;
    printf("O que deseja?\n");
    printf("1 - Pesquisar veiculo.\n");
    printf("2 - Editar status de veiculo.\n");
    printf("3 - Adicionar Veiculo.\n");
    printf("4 - Remover veiculo.\n");
    printf("5 - Listar os veiculos\n");
    printf("0 - Sair\n");
    
    scanf("%d",&n);
    getchar();
    return n;


}

///ADICIONARVEICULO///

void adicionarveiculo()
{
    Veiculo v;
    
    FILE* F = fopen("banco-de-dados-oficina.txt","a");

    if (F == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }
    

    getchar();

    printf("Digite o modelo do carro\n");
    lermodelo(v.modelo);

    printf("Digite o ano do carro:\n");
    scanf("%d",&v.ano);

    getchar();

    printf("Digite a placa do carro:\n");
    lerplaca(v.placa);

    printf("O carro precisa trocar o oleo?\n");
    printf("0- Nao   1 - Sim\n");
    scanf("%d",&v.trocaoleo);

    printf("Digite a quilometragem da ultima revisao e a atual:\n");
    scanf("%d %d",&v.km_ultimarev,&v.km_atual);
    getchar();

    fprintf(F, "%s %d %s %d %d %d\n",v.modelo, v.ano, v.placa,v.trocaoleo, v.km_ultimarev, v.km_atual);


    fclose(F);

    printf("\nVEICULO CADASTRADO!\n\n");

}

/// PESQUISARVEICULO///

void pesquisarveiculo(){
    Veiculo v;
    char placateste[15];
    int encontrado = 0;
    FILE* F = fopen("banco-de-dados-oficina.txt","r");

    if (F == NULL) {
    printf("Nenhum veiculo cadastrado.\n");
    return;
    }

    printf("Digite a placa:\n");
    lerplaca(placateste);
    

    while(scanveiculos(F,&v) == 6){

        if(strcmp(v.placa,placateste) == 0){

            printf("\n=== VEICULO ENCONTRADO ===\n");
            mostrarveiculo(v);
            encontrado = 1;

            break;
        }
        
    }
    if (!encontrado)
    {
        printf("\n Veiculo com placa %s nao encontrado\n", placateste);
    }

    fclose(F);
}

/// REMOVERVEICULO///

void removerveiculo(){

    Veiculo v;
    char placateste[15];
    int encontrado = 0;

    FILE* F = fopen("banco-de-dados-oficina.txt","r");
    FILE* temp = fopen("temp.txt","w");

    if (F == NULL || temp == NULL){
    printf("Erro ao abrir arquivo.\n");
    return;
}

    printf("Digite a placa que deseja remover:\n");
    lerplaca(placateste);

        while(scanveiculos(F,&v) == 6){

        if (strcmp(placateste, v.placa) == 0)
        {
            encontrado = 1;
        }else
        {
            salvarveiculo(temp,v);
        }

        }

        if (encontrado)
        printf("\n Veiculo removido com sucesso!\n");
        else
        printf("\n Veiculo nao encontrado.\n");

        fclose(F);
        fclose(temp);

        remove("banco-de-dados-oficina.txt");
        rename("temp.txt","banco-de-dados-oficina.txt");

    }

///EDITAR VEICULO///

void editarveiculo(){

    FILE* F = fopen("banco-de-dados-oficina.txt","r");
    FILE* temp = fopen("temp.txt","w");
    if (F == NULL || temp == NULL){
    printf("Erro ao abrir arquivo.\n");
    return;
}
    Veiculo v;
    int encontrado = 0;
    char placateste[15];


    printf("Digite a placa que quer atualizar:\n");
    lerplaca(placateste);


            while(scanveiculos(F,&v) == 6){
        
            if (strcmp(placateste,v.placa) == 0)
            {
                encontrado = 1;
                printf("\n=== EDITANDO VEICULO ===\n");

                 printf("Novo modelo:\n");
                
                lermodelo(v.modelo);

                printf("Novo ano:\n");
                scanf("%d",&v.ano);

                printf("Troca de oleo 0 - nao // 1 - sim:\n");
                scanf("%d",&v.trocaoleo);

                printf("KM ultima revisao e atual:\n");
                scanf("%d %d",&v.km_ultimarev,&v.km_atual);
            }
                salvarveiculo(temp,v);

        }
        if (encontrado)
        printf("\nVeiculo atualizado com sucesso!\n");
        else
        printf("\nVeiculo nao encontrado.\n");
            fclose(F);
            fclose(temp);

        remove("banco-de-dados-oficina.txt");
        rename("temp.txt","banco-de-dados-oficina.txt");
        }
    
///LISTAR VEICULO///

void listarveiculos(){

    FILE* F = fopen("banco-de-dados-oficina.txt","r");

    if (F == NULL){
    printf("Nenhum veiculo cadastrado.\n");
    return;
}
    Veiculo v;
    while (scanveiculos(F,&v) == 6)
    {
        mostrarveiculo(v);
    }
    fclose(F);
}

