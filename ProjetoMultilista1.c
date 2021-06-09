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
    int dataDia;
    int dataMes;
    int dataAno;
    struct ListaExcursao *proxExcursao;
    tipoTurista *inicioLista;
}tipoExcursao;
typedef struct Mutilista{
    tipoExcursao *inicio;
    tipoExcursao *fim;
    int quantMultilsta;
}controlMutilista;

void inicializaMultilista(controlMutilista *listaEnc);
int estaVazia(controlMutilista *listaEnc);
tipoExcursao *buscarExcursao(controlMutilista *listaEnc, char nomeExcursao[50]);
int criarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[50], char destino[50], int Numdias);
int removerTurista(controlMutilista *listaEnc, char nomeExcursao[50], char nomeTurista[50]);
int criarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[50], char destino[50], int Numdias);
int adicionarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[50], char destino[50], int Numdias);
int removerExcursao(char nomeExcursao[50], controlMutilista *listaEnc);
int removerFrente(char nomeExcursao[50], controlMutilista *listaEnc);
int adicionarTurista(char nomeExcursao[50],char nomeTurista[50], char cpf[50], controlMutilista *listaEnc);
void mostrar(controlMutilista *listaEnc);
void mostrarTurista(controlMutilista *listaEnc, char nomeExcursao[50]);



void inicializaMultilista(controlMutilista *listaEnc){
     listaEnc->inicio=NULL;
     listaEnc->fim=NULL;
     listaEnc->quantMultilsta = 0;
}
int estaVazia(controlMutilista *listaEnc){
    if(listaEnc->inicio == NULL){
        return 1;
    }
     return 0;
}
tipoExcursao *buscarExcursao(controlMutilista *listaEnc, char nomeExcursao[50]){
    tipoExcursao *atual;
    atual = listaEnc->inicio;
    while(atual != NULL){
        if(strcmp(atual->nomeExcursao, nomeExcursao)==0){
            return atual;
        }
        atual = atual->proxExcursao;
    }
    return NULL;
}
int removerTurista(controlMutilista *listaEnc, char nomeExcursao[50], char nomeTurista[50]){
    tipoExcursao *atual;
    tipoTurista *atualTurista, *anterior;

    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        printf("\nExcursao nao encontrada");
        return 0;
    }else{
        atual = buscarExcursao(listaEnc, nomeExcursao);
        atualTurista = atual->inicioLista;
         //falta a condicao que so tem um turista na lista

        //remove inicio
        if(strcmp(atual->inicioLista->nome, nomeTurista) == 0){
            if(atualTurista->quantidadeTurista>1){
            atual->inicioLista = atualTurista->ProxNo;
            atual->inicioLista->quantidadeTurista--;
            }else{
            atual->inicioLista = NULL;
            }

            free(atualTurista);
            return 1;
        }

        while(strcmp(atualTurista->nome, nomeTurista)!=0){
            anterior = atualTurista;
            atualTurista = atualTurista->ProxNo;
        }
         //remover fim
        if(atualTurista->ProxNo ==NULL){
            anterior->ProxNo = NULL;
            atualTurista->quantidadeTurista--;
            free(atualTurista);
            return 1;
        }

        anterior->ProxNo = atualTurista->ProxNo;
        atualTurista->quantidadeTurista--;
        free(atualTurista);
        return 1;



}
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
    //adicionando atras
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

    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        return 0;
    }else{
    //remove inicio
    if(strcmp(nomeExcursao, atual->nomeExcursao)== 0){
        removerFrente(nomeExcursao, listaEnc);
        return 1;
    }
    while(strcmp(nomeExcursao, atual->nomeExcursao)!=0 || atual != NULL){
        anterior = atual;
        atual= atual->proxExcursao;
    }
    //condicao nome diferente
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


    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        return 0;
    }else{


    novoTurista = malloc(sizeof(tipoTurista));
    if(novoTurista == NULL){
        return 0;
    }
    strcpy(novoTurista->nome, nomeTurista);
    strcpy(novoTurista->cpf, cpf);
    //primeiro turista adiciconado
    if(listaEnc->inicio->inicioLista == NULL){
    novoTurista->ProxNo = NULL;
    atual->inicioLista = novoTurista;
    atual->inicioLista->quantidadeTurista++;
    return 1;
    }
    novoTurista->ProxNo = atual->inicioLista;
    atual->inicioLista = novoTurista;
    atual->inicioLista->quantidadeTurista++;

    return 1;
    }
}

void mostrar(controlMutilista *listaEnc){
    tipoExcursao *atual;
    atual = listaEnc->inicio;

    printf("\nLista das Excursao:");
    while(atual != NULL){
        printf("\nnome excursao: %s", atual->nomeExcursao);
        printf("\ndestino: %s", atual->destino);
        atual = atual->proxExcursao;
    }

}
void mostrarTurista(controlMutilista *listaEnc, char nomeExcursao[50]){
    tipoExcursao *atual;
    tipoTurista *prox;
    atual = listaEnc->inicio;


    while(strcmp(atual->nomeExcursao, nomeExcursao)!= 0){
        atual = atual->proxExcursao;
    }
    prox = atual->inicioLista;

    printf("\nLista de turistas:");
    while(prox != NULL){
        printf("nome: %s", prox->nome);
        printf("cpf: %s", prox->cpf);
        prox = prox->ProxNo;
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
        printf("\n6- mostrar turista");
        printf("\n7- remover turista");
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
            if(estaVazia(&multilista)== 1){
                printf("\nA lista esta vazia");
            }else{
            printf("\nnome:");
            scanf("%s", &nomet);
            printf("\ncpf:");
            scanf("%s", &cpft);

            printf("digite o nome da excursao que quer adicionar");
            scanf("%s", &nomeP);


            if(adicionarTurista(nomeP,nomet,cpft,&multilista)){
                printf("\nO turista foi adicionado");
            }else{
                printf("\nNome da excursao errado");
            }
            }
            break;
        case 5:
            printf("\ndigite o nome da excursao que quer remover:");
            scanf("%s", &nomeP);
            if(removerExcursao(nomeP,&multilista)== 0){
                printf("\nO nome dessa excursao esta errado");
            }else{
                printf("\nRemovido com sucesso");
            }
            break;
        case 6:
            printf("\ndigite o nome da excursao que quer ver os dados do turistas:");
            scanf("%s", &nomeP);
            mostrarTurista(&multilista, nomeP);
            break;
        case 7:
            printf("\nDigite a excursao em que deseja remover");
            scanf("%s", &nomeP);
            printf("\nnome do turista:");
            scanf("%s", &nomet);
            if(estaVazia(&multilista)){
                printf("\nNenhuma excursao para adicionar");
            }
            if(removerTurista(&multilista,nomeP ,nomet)==1){
                printf("\nTurista removido");
            }
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
