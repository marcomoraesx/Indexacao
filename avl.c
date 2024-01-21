#include "indexing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void inicializar_avl(arvore_avl *raiz) {
    *raiz = NULL;
}

arvore_avl adicionar_avl(arvore_avl raiz, tipo_dado *valor, int *cresceu){
    if(raiz == NULL) {
        arvore_avl nova = (arvore_avl) malloc(sizeof(struct no_avl));
        nova->dado = valor;
        nova->esq = NULL;
        nova->dir = NULL;
        nova->fb = 0;
        *cresceu = 1;
        return nova;
    } else {
        if(valor > raiz->dado->chave) {
            raiz->dir = adicionar_avl(raiz->dir, valor, cresceu);
            if (*cresceu) {
                //Atualização dos Fatores de Balanço após a árvore à direita crescer
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *cresceu = 1;
                        break;
                    case 1:
                        *cresceu = 0;
                        return rotacao_avl(raiz);
                        break;
                    case -1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                }
            }
        } else {
            raiz->esq = adicionar_avl(raiz->esq, valor, cresceu);
            if (*cresceu) {
            //Atualização dos Fatores de Balanço após a árvore à esquerda crescer
                switch (raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *cresceu = 1;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *cresceu = 0;
                        break;
                    case -1:
                        *cresceu = 0;
                        return rotacao_avl(raiz);
                        break;
                }
            }
        }
        return raiz;
    }
}

arvore_avl rotacao_avl(arvore_avl pivo) {
    if (pivo->fb > 0) {
        //Rotações à Esquerda
        if (pivo->dir->fb >= 0) {
            //Rotação Simples à Esquerda
            if (pivo->dir->fb == 0) {
                pivo->fb = 1;
                pivo->dir->fb = -1;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
            }
            return rotacao_simples_esquerda_avl(pivo);
        } else {
            //Rotação Dupla à Esquerda
            if (pivo->dir->esq->fb < 0) {
                pivo->fb = 0;
                pivo->dir->fb = 1;
                pivo->dir->esq->fb = 0;
            } else if (pivo->dir->esq->fb > 0){
                pivo->fb = -1;
                pivo->dir->fb = 0;
                pivo->dir->esq->fb = 0;
            } else {
                pivo->fb = 0;
                pivo->dir->fb = 0;
                pivo->dir->esq->fb = 0;
            }
            return rotacao_dupla_esquerda_avl(pivo);
        }
    } else {
        //Rotações à Direita
        if (pivo->esq->fb <= 0) {
            //Rotação Simples à Direita
            if (pivo->esq->fb == 0) {
                pivo->fb = -1;
                pivo->esq->fb = 1;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
            }
            return rotacao_simples_direita_avl(pivo);
        } else {
            //Rotação Dupla à Direita
            if (pivo->esq->dir->fb < 0) {
                pivo->fb = 1;
                pivo->esq->fb = 0;
                pivo->esq->dir->fb = 0;
            } else if (pivo->esq->dir->fb > 0) {
                pivo->fb = 0;
                pivo->esq->fb = -1;
                pivo->esq->dir->fb = 0;
            } else {
                pivo->fb = 0;
                pivo->esq->fb = 0;
                pivo->esq->dir->fb = 0;
            }
            return rotacao_dupla_direita_avl(pivo);
        }
    }
}

arvore_avl rotacao_simples_esquerda_avl(arvore_avl pivo) {
    arvore_avl u, t1, t2, t3;
    u = pivo->dir;
    t1 = pivo->esq;
    t2 = u->esq;
    t3 = u->dir;
    u->esq = pivo;
    pivo->dir = t2;
    return u;
}

arvore_avl rotacao_simples_direita_avl(arvore_avl pivo) {
    arvore_avl u, t1, t2, t3;
    u = pivo->esq;
    t1 = pivo->dir;
    t2 = u->esq;
    t3 = u->dir;
    u->dir = pivo;
    pivo->esq = t3;
    return u;
}

arvore_avl rotacao_dupla_direita_avl(arvore_avl pivo) {
    pivo->esq = rotacao_simples_esquerda_avl(pivo->esq);
    return rotacao_simples_direita_avl(pivo);
}

arvore_avl rotacao_dupla_esquerda_avl(arvore_avl pivo) {
    pivo->dir = rotacao_simples_direita_avl(pivo->dir);
    return rotacao_simples_esquerda_avl(pivo);
}

arvore_avl remover_avl(arvore_avl raiz, int valor, int *caiu) {
    if (raiz != NULL) {
        if (raiz->dado->chave == valor) {
            if (raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                *caiu = 1;
                return NULL;
            }
            if (raiz->esq != NULL && raiz->dir == NULL) {
                arvore_avl temp = raiz->esq;
                free(raiz);
                *caiu = 1;
                return temp;
            }
            if (raiz->dir != NULL && raiz->esq == NULL) {
                arvore_avl temp = raiz->dir;
                free(raiz);
                *caiu = 1;
                return temp;
            }
            raiz->dado = menor_elemento_avl(raiz->dir);
            raiz->dir = remover_avl(raiz->dir, raiz->dado->chave, caiu);
            if (*caiu) {
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *caiu = 0;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                    case -1:
                        if (raiz->esq->fb == 0) {
                            *caiu = 0;
                        } else {
                            *caiu = 1;
                        }
                        return rotacao_avl(raiz);
                        break;
                }
            }
            return raiz;
        } else if (valor < raiz->dado->chave) {
            raiz->esq = remover_avl(raiz->esq, valor, caiu);
            if (*caiu) {
                //Atualização dos Fatores de Balanço após a árvore à esquerda diminuir
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = 1;
                        *caiu = 0;
                        break;
                    case 1:
                        if (raiz->dir->fb == 0) {
                            *caiu = 0;
                        } else {
                            *caiu = 1;
                        }
                        return rotacao_avl(raiz);
                        break;
                    case -1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                }
                return raiz;
            }
        } else {
            raiz->dir = remover_avl(raiz->dir, valor, caiu);
            if (*caiu) {
                //Atualização dos Fatores de Balanço após a árvore à direita diminuir
                switch(raiz->fb) {
                    case 0:
                        raiz->fb = -1;
                        *caiu = 0;
                        break;
                    case 1:
                        raiz->fb = 0;
                        *caiu = 1;
                        break;
                    case -1:
                        if (raiz->esq->fb == 0) {
                            *caiu = 0;
                        } else {
                            *caiu = 1;
                        }
                        return rotacao_avl(raiz);
                        break;
                }
                return raiz;
            }
        }
    }
    *caiu = 0;
    return raiz;
}

void imprimir_elemento_avl(arvore_avl raiz, tabela * tab) {
	dado * temp = (dado *) malloc (sizeof(dado));
   	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
	int r = fread(temp, sizeof(dado), 1, tab->arquivo_dados);
	printf("[%d, %d, %s, %s, %s ]\n", raiz->dado->chave,r, temp->titulo, temp->autor, temp->isbn);
	free(temp);
}

void pre_order_avl(arvore_avl raiz) {
	if(raiz != NULL) {
		imprimir_elemento_avl(raiz);
		pre_order_avl(raiz->esq);
		pre_order_avl(raiz->dir);
	}
}

void pos_order_avl(arvore_avl raiz) {
	if(raiz != NULL) {
		pos_order_avl(raiz->esq);
		pos_order_avl(raiz->dir);
		imprimir_elemento_avl(raiz);
	}
}

void in_order_avl(arvore_avl raiz) {
	if(raiz != NULL) {
		in_order_avl(raiz->esq);
		imprimir_elemento_avl(raiz);
		in_order_avl(raiz->dir);
	}
}

tipo_dado * maior_elemento_avl(arvore_avl raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento_avl(raiz->dir);
}

tipo_dado * menor_elemento_avl(arvore_avl raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento_avl(raiz->esq);
}

int altura_avl(arvore_avl raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura_avl(raiz->dir), altura_avl(raiz->esq));
}

void salvar_arquivo_avl(char *nome, arvore_avl a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar_avl(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_avl(arvore_avl raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar_avl(raiz->esq, arq);
		salvar_auxiliar_avl(raiz->dir, arq);
	}
}

arvore_avl carregar_arquivo_avl(char *nome, arvore_avl a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {
            a = adicionar_avl(a, temp, 0);
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		}
		fclose(arq);
	}
	return a;
}
