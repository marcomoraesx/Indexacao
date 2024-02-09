#include "indexing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

arvore_rb no_null;

void inicializar_rb(arvore_rb *raiz) {
    *raiz = NULL;
    no_null = (arvore_rb) malloc(sizeof(struct no_rb));
    no_null->cor = DUPLO_PRETO;
    no_null->esq = NULL;
    no_null->dir = NULL;
    no_null->pai = NULL;
}

void adicionar_rb(index_rb *valor, arvore_rb *raiz){
    arvore_rb posicao, pai, novo;
    posicao = *raiz;
    pai = NULL;
    while(posicao != NULL) {
        pai = posicao;
        if (strcmp(valor->chave, posicao->dado->chave) > 0) {
            posicao = posicao->dir;
        } else {
            posicao = posicao->esq;
        }
    }
    novo = (arvore_rb) malloc(sizeof(struct no_rb));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;
    if (eh_raiz(novo)) {
        *raiz = novo;
    } else {
        if (strcmp(valor->chave, pai->dado->chave) > 0) {
            pai->dir = novo;
        } else {
            pai->esq = novo;
        }
    }
    ajustar_rb(raiz, novo);
}

void ajustar_rb(arvore_rb *raiz, arvore_rb elemento) {
    //Buscar todas as sequências de elementos que tem a cor VERMELHO e corrigir
    while (cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
        //Recolorir
        if (cor(tio(elemento)) == VERMELHO) {
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            avo(elemento)->cor = VERMELHO;
            elemento = avo(elemento);
            continue;
        }
        //Rotação simples à direita
        if (eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_simples_direita_rb(raiz, avo(elemento));
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            continue;
        }
        //Rotação simples à esquerda
        if (eh_filho_direito(elemento) && eh_filho_direito(elemento->pai)) {
            rotacao_simples_esquerda_rb(raiz, avo(elemento));
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;
            continue;
        }
        //Rotação dupla à direita
        if (eh_filho_direito(elemento) && eh_filho_esquerdo(elemento->pai)) {
            rotacao_simples_esquerda_rb(raiz, elemento->pai);
            rotacao_simples_direita_rb(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            continue;
        }
        //Rotação dupla à esquerda
        if (eh_filho_esquerdo(elemento) && eh_filho_direito(elemento->pai)) {
            rotacao_simples_direita_rb(raiz, elemento->pai);
            rotacao_simples_esquerda_rb(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->esq->cor = VERMELHO;
            continue;
        }
    }
    //Reajustar a cor da raiz para PRETO
    (*raiz)->cor = PRETO;
}

void rotacao_simples_esquerda_rb(arvore_rb *raiz, arvore_rb pivo) {
    arvore_rb u, t1;
    u = pivo->dir;
    t1 = u->esq;
    int posicao_pivo_dir = eh_filho_direito(pivo);
    pivo->dir = t1;
    if (t1 != NULL) {
        t1->pai = pivo;
    }
    u->esq = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    if (eh_raiz(u)) {
        *raiz = u;
    } else {
        if (posicao_pivo_dir) {
            u->pai->dir = u;
        } else {
            u->pai->esq = u;
        }
    }
}

void rotacao_simples_direita_rb(arvore_rb *raiz, arvore_rb pivo) {
    arvore_rb u, t1;
    u = pivo->esq;
    t1 = u->dir;
    int posicao_pivo_esq = eh_filho_esquerdo(pivo);
    pivo->esq = t1;
    if (t1 != NULL) {
        t1->pai = pivo;
    }
    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;
    if (eh_raiz(u)) {
      *raiz = u;
    } else {
       if (posicao_pivo_esq) {
          u->pai->esq = u;
       } else {
          u->pai->dir = u;
       }
    }
}

enum cor cor(arvore_rb elemento) {
    enum cor c;
    if (elemento == NULL) {
        return PRETO;
    } else {
        return elemento->cor;
    }
    return c;
}

int eh_raiz(arvore_rb elemento) {
    return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore_rb elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

int eh_filho_direito (arvore_rb elemento) {
    return (elemento->pai != NULL && elemento == elemento->pai->dir);
}

arvore_rb irmao(arvore_rb elemento) {
    if (eh_filho_direito(elemento)) {
        return elemento->pai->esq;
    } else {
        return elemento->pai->dir;
    }
}

arvore_rb tio (arvore_rb elemento) {
    return irmao(elemento->pai);
}

arvore_rb avo(arvore_rb elemento) {
    return elemento->pai->pai;
}

int altura_rb(arvore_rb raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura_rb(raiz->dir), altura_rb(raiz->esq));
}

index_rb * maior_elemento_rb(arvore_rb raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento_rb(raiz->dir);
}

index_rb * menor_elemento_rb(arvore_rb raiz) {
	if(raiz == NULL)
			return NULL;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento_rb(raiz->esq);
}

arvore_rb buscar_rb(arvore_rb raiz, char *valor) {
    arvore_rb encontrado = NULL;
    if (raiz != NULL) {
        if (strcmp(valor, raiz->dado->chave) == 0) {
            encontrado = raiz;
            return encontrado;
        }
        if (strcmp(valor, raiz->dado->chave) > 0) {
            encontrado = buscar_rb(raiz->dir, valor);
        } else {
            encontrado = buscar_rb(raiz->esq, valor);
        }
    }
    return encontrado;
}

void imprimir_elemento_rb(arvore_rb raiz, tabela * tab) {
    if (raiz != NULL) {
        dado * temp = (dado *) malloc (sizeof(dado));
        fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
        fread(temp, sizeof(dado), 1, tab->arquivo_dados);
        printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\nEmail: %s\n", raiz->dado->chave);
        printf("Nome: %s\n", temp->nome);
        printf("Matrícula: %d\n", temp->matricula);
        printf("CPF: %s\n", temp->cpf);
        printf("Telefone: %s\n", temp->telefone);
        printf("Curso: %s\n", temp->curso);
        printf("Débito: %d\n\n", temp->debito);
        printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        free(temp);
    }
}

void pre_order_rb(arvore_rb raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento_rb(raiz, tab);
		pre_order_rb(raiz->esq, tab);
		pre_order_rb(raiz->dir, tab);
	}
}

void pos_order_rb(arvore_rb raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order_rb(raiz->esq, tab);
		pos_order_rb(raiz->dir, tab);
		imprimir_elemento_rb(raiz, tab);
	}
}

void in_order_rb(arvore_rb raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order_rb(raiz->esq, tab);
		imprimir_elemento_rb(raiz, tab);
		in_order_rb(raiz->dir, tab);
	}
}

void remover_rb(char *valor, arvore_rb *raiz) {
    arvore_rb posicao;
    posicao = *raiz;
    while (posicao != NULL) {
        if (strcmp(valor, posicao->dado->chave) == 0) {
            if (posicao->esq != NULL && posicao->dir != NULL) {
                posicao->dado = maior_elemento_rb(posicao->esq);
                remover_rb(posicao->dado->chave, &(posicao->esq));
                break;
            }
            //Possui apenas o filho direito
            if (posicao->esq == NULL && posicao->dir != NULL) {
                posicao->dir->cor = PRETO;
                posicao->dir->pai = posicao->pai;
                if (eh_raiz(posicao)) {
                    *raiz = posicao->dir;
                } else {
                    if (eh_filho_esquerdo(posicao)) {
                        posicao->pai->esq = posicao->dir;
                    } else {
                        posicao->pai->dir = posicao->dir;
                    }
                }
                free(posicao);
                break;
            }
            //Possui apenas o filho esquerdo
            if (posicao->esq != NULL && posicao->dir == NULL) {
                posicao->esq->cor = PRETO;
                posicao->esq->pai = posicao->pai;
                if (eh_raiz(posicao)) {
                    *raiz = posicao->esq;
                } else {
                    if (eh_filho_esquerdo(posicao)) {
                        posicao->pai->esq = posicao->esq;
                    } else {
                        posicao->pai->dir = posicao->esq;
                    }
                }
                free(posicao);
                break;
            }
            //Possui os dois filhos
            if (posicao->esq == NULL && posicao->dir == NULL) {
                if (eh_raiz(posicao)) {
                    *raiz = NULL;
                    free(posicao);
                    break;
                }
                if (posicao->cor == VERMELHO) {
                    if (eh_filho_esquerdo(posicao)) {
                        posicao->pai->esq = NULL;
                    } else {
                        posicao->pai->dir = NULL;
                    }
                    free(posicao);
                    break;
                } else {
                    no_null->cor = DUPLO_PRETO;
                    no_null->pai = posicao->pai;
                    if (eh_filho_esquerdo(posicao)) {
                        posicao->pai->esq = no_null;
                    } else {
                        posicao->pai->dir = no_null;
                    }
                    free(posicao);
                    reajustar_rb(raiz, no_null);
                    break;
                }
            }
        }
        if (strcmp(valor, posicao->dado->chave) > 0) {
            posicao = posicao->dir;
        } else {
            posicao = posicao->esq;
        }
    }
}

void reajustar_rb(arvore_rb *raiz, arvore_rb elemento) {
    //CASO 1 - Elemento é a raiz
    if (eh_raiz(elemento)) {
        elemento->cor = PRETO;
        if (elemento == no_null) {
            *raiz = NULL;
        }
        return;
    }
    //CASO 2 - Seu pai é PRETO, seu irmão é VERMELHO e seus sobrinhos são PRETOS
    if (cor(irmao(elemento)) == VERMELHO && cor(elemento->pai) == PRETO && cor(irmao(elemento)->esq) == PRETO && cor(irmao(elemento)->dir) == PRETO) {
        if (eh_filho_esquerdo(elemento)) {
            rotacao_simples_esquerda_rb(raiz, elemento->pai);
        } else {
            rotacao_simples_direita_rb(raiz, elemento->pai);
        }
        elemento->pai->cor = VERMELHO;
        avo(elemento)->cor = PRETO;
        reajustar_rb(raiz, elemento);
        return;
    }
    //CASO 3 - Seu pai é PRETO, seu irmão é PRETO e seus sobrinhos são PRETOS
    if (cor(elemento->pai) == PRETO && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == PRETO && cor(irmao(elemento)->dir) == PRETO) {
        elemento->pai->cor = DUPLO_PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        reajustar_rb(raiz, elemento->pai);
        return;
    }
    //CASO 4 - Seu pai é VERMELHO, seu irmão é PRETO e seus sobrinhos são PRETOS
    if (cor(elemento->pai) == VERMELHO && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == PRETO && cor(irmao(elemento)->dir) == PRETO) {
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        return;
    }
    //CASO 5a - Independe da cor do pai, seu irmão é PRETO, seu sobrinho esquerdo é VERMELHO e seu sobrinho direito é PRETO
    if (eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO && cor(irmao(elemento)->dir) == PRETO) {
        rotacao_simples_direita_rb(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->dir->cor = VERMELHO;
        reajustar_rb(raiz, elemento);
        return;
    }
    //CASO 5b - Independe da cor do pai, seu irmão é PRETO, seu sobrinho direito é VERMELHO e seu sobrinho esquerdo é PRETO
    if (eh_filho_direito(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == PRETO && cor(irmao(elemento)->dir) == VERMELHO) {
        rotacao_simples_esquerda_rb(raiz, irmao(elemento));
        irmao(elemento)->cor = PRETO;
        irmao(elemento)->esq->cor = VERMELHO;
        reajustar_rb(raiz, elemento);
        return;
    }
    //CASO 6a - Independe da cor do pai, seu irmão é PRETO, independe da cor do sobrinho esquerdo e seu sobrinho direito é VERMELHO
    if (eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO) {
        rotacao_simples_esquerda_rb(raiz, elemento->pai);
        avo(elemento)->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);
        return;
    }
    //CASO 6b - Independe da cor do pai, seu irmão é PRETO, independe da cor do sobrinho direito e seu sobrinho esquerdo é VERMELHO
    if (eh_filho_direito(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO) {
        rotacao_simples_direita_rb(raiz, elemento->pai);
        avo(elemento)->cor = elemento->pai->cor;
        elemento->pai->cor = PRETO;
        irmao(elemento->pai)->cor = PRETO;
        retira_duplo_preto(raiz, elemento);
        return;
    }
}

void retira_duplo_preto(arvore_rb *raiz, arvore_rb elemento) {
    if (elemento == no_null) {
        if (eh_filho_esquerdo(elemento)) {
            elemento->pai->esq = NULL;
        } else {
            elemento->pai->dir = NULL;
        }
    } else {
        elemento->cor = PRETO;
    }
}

void salvar_arquivo_rb(char *nome, arvore_rb a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar_rb(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_rb(arvore_rb raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(index_rb), 1, arq);
		salvar_auxiliar_rb(raiz->esq, arq);
		salvar_auxiliar_rb(raiz->dir, arq);
	}
}

arvore_rb carregar_arquivo_rb(char *nome, arvore_rb a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	index_rb * temp;
	if(arq != NULL) {
		temp = (index_rb *) malloc(sizeof(index_rb));
		while(fread(temp, sizeof(index_rb), 1, arq)) {
            adicionar_rb(temp, &a);
			temp = (index_rb *) malloc(sizeof(index_rb));
		}
		fclose(arq);
	}
	return a;
}
