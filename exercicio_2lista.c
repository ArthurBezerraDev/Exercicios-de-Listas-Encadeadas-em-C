#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct Veículo{
    
    char placa[10];
    float tempo;
    struct Veículo *prox;
    
}Veículo;

typedef struct Garagem{ 

    Veículo *inicio;
    
}Garagem;


void Remove_barran(char *str){
    str[strcspn(str,"\n")]= '\0';
}


// ------- Adicionar Veículo -------
void Adicionar_Veículo(Garagem *est){
    
    float tempo;
    char placa[10];
    
    printf("TEMPO do veículo: ");
    scanf(" %f", &tempo);
    getchar(); //Pegar o '\n' solto
    
    printf("PLACA do veículo: ");
    fgets(placa, sizeof(placa), stdin);
    Remove_barran(placa);
    
    Veículo *aux = est->inicio;
    while (aux){
        if (strcmp(aux->placa, placa) == 0){
            aux->tempo = tempo;
            printf("Placa já existia!\n Tempo alterado com sucesso\n");
            return;
        }
        aux = aux->prox;
    }
    
    Veículo *novo = malloc(sizeof(Veículo));
    
    if (!(novo)){
        printf("ERRO, alocação de memória!\n");
        return;
    }
    
    novo->tempo = tempo;
    strcpy(novo->placa, placa);
    
    novo->prox = est->inicio;
    est->inicio = novo;
    printf("Nó criado com sucesso!\n");
}

// ------- Remover Nó -------
void Remover(Garagem *est){
    
    if (!(est->inicio)){
        
    }
    
    Veículo *aux = est->inicio;
    Veículo *pre;
    
    char placa[10];
    
    printf("PLACA do veículo: ");
    fgets(placa, sizeof(placa), stdin);
    Remove_barran(placa);
    
    
    if (strcmp(aux->placa, placa) == 0){
        
        est->inicio = aux->prox;
        free(aux);
        printf("Primeiro Nó removido com sucesso!\n");
        return;

    }
    while(aux){
        if (strcmp(aux->placa, placa) == 0){
            pre->prox = aux->prox;
            free(aux);
            printf("Nó removido com sucesso!\n");
            return;
        }
        pre = aux;
        aux = aux->prox;
    }
    printf("ERRO, placa não encontrada!\n");
}

// ------- Imprimir Lista -------
void Imprimir(Garagem *est){
    
    if (!(est->inicio)){
        printf("ERRO, garagem vazia!\n");
        return; 
    }
    Veículo *aux = est->inicio;
    
    
    printf("---------------------------------\n");
    while(aux){
        printf("\t %s: %.1f horas\n", aux->placa, aux->tempo);
        aux = aux->prox;
    }
    printf("---------------------------------\n");
}

// ------- Encerramento -------
void Encerramento(Garagem *est){
    
    if (!(est)) return;
    
    if (!(est->inicio)){
        printf("Lista já vazia!\n");
        est = NULL;
        free(est);
        printf("Lista liberada com sucesso!\n");
        return;
    }
    
    Veículo *aux = est->inicio;
    Veículo *pos;
 
    while(aux){
        pos = atual->prox;
        free(aux)
        aux = pos;
    }
    
    est->inicio = NULL;
    est = NULL;
    free(est);
    printf("Lista liberada com sucesso!\n");
    
}

int main()
{
    
    Garagem *estacionamento = malloc(sizeof(Garagem));
    estacionamento->inicio = NULL;
    
    Adicionar_Veículo(estacionamento);
    Imprimir(estacionamento);
    Remover(estacionamento);
    Imprimir(estacionamento);   
    
    return 0;
}
