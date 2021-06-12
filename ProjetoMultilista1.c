#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char nome[70];
    char cpf[50];
    struct no *ProxNo;
}tipoTurista;
//mudei aqui
typedef struct ListaExcursao{
    char nomeExcursao[70];
    char destino[70];
    int numDias;
    int dataDia;
    int dataMes;
    int dataAno;
    struct ListaExcursao *proxExcursao;
    tipoTurista *inicioLista;
    int quantidadeTurista;
}tipoExcursao;
typedef struct Mutilista{
    tipoExcursao *inicio;
    tipoExcursao *fim;
    int quantMultilsta;
}controlMutilista;

void inicializaMultilista(controlMutilista *listaEnc);
int estaVazia(controlMutilista *listaEnc);
tipoExcursao *buscarExcursao(controlMutilista *listaEnc, char nomeExcursao[70]);
int removerDeterminadoTurista(controlMutilista *listaEnc, char nomeExcursao[70], char nomeTurista[70]);
int criarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[70], char destino[70], int Numdias, int dia, int mes,int ano);
int adicionarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[70], char destino[70], int Numdias, int dia, int mes, int ano);
int removerExcursao(char nomeExcursao[70], controlMutilista *listaEnc);
int removerFrente(tipoExcursao *atual, controlMutilista *listaEnc);
int adicionarTurista(char nomeExcursao[70],char nomeTurista[70], char cpf[50], controlMutilista *listaEnc);
void mostrar(controlMutilista *listaEnc);
void mostrarTurista(controlMutilista *listaEnc, char nomeExcursao[70]);
tipoExcursao* mostrarExcursao(controlMutilista *listaEnc, char nomeExcursao[70]);
void removeTuristaFrente(controlMutilista *listaEnc, tipoExcursao* NoExcursao);

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

void removeTuristaFrente(controlMutilista *listaEnc, tipoExcursao* NoExcursao){
       tipoTurista *aux, *atualturista;
       atualturista = NoExcursao->inicioLista;

       while(atualturista != NULL){
        aux = atualturista;
        listaEnc->inicio->quantidadeTurista--;
        atualturista = atualturista->ProxNo;
        free(aux);
       }

}
tipoExcursao *buscarExcursao(controlMutilista *listaEnc, char nomeExcursao[70]){
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
int removerDeterminadoTurista(controlMutilista *listaEnc, char nomeExcursao[70], char nomeTurista[70]){
    tipoExcursao *atual;
    tipoTurista *atualTurista, *anterior, *aux;

    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        printf("\nExcursao nao encontrada");
        return 0;
    }
     atual = buscarExcursao(listaEnc, nomeExcursao);
     if(atual->inicioLista == NULL){
        printf("\nNenhum turista na lista");
        return 0;
     }else{
        atual = buscarExcursao(listaEnc, nomeExcursao);
        atualTurista = atual->inicioLista;
         //falta a condicao que so tem um turista na lista

        //remove inicio
        if(strcmp(atualTurista->nome, nomeTurista) == 0){
            if(atual->quantidadeTurista>1){
            aux = atualTurista->ProxNo;
            atual->inicioLista = aux;
            atual->quantidadeTurista--;
            free(atualTurista);
            return 1;
            }else{
            atual->quantidadeTurista--;
            atual->inicioLista = NULL;
            free(atualTurista);
            return 1;
            }
        }

        while(strcmp(atualTurista->nome, nomeTurista)!=0){
            anterior = atualTurista;
            atualTurista = atualTurista->ProxNo;
        }
         //remover fim
        if(atualTurista->ProxNo ==NULL){
            anterior->ProxNo = NULL;
            atual->quantidadeTurista--;
            free(atualTurista);
            return 1;
        }

        anterior->ProxNo = atualTurista->ProxNo;
        atual->quantidadeTurista--;
        free(atualTurista);
        return 1;



}
}
int criarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[70], char destino[70], int Numdias, int dia, int mes, int ano){
    tipoExcursao *novaExcursao;
    novaExcursao = malloc(sizeof(tipoExcursao));
    if(novaExcursao == NULL){
        return 0;
    }
    strcpy(novaExcursao->nomeExcursao, nome);
    strcpy(novaExcursao->destino, destino);
    novaExcursao->numDias = Numdias;
    novaExcursao->dataDia = dia;
    novaExcursao->dataMes = mes;
    novaExcursao->dataAno = ano;
    novaExcursao->quantidadeTurista = 0;
    novaExcursao->proxExcursao = NULL;
    novaExcursao->inicioLista = NULL;
    listaEnc->inicio = novaExcursao;
    listaEnc->fim = novaExcursao;
    listaEnc->quantMultilsta++;

    return 1;
}
int adicionarExcursao(controlMutilista *listaEnc, tipoExcursao *listaExcursao, char nome[70], char destino[70], int Numdias, int dia, int mes, int ano){
    tipoExcursao *novaExcursao;
     if(listaEnc->inicio == NULL){
        criarExcursao(listaEnc, listaExcursao, nome, destino, Numdias, dia, mes, ano);
        return 1;
    }
    novaExcursao = malloc(sizeof(tipoExcursao));
    if(novaExcursao == NULL){
        return 0;
    }
    //adicionando atras
    strcpy(novaExcursao->nomeExcursao, nome);
    strcpy(novaExcursao->destino, destino);
    novaExcursao->numDias = Numdias;
    novaExcursao->dataDia = dia;
    novaExcursao->dataMes = mes;
    novaExcursao->dataAno = ano;
    novaExcursao->quantidadeTurista = 0;
    novaExcursao->inicioLista =NULL;
    novaExcursao->proxExcursao = NULL;

    listaEnc->fim->proxExcursao= novaExcursao;
    listaEnc->fim = novaExcursao;
    listaEnc->quantMultilsta++;

    return 1;



}
int removerExcursao(char nomeExcursao[70], controlMutilista *listaEnc){
    tipoExcursao *atual, *anterior;
    tipoTurista *atualTurista, *aux;
    atual = listaEnc->inicio;

    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        return 0;
    }else{
    //remove inicio
    if(strcmp(nomeExcursao, atual->nomeExcursao)== 0){
        removerFrente(atual, listaEnc);
        return 1;
    }
    while(strcmp(nomeExcursao, atual->nomeExcursao)!=0){
        anterior = atual;
        atual= atual->proxExcursao;
    }
    //condicao nome diferente
    //remove fim
    if(atual->proxExcursao== NULL){
        removeTuristaFrente(listaEnc, atual);

        anterior->proxExcursao = NULL;
        listaEnc->fim = anterior;
        listaEnc->quantMultilsta--;
        free(atual);
        return 1;
    }

    removeTuristaFrente(listaEnc, atual);
    anterior->proxExcursao = atual->proxExcursao;
    listaEnc->quantMultilsta--;
    free(atual);


    return 1;
    }

}
int removerFrente(tipoExcursao* atual, controlMutilista *listaEnc){

    if(atual->proxExcursao == NULL){
        removeTuristaFrente(listaEnc, atual);
        listaEnc->fim=NULL;
        listaEnc->inicio=NULL;
        listaEnc->quantMultilsta--;
        free(atual);
        return 1;
    }
    listaEnc->inicio = atual->proxExcursao;

    //excluindo o no da lista de turistas
    //removeTuristaFrente(listaEnc, atual);



    listaEnc->quantMultilsta--;

    free(atual);
    return 1;

}
int adicionarTurista(char nomeExcursao[70],char nomeTurista[70], char cpf[50], controlMutilista *listaEnc){
    tipoTurista *novoTurista;
    tipoExcursao *atual;
    atual = listaEnc->inicio;


    if(buscarExcursao(listaEnc, nomeExcursao)==NULL){
        return 0;
    }else{
    atual = buscarExcursao(listaEnc, nomeExcursao);

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
    atual->quantidadeTurista++;
    return 1;
    }
    novoTurista->ProxNo = atual->inicioLista;
    atual->inicioLista = novoTurista;
    atual->quantidadeTurista++;

    return 1;
    }
}

void mostrar(controlMutilista *listaEnc){
    tipoExcursao *atual;
    atual = listaEnc->inicio;

    printf("\nLista das Excursao:");
    while(atual != NULL){
        printf("\n===== Excursao =====");
        printf("\nNome excursao: %s", atual->nomeExcursao);
        printf("\ndestino: %s", atual->destino);
        printf("\ndias da excursao: %d", atual->numDias);
        printf("\ndata: %d / %d / %d", atual->dataDia, atual->dataMes, atual->dataAno);
        printf("\nQuantidade de turista: %d", atual->quantidadeTurista);
        printf("\nQuantidade multilista: %d", listaEnc->quantMultilsta);

        atual = atual->proxExcursao;

    }

}
tipoExcursao* mostrarExcursao(controlMutilista *listaEnc, char nomeExcursao[70]){
     tipoExcursao *atual;
     tipoTurista *atualTurista;
     atual = buscarExcursao(listaEnc, nomeExcursao);
     if(atual == NULL){
            return atual;
     }
     atualTurista = atual->inicioLista;

     if(atual != NULL){
        printf("\n===== Excursao: %s =====", atual->nomeExcursao);
        printf("\ndestino: %s", atual->destino);
        printf("\ndias da excursao: %d", atual->numDias);
        printf("\ndata: %d / %d / %d", atual->dataDia, atual->dataMes, atual->dataAno);
        printf("\nQuantidade Turista: %d", atual->quantidadeTurista);
        mostrarTurista(listaEnc, atual->nomeExcursao);

     }


}
void mostrarTurista(controlMutilista *listaEnc, char nomeExcursao[70]){
    tipoExcursao *atual;
    tipoTurista *prox;
    atual = listaEnc->inicio;


    while(strcmp(atual->nomeExcursao, nomeExcursao)!= 0){
        atual = atual->proxExcursao;
    }
    prox = atual->inicioLista;

    if(prox == NULL){
        printf("\nNao ha nenhum turista");
    }
    printf("\nLista de turistas:");
    while(prox != NULL){
        printf("\n======= TURISTA ========");
        printf("\nnome: %s", prox->nome);
        printf("\ncpf: %s", prox->cpf);
        prox = prox->ProxNo;
    }


}
int main(){
    controlMutilista multilista;
    tipoExcursao excursao;
    tipoExcursao aux;

    char nomeP[70], nomet[70], cpft[30];
    char destinoP[70];
    int diasP, opc;
    int diaMain, mesMain, anoMain;



    do{
        printf("\n1- Inicializar multilista");
        printf("\n2- Criar excursao");
        printf("\n3- Adicionar excursao");
        printf("\n4- adicionar turistas");
        printf("\n5- remover excursao");
        printf("\n6- mostrar turista");
        printf("\n7- remover turista");
        printf("\n8- Mostrar dados de excursao especifica");
        printf("\n9- Mostrar");
        printf("\n10- Esta vazia");
        scanf("%d", &opc);

        switch(opc){
        case 1:
            inicializaMultilista(&multilista);
            break;
        case 2:
            setbuf(stdin, NULL);
            printf("\nNome da excursao:");
            fgets(nomeP, 70, stdin);
            setbuf(stdin, NULL);
            printf("\nDestino:");
            fgets(destinoP, 70, stdin);
            setbuf(stdin, NULL);
            printf("\nNumero de dias:");
            scanf("%d", &diasP);
            printf("\ndigite a data:");
            printf("\ndia: ");
            scanf("%d", &diaMain);
            printf("\nMes: ");
            scanf("%d", &mesMain);
            printf("\nAno: ");
            scanf("%d", &anoMain);

            if(criarExcursao(&multilista, &excursao, nomeP, destinoP, diasP, diaMain, mesMain,anoMain)== 1 ){
                printf("\nExcursao adicionada");
            }else{
                printf("\nExcursao nao adicionada, tente novamente");
            }
            break;
        case 3:
            setbuf(stdin, NULL);
            printf("\nDigite o Nome da excursao:");
            fgets(nomeP, 70, stdin);
            setbuf(stdin, NULL);
            printf("\nDigite o Destino:");
            fgets(destinoP, 70, stdin);
            setbuf(stdin, NULL);
            printf("\nNumero de dias:");
            scanf("%d", &diasP);
            printf("\ndigite a data");
            printf("\ndia: ");
            scanf("%d", &diaMain);
            printf("\nMes: ");
            scanf("%d", &mesMain);
            printf("\nAno: ");
            scanf("%d", &anoMain);


            if(adicionarExcursao(&multilista, &excursao, nomeP, destinoP, diasP, diaMain, mesMain,anoMain)== 1 ){
                printf("\nExcursao adicionada");
            }else{
                printf("\nExcursao nao adicionada, tente novamente");
            }
            break;
        case 4:
            if(estaVazia(&multilista)== 1){
                printf("\nA lista esta vazia, adicione uma excursao");
            }else{
            setbuf(stdin, NULL);
            printf("\nDigite o nome do turista:");
            fgets(nomet, 70, stdin);
            setbuf(stdin, NULL);
            printf("\ncpf:");
            fgets(cpft, 50, stdin);

            setbuf(stdin, NULL);
            printf("\nDigite o nome da excursao que quer adicionar");
            fgets(nomeP, 70, stdin);


            if(adicionarTurista(nomeP,nomet,cpft,&multilista)){
                printf("\nO turista foi adicionado");
            }else{
                printf("\nNome da excursao errado");
            }
            }
            break;
        case 5:
            mostrar(&multilista);
            setbuf(stdin, NULL);
            printf("\nNome da excursao:");
            fgets(nomeP, 70, stdin);
            if(removerExcursao(nomeP,&multilista)== 0){
                printf("\nO nome dessa excursao esta errado");
            }else{
                printf("\nRemovido com sucesso");
            }
            break;
        case 6:
            setbuf(stdin, NULL);
            printf("\ndigite o nome da excursao que quer ver os dados do turistas:");
            fgets(nomeP, 70, stdin);
            if(buscarExcursao(&multilista, nomeP)== NULL){
                printf("\nExcursao nao existe");
            }else{
            mostrarTurista(&multilista, nomeP);
            }
            break;
        case 7:
            mostrar(&multilista);
            setbuf(stdin, NULL);
            printf("\nDigite Nome da excursao:");
            fgets(nomeP, 70, stdin);
            setbuf(stdin, NULL);
            printf("\nDigite o Nome do turista:");
            fgets(nomet, 70, stdin);
            if(estaVazia(&multilista)){
                printf("\nNenhuma excursao para adicionar o turista");
            }
            if(removerDeterminadoTurista(&multilista,nomeP ,nomet)==1){
                printf("\nTurista removido");
            }
            break;
        case 8:
            if(estaVazia(&multilista)== 1){
                printf("\nNenhuma excursao, adicione alguma");
                break;
            }

            fflush(stdin);
            printf("\nNome da excursao:");
            fgets(nomeP, 70, stdin);

            if(buscarExcursao(&multilista, nomeP)==NULL){
                printf("\nExcursao nao encontrada");
            }
            mostrarExcursao(&multilista, nomeP);

            break;
        case 9:
            if(estaVazia(&multilista)== 1){
                printf("\nNenhuma excursao, adicione alguma");
            }
            mostrar(&multilista);
            break;
        case 10:
            if(estaVazia(&multilista)== 1){
                printf("\nNenhuma excursao, adicione alguma");
            }else{
                printf("\nPode adicionar");
            }
            break;
        default:
            printf("\nOpcao invalida");
            break;
        }


    }while(opc != 0);



    return 0;
}
