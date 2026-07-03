/* Louvado seja o Senhor */

#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

Lista * vetorPrincipal[TAM];

No * criar_no(int num){
    No * n = malloc(sizeof(No));

    n->conteudo = num;
    n->prox = n->ant = NULL;

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
        n->ant = l->fim;
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
    No * n = l->fim;

    l->fim = n->ant;
    if(n == l->inicio){
        l->inicio = NULL;
    }
    else{
        n->ant->prox = NULL;
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
    No * n = buscar_no_valor(l->inicio, valor);

    if(n == NULL){ return NUMERO_INEXISTENTE; }

    if(n == l->inicio){
        l->inicio = n->prox;

        if(n == l->fim){
            l->fim = NULL;
        }
        else{
            n->prox->ant = NULL;
        }
    }
    else if(n == l->fim){
        excluir_valor_final(l);
    }
    else{
        n->ant->prox = n->prox;
        n->prox->ant = n->ant;
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

        for(int i = -novoTamanho; i > 0; i--){
            vetorPrincipal[posicao-1]->fim = vetorPrincipal[posicao-1]->fim->ant;
        }
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
    l->prox = l ->ant = NULL;
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

void testeInserirSemNada();
void testeCriarEstrutura();
void testeInserirComEstrutura();
void testeExcluir();
void testeExcluirNumeroEspecifico();
void testeListar();
void testeRetornarTodosNumeros();
void testeMudarTamanhoEstrutura();
void testeListaEncadeada();


int main()
{
    inicializar();
    testeInserirSemNada();
    testeCriarEstrutura();
    testeInserirComEstrutura();
    testeExcluir();
    testeExcluirNumeroEspecifico();
    testeListar();
    testeRetornarTodosNumeros();
    testeMudarTamanhoEstrutura();
    testeListaEncadeada();
}

void testeInserirSemNada()
{
    printf("%d\n", inserirNumeroEmEstrutura(2, 2) == SEM_ESTRUTURA_AUXILIAR);
    printf("%d\n", inserirNumeroEmEstrutura(-2, 2) == POSICAO_INVALIDA);
    printf("%d\n", inserirNumeroEmEstrutura(0, 2) == POSICAO_INVALIDA);
    printf("%d\n", inserirNumeroEmEstrutura(11, 2) == POSICAO_INVALIDA);
}

void testeCriarEstrutura()
{
    printf("%d\n", criarEstruturaAuxiliar(-2, 5) == POSICAO_INVALIDA);
    printf("%d\n", criarEstruturaAuxiliar(0, 5) == POSICAO_INVALIDA);
    printf("%d\n", criarEstruturaAuxiliar(11, 5) == POSICAO_INVALIDA);
    printf("%d\n", criarEstruturaAuxiliar(2, -5) == TAMANHO_INVALIDO);
    printf("%d\n", criarEstruturaAuxiliar(2, 0) == TAMANHO_INVALIDO);
    printf("%d\n", criarEstruturaAuxiliar(2, 3) == SUCESSO);
    printf("%d\n", criarEstruturaAuxiliar(2, 6) == JA_TEM_ESTRUTURA_AUXILIAR);
}
/*
2 [ , , ]
*/

void testeInserirComEstrutura()
{
    //###  int inserirNumeroEmEstrutura(int valor, int posicao); ###
    printf("%d\n", inserirNumeroEmEstrutura(2, 4) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, -2) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 6) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 5) == SEM_ESPACO);
}

void testeExcluir()
{
    //###  int excluirNumeroDoFinaldaEstrutura(int posicao); ###
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == SUCESSO);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == SUCESSO);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(0) == POSICAO_INVALIDA);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(1) == SEM_ESTRUTURA_AUXILIAR);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == SUCESSO);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == ESTRUTURA_AUXILIAR_VAZIA);
}

/*
2 [ , , ]
*/

void testeExcluirNumeroEspecifico()
{
    //###  int excluirNumeroEspecificoDeEstrutura(int posicao, int valor); ###
    printf("%d\n", criarEstruturaAuxiliar(9, 3) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(9, 7) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(9, 4) == SUCESSO);
    printf("%d\n", excluirNumeroEspecificoDeEstrutura(9, 12) == NUMERO_INEXISTENTE);
    printf("%d\n", excluirNumeroEspecificoDeEstrutura(9, 7) == SUCESSO);
    printf("%d\n", excluirNumeroEspecificoDeEstrutura(9, 4) == SUCESSO);
    printf("%d\n", excluirNumeroEspecificoDeEstrutura(1, 2) == SEM_ESTRUTURA_AUXILIAR);
}

void testeListar()
{
    //###  int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]); ###
    printf("%d\n", inserirNumeroEmEstrutura(2, 7) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, -9) == SUCESSO);

    int vet[2];

    printf("%d\n", getDadosEstruturaAuxiliar(1, vet) == SEM_ESTRUTURA_AUXILIAR);
    printf("%d\n", getDadosEstruturaAuxiliar(11, vet) == POSICAO_INVALIDA);
    printf("%d\n", getDadosEstruturaAuxiliar(2, vet) == SUCESSO);

    printf("%d\n", vet[0] == 7);
    printf("%d\n", vet[1] == -9);

    printf("%d\n", getDadosOrdenadosEstruturaAuxiliar(1, vet) == SEM_ESTRUTURA_AUXILIAR);
    printf("%d\n", getDadosOrdenadosEstruturaAuxiliar(11, vet) == POSICAO_INVALIDA);
    printf("%d\n", getDadosOrdenadosEstruturaAuxiliar(2, vet) == SUCESSO);

    printf("%d\n", vet[0] == -9);
    printf("%d\n", vet[1] == 7);

    printf("%d\n", getDadosEstruturaAuxiliar(2, vet) == SUCESSO);

    printf("%d\n", vet[0] == 7);
    printf("%d\n", vet[1] == -9);

    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == SUCESSO);
    printf("%d\n", excluirNumeroDoFinaldaEstrutura(2) == SUCESSO);
}

/*
2 [ , , ]
*/

void testeRetornarTodosNumeros()
{
    int vet1[2];
    printf("%d\n", getDadosDeTodasEstruturasAuxiliares(vet1) == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS);

    printf("%d\n", getDadosOrdenadosDeTodasEstruturasAuxiliares(vet1) == TODAS_ESTRUTURAS_AUXILIARES_VAZIAS);

    printf("%d\n", inserirNumeroEmEstrutura(2, 3) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 8) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 0) == SUCESSO);
    /*
2 [3,8,0]
*/

    printf("%d\n", criarEstruturaAuxiliar(5, 10) == SUCESSO);

    printf("%d\n", inserirNumeroEmEstrutura(5, 1) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(5, 34) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(5, 12) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(5, 6) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(5, 27) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(5, -6) == SUCESSO);
    /*
2 [3,8,0]
5 [1,34,12,6,27,-6, , , , ]
*/
    int vet[9];

    printf("%d\n", getDadosDeTodasEstruturasAuxiliares(vet) == SUCESSO);

    printf("%d\n", vet[0] == 3);
    printf("%d\n", vet[1] == 8);
    printf("%d\n", vet[2] == 0);
    printf("%d\n", vet[3] == 1);
    printf("%d\n", vet[4] == 34);
    printf("%d\n", vet[5] == 12);
    printf("%d\n", vet[6] == 6);
    printf("%d\n", vet[7] == 27);
    printf("%d\n", vet[8] == -6);

    int vet2[9];

    printf("%d\n", getDadosOrdenadosDeTodasEstruturasAuxiliares(vet2) == SUCESSO);

    printf("%d\n", vet2[0] == -6);
    printf("%d\n", vet2[1] == 0);
    printf("%d\n", vet2[2] == 1);
    printf("%d\n", vet2[3] == 3);
    printf("%d\n", vet2[4] == 6);
    printf("%d\n", vet2[5] == 8);
    printf("%d\n", vet2[6] == 12);
    printf("%d\n", vet2[7] == 27);
    printf("%d\n", vet2[8] == 34);

    printf("%d\n", getDadosDeTodasEstruturasAuxiliares(vet) == SUCESSO);

    printf("%d\n", vet[0] == 3);
    printf("%d\n", vet[1] == 8);
    printf("%d\n", vet[2] == 0);
    printf("%d\n", vet[3] == 1);
    printf("%d\n", vet[4] == 34);
    printf("%d\n", vet[5] == 12);
    printf("%d\n", vet[6] == 6);
    printf("%d\n", vet[7] == 27);
    printf("%d\n", vet[8] == -6);
}
/*
2 [3,8,0]
5 [1,34,12,6,27,-6, , , , ]
*/

/*
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho);
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
void testeMudarTamanhoEstrutura()
{
    int vet[1];
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(2, -3) == NOVO_TAMANHO_INVALIDO);
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(2, -4) == NOVO_TAMANHO_INVALIDO);
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(11, 7) == POSICAO_INVALIDA);
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(0, 7) == POSICAO_INVALIDA);
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(1, 7) == SEM_ESTRUTURA_AUXILIAR);

    //modificar para tamanho de 3 para 1
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(2, -2) == SUCESSO);
    printf("%d\n", getQuantidadeElementosEstruturaAuxiliar(2) == 1);
    printf("%d\n", getDadosEstruturaAuxiliar(2, vet) == SUCESSO);
    printf("%d\n", vet[0] == 3);

    //modificar para tamanho de 1 para 4
    printf("%d\n", modificarTamanhoEstruturaAuxiliar(2, 3) == SUCESSO);
    printf("%d\n", getQuantidadeElementosEstruturaAuxiliar(2) == 1);
    printf("%d\n", getDadosEstruturaAuxiliar(2, vet) == SUCESSO);
    printf("%d\n", vet[0] == 3);

    printf("%d\n", inserirNumeroEmEstrutura(2, 4) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, -2) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 6) == SUCESSO);
    printf("%d\n", inserirNumeroEmEstrutura(2, 5) == SEM_ESPACO);
}

/*
2 [3,4,-2,6]
5 [1,34,12,6,27,-6, , , , ]
*/

void testeListaEncadeada()
{
    int vet[10];
    No *inicio = montarListaEncadeadaComCabecote();
    getDadosListaEncadeadaComCabecote(inicio, vet);

    printf("%d\n", vet[0] == 3);
    printf("%d\n", vet[1] == 4);
    printf("%d\n", vet[2] == -2);
    printf("%d\n", vet[3] == 6);
    printf("%d\n", vet[4] == 1);
    printf("%d\n", vet[5] == 34);
    printf("%d\n", vet[6] == 12);
    printf("%d\n", vet[7] == 6);
    printf("%d\n", vet[8] == 27);
    printf("%d\n", vet[9] == -6);

    destruirListaEncadeadaComCabecote(&inicio);

    printf("%d\n", inicio == NULL);
}