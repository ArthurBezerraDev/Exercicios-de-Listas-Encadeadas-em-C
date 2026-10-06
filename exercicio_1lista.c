#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*-----------------------------------------------------

A intenção desse projeto é refazer o exercício 1 incorporando o 
'fgets' para pegar as 'strings'.

------------------------------------------------------*/

typedef struct aluno{
    
    char nome[50];
    float nota;
    struct aluno *prox;
    
}aluno; // definindo o nó 'aluno' contendo 'nome', 'nota' e um 'prox' que aponta para o próximo elemento da lista encadeada

typedef struct turma{
    
    aluno *inicio;
    
}turma; // definindo o 'nó cabeça' que contém um 'inicio' q aponta para o primeiro elemento da lista encadeada;

// -------------------------- Função Auxiliar --------------------------

void limpar_barra_n(char *nome){
    int i = 0;
    while (nome[i] != '\0'){
        if (nome[i] == '\n'){ //Procurando '\n' e quando encontrar retira e bota o '\0'
            nome[i] = '\0';
            return;
        }
        i++;
    }
}// remove o '\n' de uma string

int nome_encontrado(turma *classe, char *nome){
    
    aluno *aux = classe->inicio;
    
    while (aux){
        if (strcmp(aux->nome, nome) == 0){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
} // retorna 1 se encontra o nome e 0 se não.

// -------------------------- Cadastrar aluno --------------------------
/*
O usuário deverá informar o nome e a nota. Caso o aluno ainda não esteja na lista, um novo
elemento deverá ser criado dinamicamente e inserido na lista.

Caso já exista um aluno com o mesmo nome, o programa deverá informar “Aluno já cadastrado.” e
não deverá criar um novo elemento.
*/
void Cadastrar_aluno(turma *classe){
    
    float nota;
    char nome[50];
    
    printf("Digite o nome do aluno: ");
    fgets(nome, sizeof(nome), stdin);
    limpar_barra_n(nome);
    
    if (nome_encontrado((classe), nome) == 1){ // nome do aluno encontrado
        printf("\n-\nERRO, Aluno já cadastrado\n-\n");
        return;
    }// nome do aluno encontrado
    
    printf("Digite a nota: ");
    scanf("%f", &nota);
    getchar();
 
    
    aluno *novo = malloc(sizeof(aluno));
    
    strcpy(novo->nome, nome);//passando o nome para o nó
    novo->nota = nota;// passando a nota para o nó
    
    aluno *aux = (classe)->inicio; // 'aux' assume o 1° elemento
    
    (classe)->inicio = novo;// 'novo' assume como 1° elemento
    novo->prox = aux;// 'novo' aponta para o 'aux'
    printf("\nAluno Cadastrado!\n");
}

// -------------------------- Alterar nota --------------------------
/*
O usuário deverá informar o nome do aluno. Caso ele exista, deverá ser solicitada uma nova nota e
o valor armazenado deverá ser atualizado.
Caso o aluno não exista, o programa deverá informar “Aluno não encontrado.”
*/
void Alterar_nota(turma *classe){
    
    if (!(classe->inicio)){
        printf("\n-\nERRO, Nenhum aluno cadastrado\n-\n");
        return;
    }
    char nome[50];
    float nota;
    
    printf("Digite o nome do aluno a ter a nota alterada: ");
    fgets(nome, sizeof(nome), stdin);
    limpar_barra_n(nome);
    
    if (nome_encontrado(classe,nome) == 0){
        printf("\n-\nERRO, Aluno não encontrado\n-\n");
        return;
    }
    
    printf("Digite a nota a ser alterada: ");
    scanf("%f", &nota);
    getchar();
    
    aluno *aux = (classe)->inicio;
    
    while (aux){
        if (strcmp(aux->nome, nome) == 0){
            aux->nota = nota;
            printf("\nNota alterada!\n");
            return;
        }
        aux = aux->prox;
    }
}


// -------------------------- Remover Aluno --------------------------
/*
O usuário deverá informar o nome do aluno que deseja remover. O programa deverá localizar e
remover corretamente o elemento, independentemente de ele estar:
 no início da lista;
 no meio da lista;
 no final da lista.
A memória ocupada pelo elemento removido deverá ser liberada.
*/
void Remover_aluno(turma *classe){
    if (!(classe->inicio)){
        printf("\n-\nERRO, Nenhum aluno cadastrado\n-\n");
        return;
    }
    char nome[50];
    float nota;
    
    printf("Digite o nome do aluno: ");
    fgets(nome, sizeof(nome), stdin);
    limpar_barra_n(nome);
    
    if (nome_encontrado(classe, nome) == 0){// Se não encontrar o nome, ele retorna 'erro'
        printf("\n-\nERRO, Aluno não encontrado\n-\n");
        return;
    }
    
    aluno *aux = classe->inicio;
    aluno *pre;
    
    // Se o primeiro aluno for o aluno procurado 
    if (strcmp(aux->nome, nome) == 0){
        classe->inicio = aux->prox;
        free(aux);
        printf("\nAluno removido!\n");
        return;
    }
    while (aux){
        
        if (strcmp(aux->nome, nome) == 0){
            pre->prox = aux->prox;
            free(aux);
            printf("\nAluno removido!\n");
            return;
        }
        pre = aux;
        aux = aux->prox;
    }
    
}

// -------------------------- Mostrar alunos --------------------------
/*
O programa deverá percorrer toda a lista e apresentar os alunos cadastrados e suas respectivas
notas.
Caso a lista esteja vazia, o programa deverá informar “Nenhum aluno cadastrado.”
*/
void Mostrar_alunos(turma *classe){
    
    if (classe->inicio == NULL){
        printf("\n-\nERRO, Nenhum aluno cadastrado.\n-\n");
        return;
    }
    
    aluno *aux = classe->inicio;
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    while (aux){
        printf("\t%s: %.1f\n", aux->nome, aux->nota);
        aux = aux->prox;
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// -------------------------- Encerramento --------------------------
/*
Antes de encerrar o programa, toda a memória dinamicamente alocada deverá ser liberada.
*/
void Encerramento(turma *classe){
    
    aluno *aux = classe->inicio;
    aluno *pos;
    
    if (classe->inicio != NULL){// Se a lista tiver algum nó
        
        (classe->inicio) = aux->prox;
        
        free(aux);
        
        aux = classe->inicio;
        pos = aux->prox;
    }
    
    while (aux){
        free(aux);
        aux = pos;
        if (pos){
            pos = pos->prox;
        }
    }
    classe->inicio = NULL;
    free(classe);
    
}

int main(){
    turma *classe = malloc(sizeof(turma));
    classe->inicio = NULL;
    
    int escolha;
    
    int i;
    
    printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\tCadastro de Alunos");
    while (1){
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n");
        printf("Digite o respectivo número para realizar\na ação:\n");
        printf("1 - Cadastrar Aluno\n");
        printf("2 - Alterar a nota\n");
        printf("3 - Remover aluno\n");
        printf("4 - Mostrar os alunos\n");
        printf("0 - Encerramento\n");
        printf(": ");
        scanf("%d", &escolha);
        getchar();
        printf("\n\n");
        
        //Cadastrar aluno
        if (escolha == 1){
            Cadastrar_aluno(classe);
            printf("\n");
        }
        //Alterar nota
        else if (escolha == 2){
            Alterar_nota(classe);
            printf("\n");
        }
        //Remover aluno
        else if (escolha == 3){
            Remover_aluno(classe);
            printf("\n");
        }
        //Mostrar alunos
        else if (escolha == 4){
            Mostrar_alunos(classe);
            printf("\n");
        }
        //Encerramento
        else if (escolha == 0){
            Encerramento(classe);
            printf("\n");
            printf("Lista encerrada!\nObrigado por executar o código!\n");
            break;
        }
        
        else{
            printf("\n-\nERRO, entrada inapropriada\n-\n");
        }

    }
    
    return 0;
}
