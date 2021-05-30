#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct no{
    char nome[50];
    char cpf[20];
    int quantidadeTurista;
    struct no *ProxNo;
}tipoTurista;
//mudei aqui
typedef struct ListaExcursao{
    char nomeExcursao[50];
    char destino[50];
    int numDias;
    struct ListaExcursao *proxExcursao;
    tipoTurista *inicioLista;
}tipoExcursao;
typedef struct Mutilista{
    tipoExcursao *inicio;
    tipoExcursao *fim;
    int quantMultilsta;
}controlMutilista;

void inicializaMultilista(controlMutilista *listaEnc){
     listaEnc->inicio=NULL;
     listaEnc->fim=NULL;
     listaEnc->quantMultilsta = 0;
}
int criarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[50], char destino[50], int Numdias){
    tipoExcursao *novaExcursao;
    novaExcursao = malloc(sizeof(tipoExcursao));
    if(novaExcursao == NULL){
        return 0;
    }
    strcpy(novaExcursao->nomeExcursao, nome);
    strcpy(novaExcursao->destino, destino);
    novaExcursao->numDias = Numdias;
    novaExcursao->proxExcursao = NULL;
    novaExcursao->inicioLista = NULL;
    listaEnc->inicio = novaExcursao;
    listaEnc->fim = novaExcursao;
    listaEnc->quantMultilsta++;

    return 1;
}
int adicionarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[50], char destino[50], int Numdias){
    tipoExcursao *novaExcursao;
     if(listaEnc->inicio == NULL){
        criarExcursao(listaEnc, listaExcursao, nome, destino, Numdias);
    }
    novaExcursao = malloc(sizeof(tipoExcursao));
    if(novaExcursao == NULL){
        return 0;
    }
    strcpy(novaExcursao->nomeExcursao, nome);
    strcpy(novaExcursao->destino, destino);
    novaExcursao->numDias = Numdias;
    novaExcursao->proxExcursao = NULL;
    novaExcursao->inicioLista = NULL;
    listaEnc->fim->proxExcursao= novaExcursao;
    listaEnc->fim = novaExcursao;
    listaEnc->quantMultilsta++;

    return 1;



}
int removerExcursao(char nomeExcursao[50], controlMutilista *listaEnc){
    tipoExcursao *atual, *anterior;
    atual = listaEnc->inicio;

    //remove inicio
    if(strcmp(nomeExcursao, atual->nomeExcursao)== 0){
        removerFrente(nomeExcursao, listaEnc);
        return 1;
    }
    while(strcmp(nomeExcursao, atual->nomeExcursao)!=0){
        anterior = atual;
        atual= atual->proxExcursao;
    }
    //remove fim
    if(atual->proxExcursao== NULL){
        anterior->proxExcursao = NULL;
        listaEnc->fim = anterior;
        free(atual);
        return 1;

    }
    anterior->proxExcursao = atual->proxExcursao;
    free(atual);


    return 1;


}
int removerFrente(char nomeExcursao[50], controlMutilista *listaEnc){
    tipoExcursao *atual;
    atual = listaEnc->inicio;
    listaEnc->inicio = atual->proxExcursao;

    if(listaEnc->quantMultilsta == 1){
        listaEnc->fim=NULL;
    }

    free(atual);
    return 1;

}
int adicionarTurista(char nomeExcursao[50],char nomeTurista[50], char cpf[50], controlMutilista *listaEnc){
    tipoTurista *novoTurista;
    tipoExcursao *atual;
    atual = listaEnc->inicio;

    if(listaEnc == NULL){
        return 0;
    }
    while(!strcmp(atual->nomeExcursao, nomeExcursao)){
        atual = atual->proxExcursao;
    }

    novoTurista = malloc(sizeof(tipoTurista));
    if(novoTurista == NULL){
        return 0;
    }
    strcpy(novoTurista->nome, nomeTurista);
    strcpy(novoTurista->cpf, cpf);
    novoTurista->ProxNo = NULL;
    atual->inicioLista = novoTurista;

    return 1;
}

void mostrar(controlMutilista *listaEnc){
    tipoExcursao *atual;
    atual = listaEnc->inicio;

    while(atual != NULL){
        printf("\nnome excursao: %s", atual->nomeExcursao);
        printf("\ndestino: %s", atual->destino);
        atual = atual->proxExcursao;
    }

}
int main(){
    controlMutilista multilista;
    tipoExcursao excursao;

    char nomeP[50], nomet[50], cpft[50];
    char destinoP[50];
    int diasP, opc;



    do{
        printf("\n1- Inicializar multilista");
        printf("\n2- Criar excursao");
        printf("\n3- Adicionar excursao");
        printf("\n4- adicionar turistas");
        printf("\n5- remover excursao");
        printf("\n9- Mostrar");
        scanf("%d", &opc);

        switch(opc){
        case 1:
            inicializaMultilista(&multilista);
            break;
        case 2:
            printf("\nNome da excursao:");
            scanf("%s", &nomeP);
            printf("\nDestino:");
            scanf("%s", &destinoP);
            printf("\nNumero de dias:");
            scanf("%d", &diasP);

            criarExcursao(&multilista, &excursao, nomeP, destinoP, diasP);
            break;
        case 3:
            printf("\nNome da excursao:");
            scanf("%s", &nomeP);
            printf("\nDestino:");
            scanf("%s", &destinoP);
            printf("\nNumero de dias:");
            scanf("%d", &diasP);

            adicionarExcursao(&multilista, &excursao, nomeP, destinoP, diasP);
            break;
        case 4:
            printf("\nnome:");
            scanf("%s", &nomet);
            printf("\ncpf:");
            scanf("%s", &cpft);

            printf("digite o nome da excursao que quer adicionar");
            scanf("%s", &nomeP);

            adicionarTurista(nomeP,nomet,cpft,&multilista);
            break;
        case 5:
            printf("\ndigite o nome da excursao que quer remover:");
            scanf("%s", &nomeP);
            removerExcursao(nomeP,&multilista);
            break;
        case 9:
            mostrar(&multilista);
            break;
        default:
            printf("\nOpcao invalida");
            break;
        }


    }while(opc != 0);



    return 0;
}
