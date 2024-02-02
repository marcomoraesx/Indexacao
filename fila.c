#include <stdio.h>
#include <stdlib.h>
#include "indexing.h"

void inicializar_fila(fila f) {
    f = NULL;
}

void exibir_fila(fila f){
    fila aux = f;
    while(aux != NULL) {
        printf("[%d]", aux->indice);
        aux = aux->proximo;
    }
    printf("\n");
}

fila enqueue(fila f, int valor) {
    fila aux = f;
    if(f == NULL) {
        //Inserir o primeiro elemento da fila!!!
        //return inserir_inicio(f, valor);
    }

    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
    fila novo = (fila) malloc(sizeof(no_fila));
    novo->indice = valor;
    novo->proximo = NULL;

    aux->proximo = novo;
    return f;
}

fila dequeue(fila f) {
    if(f == NULL)
        return NULL;
    fila aux = f->proximo;
    free(f);
    return aux;
}
