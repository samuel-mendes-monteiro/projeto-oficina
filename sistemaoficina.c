#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>


/// STRUCT-VEICULO///
typedef struct {


    char modelo[50];
    int ano;
    char placa[15];
    int trocaoleo;
    int km_ultimarev;
    int km_atual;
}Veiculo;

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
    printf("0 - Sair\n");

    scanf("%d",&n);

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
    fgets(v.modelo,50,stdin);
    v.modelo[strcspn(v.modelo, "\n")] = '\0';

    printf("Digite o ano do carro:\n");
    scanf("%d",&v.ano);

    getchar();

    printf("Digite a placa do carro:\n");
    fgets(v.placa,15,stdin);
    v.placa[strcspn(v.placa, "\n")] = '\0';

    ///SE DIGITAR LETRA MINUSCULA TRANSFORMA EM MAISCULA///
    int Q = strlen(v.placa);
    for (int i = 0; i < Q; i++)
    {
        if (islower(v.placa[i]))
        {
            v.placa[i] = toupper(v.placa[i]);
        }
        
    }

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
    getchar();
    fgets(placateste,15,stdin);
    placateste[strcspn(placateste, "\n")] = '\0';

    ///SE DIGITAR LETRA MINUSCULA TRANSFORMA EM MAISCULA///
    int Q = strlen(placateste);
    for (int i = 0; i < Q; i++)
    {
        if (islower(placateste[i]))
        {
            placateste[i] = toupper(placateste[i]);
        }
    }

    while(fscanf(F,"%s %d %s %d %d %d",v.modelo, &v.ano, v.placa,&v.trocaoleo,&v.km_ultimarev,&v.km_atual)!=EOF){

        if(strcmp(v.placa,placateste) == 0){

            printf("\n=== VEICULO ENCONTRADO ===\n");
            printf("Modelo: %s\n", v.modelo);
            printf("Ano: %d\n", v.ano);
            printf("Placa: %s\n", v.placa);
            if (v.trocaoleo == 1)
            {
                printf("Precisa trocar oleo\n");
            }else printf("Nao precisa trocar oleo\n");
            printf("KM ultima revisao: %d\n", v.km_ultimarev);
            printf("KM atual: %d\n", v.km_atual);
            printf("\n");
            printf("\n");
            printf("\n");
            encontrado = 1;

            break;
        }
        
    }
    if (encontrado == 0)
    {
        printf("\n Veiculo com placa %s nao encontrado\n", placateste);
    }

    fclose(F);
}
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
            break;
        case 3:
            adicionarveiculo();
            break;
        case 4:
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