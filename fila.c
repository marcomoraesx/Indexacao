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
    fila novo = (fila) malloc(sizeof(fila));
    if(f == NULL) {
        novo->indice = valor;
        novo->proximo = f;
        return novo;
    }
    while(aux->proximo != NULL) {
        aux = aux->proximo;
    }
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

void salvar_arquivo_fila(char *nome, fila f) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar_fila(f, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_fila(fila f, FILE *arq){
	if(f != NULL) {
		fwrite(f->indice, sizeof(no_fila), 1, arq);
		salvar_auxiliar_fila(f->proximo, arq);
	}
}

fila carregar_arquivo_fila(char *nome, fila f) {
	FILE *arq;
	arq = fopen(nome, "rb");
	no_fila * temp;
	if(arq != NULL) {
		temp = (no_fila *) malloc(sizeof(no_fila));
		while(fread(temp, sizeof(no_fila), 1, arq)) {
            f = enqueue(f, temp->indice);
			temp = (no_fila *) malloc(sizeof(no_fila));
		}
		fclose(arq);
	}
	return f;
}
