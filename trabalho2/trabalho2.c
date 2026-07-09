/* Louvado seja o Senhor */

#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct lista {
    int size; int qntEl;
    No *inicio, *fim;
} Lista;

Lista * vetorPrincipal[TAM];

No * criar_no(int num){
    No * n = malloc(sizeof(No));

    n->conteudo = num;
    n->prox = NULL;

    return n;
}

Lista * criar_lista(int size){
    Lista * l = malloc(sizeof(Lista));

    l->inicio = l->fim = NULL;
    l->size = size;
    l->qntEl = 0;

    return l;
}

int ehPosicaoValida(int posicao);

int validacao(int posicao){
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){ return POSICAO_INVALIDA; }
    if(vetorPrincipal[posicao-1] == NULL){ return SEM_ESTRUTURA_AUXILIAR; }

    return SUCESSO;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Retorno (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int pos = posicao-1;
    
    // se posição é um valor válido {entre 1 e 10}
    if(pos < 0 || pos > 9){ return POSICAO_INVALIDA; }
    
    // a posicao pode já existir estrutura auxiliar
    if(vetorPrincipal[pos] != NULL){ return JA_TEM_ESTRUTURA_AUXILIAR; }
    
    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){ return TAMANHO_INVALIDO; }

    Lista * l = criar_lista(tamanho);

    // o tamanho ser muito grande
    if(l == NULL){ return SEM_ESPACO_DE_MEMORIA; } 

    // deu tudo certo, crie
    vetorPrincipal[pos] = l;
    return SUCESSO;
}

void inserir_no_lista(Lista * l, int valor){
    No * n = criar_no(valor);

    if(l->inicio == NULL){
        l->inicio = l->fim = n;
    }
    else{
        l->fim->prox = n;
        l->fim = n;
    }

    l->qntEl++;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }

    Lista * l = vetorPrincipal[posicao-1];

    if(l->qntEl == l->size){ return SEM_ESPACO; }
        
    inserir_no_lista(l, valor);
    return SUCESSO;
}

void excluir_valor_final(Lista * l){
    No * n = l->fim, *p = l->inicio;

    while(p != n && p->prox != n){
        p = p->prox;
    }

    l->fim = p;
    if(n == l->inicio){
        l->inicio = NULL;
    }
    else{
        p->prox = NULL;
    }
    l->qntEl--;
    free(n);
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }

    Lista * l = vetorPrincipal[posicao-1];
    if(l->qntEl == 0){ return ESTRUTURA_AUXILIAR_VAZIA; }

    excluir_valor_final(l);

    return SUCESSO;
}

No * buscar_no_valor(No * n, int valor){
    No * aux = n;

    while(aux != NULL && aux->conteudo != valor){
        aux = aux->prox;
    }

    return aux;
}

int excluir_valor_especifico(Lista * l, int valor){
    No * n = buscar_no_valor(l->inicio, valor), *p = l->inicio;

    if(n == NULL){ return NUMERO_INEXISTENTE; }

    while(p != n && p->prox != n){
        p = p->prox;
    }

    if(n == l->inicio){
        l->inicio = n->prox;

        if(n == l->fim){
            l->fim = NULL;
        }
    }
    else if(n == l->fim){
        excluir_valor_final(l);
    }
    else{
        p->prox = n->prox;
    }
    free(n);
    l->qntEl--;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }

    Lista * l = vetorPrincipal[posicao-1];

    if(l->qntEl == 0){ return ESTRUTURA_AUXILIAR_VAZIA; }

    return excluir_valor_especifico(l, valor);
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int preencherVetor(int vet[], int posicao, int i){
    No * n = vetorPrincipal[posicao-1]->inicio;

    for(i; n != NULL; n = n->prox, i++){
        vet[i] = n->conteudo;
    }

    return i;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }
    
    preencherVetor(vetorAux, posicao, 0);

    return SUCESSO;
}

void ordenarVetor(int vet[], int tamanho){
    for (int step = 1; step < tamanho; step++) {
        int key = vet[step];
        int j = step - 1;

        while (j >=0 && key < vet[j]) {
        vet[j + 1] = vet[j];
        --j;
        }
        vet[j + 1] = key;
    }
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int v = getDadosEstruturaAuxiliar(posicao, vetorAux); 
    if(v != SUCESSO){ return v; }

    ordenarVetor(vetorAux, vetorPrincipal[posicao-1]->qntEl);
    
    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int checkAllNull = 0, pos = 0;

    for(int i = 0; i < 10; i++){
        if(vetorPrincipal[i] == NULL || vetorPrincipal[i]->qntEl == 0){ checkAllNull++;} 
        else {
            pos = preencherVetor(vetorAux, i+1, pos);            
        }
    }

    if(checkAllNull == 10){ return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS; }
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int checkAllNull = 0, pos = 0;

    for(int i = 0; i < 10; i++){
        if(vetorPrincipal[i] == NULL || vetorPrincipal[i]->qntEl == 0){ checkAllNull++; }
        else{
            pos = preencherVetor(vetorAux, i+1, pos);
        }
    }

    if(checkAllNull == 10){ return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS; }

    ordenarVetor(vetorAux, pos);
    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }

    if(vetorPrincipal[posicao-1]->size + novoTamanho < 1){ return NOVO_TAMANHO_INVALIDO; }

    vetorPrincipal[posicao-1]->size += novoTamanho;
    if(novoTamanho < 0){ 
        vetorPrincipal[posicao-1]->qntEl += novoTamanho;

        No * n = vetorPrincipal[posicao-1]->inicio;
        for(int i = 1; i < vetorPrincipal[posicao-1]->qntEl; i++){
            n = n->prox;
        }
        vetorPrincipal[posicao-1]->fim = n;
    }
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    int v = validacao(posicao);
    if(v != SUCESSO){ return v; }
    if(vetorPrincipal[posicao-1]->qntEl == 0){ return ESTRUTURA_AUXILIAR_VAZIA; }
    int p = vetorPrincipal[posicao-1]->qntEl;
    return vetorPrincipal[posicao-1]->qntEl;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    No * l = malloc(sizeof(No));
    l->prox = NULL;
    int checkAllNull = 0, pos = 0;

    for(int i = 0; i < 10; i++){
        if(vetorPrincipal[i] == NULL || vetorPrincipal[i]->qntEl == 0){ checkAllNull++;} 
        else {
            No * n = vetorPrincipal[i]->inicio;
            No * posL = l, *guide = l->prox;

            while(guide != NULL){
                posL = guide;
                guide = guide->prox;
            }

            while(n != NULL){
                posL->prox = n;
                posL = posL->prox;
                n = n->prox;
            }           
        }
    }

    if(checkAllNull == 10){ return NULL; }
    return l;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No * aux = inicio->prox;

    for(int i = 0; aux != NULL; aux = aux->prox, i++){
        vetorAux[i] = aux->conteudo;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No * i = *inicio;
    No * n = i->prox;

    while(n != NULL){
        No * aux = n;
        n = n->prox;
        free(aux);
    }

    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for(int i = 0; i < TAM; i++){
        vetorPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
}