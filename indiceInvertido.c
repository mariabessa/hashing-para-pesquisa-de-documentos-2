#include "indiceInvertido.h"


void inicia(IndiceInvertido *indiceInvertido){
    for(int i = 0; i < M; i++){
        indiceInvertido->v[i].primeiro = malloc(sizeof(Celula));
        indiceInvertido->v[i].ultimo = indiceInvertido->v[i].primeiro;
        indiceInvertido->v[i].primeiro->prox = NULL;
    }
}

int Lista_Eh_Vazia(Lista *lista){
    return(lista->ultimo == lista->primeiro);
}

Celula * indiceInvertidoPesquisa(IndiceInvertido *indiceInvertido, Chave chave){
    int ini = h(chave);
    Celula *aux;
    if (Lista_Eh_Vazia(&indiceInvertido->v[ini])){
        return NULL;
    }
    aux = indiceInvertido->v[ini].primeiro;
    while(aux->prox->prox != NULL && strcmp(chave, aux->prox->item.chave) != 0){
        aux = aux->prox;
    }if (!strcmp(chave, aux->prox->item.chave))
        return aux;
    else
        return NULL;
}

void inserePalavras(IndiceInvertido *indiceInvertido, int numeroDocumentoInseridos){
    Chave aux[MAX_STR];
    char nomeDocumento[D];
    for(int i = 0; i < numeroDocumentoInseridos; i++){
        int numeroPalavrasInseridas = pegarChaves(aux);
        strcpy(nomeDocumento, aux[0]);
        for(int j = 1; j < numeroPalavrasInseridas; j++){
            indiceInvertidoInsere(indiceInvertido, aux[j]);
            insereDocumento(indiceInvertido, aux[j], nomeDocumento);
        }
    }
}

void TLista_Insere(Lista *lista, Chave chave){
    Celula * new = malloc(sizeof(Celula));
    strcpy(new->item.chave, chave);
    new->prox = NULL;
    lista->ultimo->prox = new;
    lista->ultimo = new;
}

int indiceInvertidoInsere(IndiceInvertido * indiceInvertido, Chave chave){
    if(indiceInvertidoPesquisa(indiceInvertido, chave ) == NULL ) {
        TLista_Insere(&indiceInvertido->v[h(chave)], chave);
        return 1;
    }
    return 0;
}

int insereDocumento(IndiceInvertido *indiceInvertido, Chave chave, NomeDocumento documento){
    Celula *aux = indiceInvertidoPesquisa(indiceInvertido, chave);
    strcpy(aux->prox->item.documentos[aux->prox->item.n], documento);
    aux->prox->item.n++;
    return 1;   
}

NomeDocumento * busca(IndiceInvertido *indiceInvertido, Chave *aux1, int numPalavrasBuscadas, int *tamanho){
    Celula *aux = indiceInvertidoPesquisa(indiceInvertido, aux1[1]);
    (*tamanho) = aux->prox->item.n;
    NomeDocumento *auxNome;
    NomeDocumento *documentosEmComum = malloc(sizeof(NomeDocumento) * (*tamanho));
    for(int i = 0; i < (*tamanho); i++){
        strcpy(documentosEmComum[i], aux->prox->item.documentos[i]);
    }
    if (numPalavrasBuscadas == 2){
        return documentosEmComum;
    }else{
        for(int i = 2; i < numPalavrasBuscadas; i++){
            Celula * aux = indiceInvertidoPesquisa(indiceInvertido, aux1[i]);
            auxNome = documentosEmComum;
            documentosEmComum = intersecao(documentosEmComum, aux->prox->item.documentos, tamanho, aux->prox->item.n);
            free(auxNome);
        }
    }
    return documentosEmComum;
}

NomeDocumento * intersecao(NomeDocumento * documentosEmComum, NomeDocumento * indiceInvertido, int *tamanho, int tamanho2){
    NomeDocumento * resultado = malloc(sizeof(NomeDocumento) * (*tamanho));
    int aux = 0;
    for (int i = 0; i < (*tamanho); i++) {
        for (int j = 0; j < tamanho2; j++) {
            if (strcmp(documentosEmComum[i], indiceInvertido[j]) == 0) {
                aux++;
                strcpy(resultado[aux-1], documentosEmComum[i]);
            }
        }
    }
    (*tamanho) = aux;
    return resultado;
}

void imprimeBusca(NomeDocumento *documentosEmComum, int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%s\n", documentosEmComum[i]);
    }
}

void imprimeIndiceInvertido(IndiceInvertido *indiceInvertido){
    for(int i = 0; i < M; i++){
        if(Lista_Eh_Vazia(&indiceInvertido->v[i])){
            continue;
        }else{
            Celula *aux;
            aux = indiceInvertido->v[i].primeiro->prox;
            while(aux != NULL){
                printf("%s - ", aux->item.chave);
                for(int j = 0; j < aux->item.n; j++){
                    printf("%s ", aux->item.documentos[j]);
                }printf("\n");
                aux = aux->prox;
            }
        }
    }
}

void mergeSort(NomeDocumento *documentos, int l, int r){
    if(l<r){
        int m = (l+r)/2;
        mergeSort(documentos, l, m);
        mergeSort(documentos, m+1, r);
        merge(documentos, l, r, m);
    }
}

void merge(NomeDocumento *documentos, int l, int r, int m){
    int tam_l= m - l + 1;
    int tam_r = r - m;
    NomeDocumento *vL = copy(documentos, tam_l, l);
    NomeDocumento *vR = copy(documentos, tam_r, m+1);
    int i = 0, j = 0, k;
    for(k=l; k<=r; k++){
        if(i==tam_l){
            strcpy(documentos[k], vR[j++]); 
        }else if(j==tam_r){
            strcpy(documentos[k], vL[i++]); 
        }else if(compara(vL[i], vR[j])){
            strcpy(documentos[k], vL[i++]);  
        }else{
            strcpy(documentos[k], vR[j++]); 
        }
    }
    free(vR);
    free(vL);
}

NomeDocumento *copy(NomeDocumento *NomeDocumentos, int tamanho, int n){
    NomeDocumento *aux = malloc(sizeof(NomeDocumento) * tamanho);
    for (int i = 0; i < tamanho; i++){ 
        strcpy(aux[i], NomeDocumentos[i+n]); 
    }
    return aux;
}

int compara(char * nomeUm, char * nomeDois){
    if (strcmp(nomeUm, nomeDois) < 0)
        return 1;
    return 0;
}

void liberaDocumentosEmComum(NomeDocumento ** documentosEmComum){
    free(*documentosEmComum);
}

void esvazia(IndiceInvertido *indiceInvertido){
    Celula *aux1, *aux2;
    for(int i = 0; i < M; i++){
        aux1 = indiceInvertido->v[i].primeiro;
        while(aux1!=NULL){
            aux2 = aux1;
            aux1= aux1->prox;
            free(aux2);
        }
    }
}