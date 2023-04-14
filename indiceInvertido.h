#ifndef HASH_ABERTO
#define HASH_ABERTO
#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Os cabeçalhos de todas as funções e os TADs podem ser alterados */

#define VAZIO " !!!!!!!!!!!!!!!!!!!!\0 "

typedef struct {
    int n; // numero de documentos
    Chave chave;
    NomeDocumento documentos[ND];
} Item;

typedef struct celula{
    struct celula *prox;
    Item item;
} Celula;

typedef struct{
    Celula *primeiro, *ultimo;
} Lista;

typedef struct{
    int n;
    int nmr_listas;
    int nmr_pesos;
    int *p;
    Lista v[M];
} IndiceInvertido;
/* Funções */

Celula * indiceInvertidoPesquisa(IndiceInvertido*, Chave);
int indiceInvertidoInsere(IndiceInvertido*, Chave);
void inicia(IndiceInvertido *);
void inserePalavras(IndiceInvertido *, int);
int insereDocumento(IndiceInvertido *, Chave, NomeDocumento);
int consulta(IndiceInvertido, Chave*, int, NomeDocumento*);
void nomenaosei(IndiceInvertido);
NomeDocumento * busca(IndiceInvertido *, Chave *, int, int *);
NomeDocumento * intersecao(NomeDocumento *, NomeDocumento *, int *, int);
void imprimeIndiceInvertido(IndiceInvertido *);
void imprimeBusca(NomeDocumento *, int);
void merge(NomeDocumento *, int, int, int);
NomeDocumento *copy(NomeDocumento *, int, int);
void mergeSort(NomeDocumento *, int, int);
int compara(char *, char *);
void liberaDocumentosEmComum(NomeDocumento ** );
void esvazia(IndiceInvertido *);
#endif // !HASH_ABERTO
