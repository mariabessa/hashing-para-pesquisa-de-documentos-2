#include "indiceInvertido.h"

int main() {
    IndiceInvertido indiceInvertido;
    int numeroDocumentoInseridos, numPalavrasBuscadas;
    Chave aux[MAX_STR];
    inicia(&indiceInvertido);
    scanf("%d ", &numeroDocumentoInseridos);
    inserePalavras(&indiceInvertido, numeroDocumentoInseridos);
    numPalavrasBuscadas = pegarChaves(aux);
    if(strcmp(aux[0], "B") == 0){
        int tamanho;
        NomeDocumento * documentosEmComum = busca(&indiceInvertido, aux, numPalavrasBuscadas, &tamanho);
        if (tamanho==0){
            printf("none\n");
        }else if(tamanho == 1){
            imprimeBusca(documentosEmComum, tamanho);
        }else{
            mergeSort(documentosEmComum, 0, tamanho-1);
            imprimeBusca(documentosEmComum, tamanho);
        }
        liberaDocumentosEmComum(&documentosEmComum);
    }else{
        imprimeIndiceInvertido(&indiceInvertido);
    }
    esvazia(&indiceInvertido);
    return 0;
}
