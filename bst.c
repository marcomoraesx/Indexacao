#include "indexing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inicializar_bst(arvore_bst raiz) {
    raiz = NULL;
}

arvore_bst adicionar_bst(index_bst *valor, arvore_bst raiz){
    if(raiz == NULL) {
        arvore_bst nova = (arvore_bst) malloc(sizeof(struct no_bst));
        nova->dado = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    } else {
        if(strcmp(valor->chave, raiz->dado->chave) > 0) {
            raiz->dir = adicionar_bst(valor, raiz->dir);
        } else {
            raiz->esq = adicionar_bst(valor, raiz->esq);
        }
        return raiz;
    }
}

arvore_bst remover_bst(char *valor, arvore_bst raiz) {
  if (raiz != NULL) {
        if (strcmp(valor, raiz->dado->chave) == 0) {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }
            if (raiz->esq != NULL && raiz->dir == NULL) {
                arvore_bst temp = raiz->esq;
                free(raiz);
                return temp;
            }
            if (raiz->dir != NULL && raiz->esq == NULL) {
                arvore_bst temp = raiz->dir;
                free(raiz);
                return temp;
            }
            raiz->dado = menor_elemento_bst(raiz->dir);
            raiz->dir = remover_bst(raiz->dado->chave, raiz->dir);
            return raiz;
        } else if (strcmp(valor, raiz->dado->chave) > 0) {
            raiz->dir = remover_bst(valor, raiz->dir);
        } else {
            raiz->esq = remover_bst(valor, raiz->esq);
        }
    }
    return raiz;
}

arvore_bst buscar_bst(arvore_bst raiz, char *valor) {
    arvore_bst encontrado = NULL;
    if (raiz != NULL) {
        if (strcmp(valor, raiz->dado->chave) == 0) {
            encontrado = raiz;
            return encontrado;
        }
        if (strcmp(valor, raiz->dado->chave) > 0) {
            encontrado = buscar_bst(raiz->dir, valor);
        } else {
            encontrado = buscar_bst(raiz->esq, valor);
        }
    }
    return encontrado;
}

void imprimir_elemento_bst(arvore_bst raiz, tabela * tab) {
    if (raiz != NULL) {
        dado * temp = (dado *) malloc (sizeof(dado));
        fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
        fread(temp, sizeof(dado), 1, tab->arquivo_dados);
        printf("\nCPF: %s\n", raiz->dado->chave);
        printf("Nome: %s\n", temp->nome);
        printf("Matrícula: %d\n", temp->matricula);
        printf("Email: %s\n", temp->email);
        printf("Telefone: %s\n", temp->telefone);
        printf("Curso: %s\n", temp->curso);
        printf("Débito: %d\n\n", temp->debito);
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        free(temp);
	}
}

void pre_order_bst(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento_bst(raiz, tab);
		pre_order_bst(raiz->esq, tab);
		pre_order_bst(raiz->dir, tab);
	}
}

void pos_order_bst(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order_bst(raiz->esq, tab);
		pos_order_bst(raiz->dir, tab);
		imprimir_elemento_bst(raiz, tab);
	}
}

void in_order_bst(arvore_bst raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order_bst(raiz->esq, tab);
		imprimir_elemento_bst(raiz, tab);
		in_order_bst(raiz->dir, tab);
	}
}

index_bst * maior_elemento_bst(arvore_bst raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento_bst(raiz->dir);
}

index_bst * menor_elemento_bst(arvore_bst raiz) {
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
		fwrite(raiz->dado, sizeof(index_bst), 1, arq);
		salvar_auxiliar_bst(raiz->esq, arq);
		salvar_auxiliar_bst(raiz->dir, arq);
	}
}

arvore_bst carregar_arquivo_bst(char *nome, arvore_bst a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	index_bst * temp;
	if(arq != NULL) {
		temp = (index_bst *) malloc(sizeof(index_bst));
		while(fread(temp, sizeof(index_bst), 1, arq)) {
            a = adicionar_bst(temp, a);
			temp = (index_bst *) malloc(sizeof(index_bst));
		}
		fclose(arq);
	}
	return a;
}
