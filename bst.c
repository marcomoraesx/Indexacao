#include "indexing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inicializar_bst(arvore_bst *raiz) {
    *raiz = NULL;
}

arvore_bst adicionar_bst(tipo_dado *valor, arvore_bst raiz){
    if(raiz == NULL) {
        arvore_bst nova = (arvore_bst) malloc(sizeof(struct no_bst));
        nova->dado = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    } else {
        if(strcmpi(valor->chave, raiz->dado->chave) > 0) {
            raiz->dir = adicionar_bst(valor, raiz->dir);
        } else {
            raiz->esq = adicionar_bst(valor, raiz->esq);
        }
        return raiz;
    }
}

arvore_bst remover_bst(char *valor, arvore_bst raiz) {
	if(raiz == NULL)
		return NULL;

	if(strcmpi(valor, raiz->dado->chave)) {
		if(raiz->esq == NULL) {
			return raiz->dir;
		}
		if(raiz->dir == NULL) {
			return raiz->esq;
		}
		raiz->dado = maior_elemento_bst(raiz->esq);
		raiz->esq = remover_bst(raiz->dado->chave, raiz->esq);
		return raiz;
	}
	if(strcmpi(valor, raiz->dado->chave) > 0) {
			raiz->dir = remover_bst(valor, raiz->dir);
	} else {
			raiz->esq = remover_bst(valor, raiz->esq);
	}
	return raiz;
}

void imprimir_elemento_bst(arvore_bst raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);
	printf("[%d, %d, %s, %s, %s ]\n", raiz->dado->chave,r, temp->titulo, temp->autor, temp->isbn);
	free(temp);
}

void pre_order_bst(arvore_bst raiz) {
	if(raiz != NULL) {
		imprimir_elemento_bst(raiz);
		pre_order_bst(raiz->esq);
		pre_order_bst(raiz->dir);
	}
}

void pos_order_bst(arvore_bst raiz) {
	if(raiz != NULL) {
		pos_order_bst(raiz->esq);
		pos_order_bst(raiz->dir);
		imprimir_elemento_bst(raiz);
	}
}

void in_order_bst(arvore_bst raiz) {
	if(raiz != NULL) {
		in_order_bst(raiz->esq);
		imprimir_elemento_bst(raiz);
		in_order_bst(raiz->dir);
	}
}

tipo_dado * maior_elemento_bst(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento_bst(raiz->dir);
}

tipo_dado * menor_elemento_bst(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento_bst(raiz->esq);
}

int altura_bst(arvore_bst raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura_bst(raiz->dir), altura_bst(raiz->esq));
}

void salvar_arquivo_bst(char *nome, arvore_bst a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar_bst(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_bst(arvore_bst raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_bst(raiz->esq, arq);
		salvar_auxiliar_bst(raiz->dir, arq);
	}
}

arvore_bst carregar_arquivo_bst(char *nome, arvore_bst a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            a = adicionar_bst(temp, a);
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		}
		fclose(arq);
	}
	return a;
}
