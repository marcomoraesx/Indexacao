#ifndef INDEXING_H
#define INDEXING_H
#include <stdio.h>

typedef struct estudante {
	char nome[255];
	char cpf[20];
	int matricula;
	char telefone[20];
    char email[127];
    char curso[50];
    int debito;
} dado;

typedef struct indice_bst {
	char chave[20];
	int indice;
} index_bst;

typedef struct no_bst{
	index_bst *dado;
	struct no_bst *esq, *dir;
} no_bst;

typedef no_bst * arvore_bst;

typedef struct indice_avl {
	int chave;
	int indice;
} index_avl;

typedef struct no_avl {
    index_avl *dado;
    int fb;
    struct no_avl *esq, *dir;
} no_avl;

typedef no_avl * arvore_avl;

enum cor { VERMELHO, PRETO, DUPLO_PRETO };

typedef struct indice_rb {
	char chave[127];
	int indice;
} index_rb;

typedef struct no_rb{
    index_rb *dado;
    enum cor cor;
    struct no_rb *esq, *dir, *pai;
} no_rb;

typedef no_rb * arvore_rb;

typedef struct no_fila{
        int indice;
        struct no* proximo;
} no_fila;

typedef no_fila * fila;

typedef struct tabela {
	FILE *arquivo_dados;
	arvore_bst indices_cpf;
	arvore_avl indices_matricula;
	arvore_rb indices_email;
	fila indices_alocacao;
} tabela;

int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarEstudante(tabela *tab, dado *estudante);

void removerEstudantePeloCpf(tabela *tab, char *valor, arvore_bst raiz);
void removerEstudantePelaMatricula(tabela *tab, int valor, arvore_avl raiz);
void removerEstudantePeloEmail(tabela *tab, char *valor, arvore_rb raiz);

void buscarEstudantePeloCpf(tabela *tab, char *valor, arvore_bst raiz);
void buscarEstudantePelaMatricula(tabela *tab, int valor, arvore_avl raiz);
void buscarEstudantePeloEmail(tabela *tab, char *valor, arvore_rb raiz);

void ordenarEstudantesPeloCpf(arvore_bst raiz, tabela *tab);
void ordenarEstudantesPelaMatricula(arvore_avl raiz, tabela *tab);
void ordenarEstudantesPeloEmail(arvore_rb raiz, tabela *tab);

//BST
void inicializar_bst(arvore_bst raiz);
arvore_bst adicionar_bst(index_bst *valor, arvore_bst raiz);
arvore_bst remover_bst(char *valor, arvore_bst raiz);
int altura_bst(arvore_bst raiz);
void imprimir_elemento_bst(arvore_bst raiz, tabela * tab);
index_bst * maior_elemento_bst(arvore_bst raiz);
index_bst * menor_elemento_bst(arvore_bst raiz);
void pre_order_bst(arvore_bst raiz, tabela *tab);
void pos_order_bst(arvore_bst raiz, tabela *tab);
void in_order_bst(arvore_bst raiz, tabela *tab);
arvore_bst buscar_bst(arvore_bst raiz, char *valor);

void salvar_arquivo_bst(char *nome, arvore_bst a);
void salvar_auxiliar_bst(arvore_bst raiz, FILE *arq);
arvore_bst carregar_arquivo_bst(char *nome, arvore_bst a);

//AVL
void inicializar_avl(arvore_avl raiz);
arvore_avl adicionar_avl(arvore_avl raiz, index_avl *valor, int *cresceu);
arvore_avl rotacao_avl(arvore_avl pivo);
arvore_avl rotacao_simples_esquerda_avl(arvore_avl pivo);
arvore_avl rotacao_simples_direita_avl(arvore_avl pivo);
arvore_avl rotacao_dupla_esquerda_avl(arvore_avl pivo);
arvore_avl rotacao_dupla_direita_avl(arvore_avl pivo);
arvore_avl remover_avl(arvore_avl raiz, int valor, int *caiu);
int altura_avl(arvore_avl raiz);
void imprimir_elemento_avl(arvore_avl raiz, tabela * tab);
index_avl * maior_elemento_avl(arvore_avl raiz);
index_avl * menor_elemento_avl(arvore_avl raiz);
void pre_order_avl(arvore_avl raiz, tabela *tab);
void pos_order_avl(arvore_avl raiz, tabela *tab);
void in_order_avl(arvore_avl raiz, tabela *tab);
arvore_avl buscar_avl(arvore_avl raiz, int valor);

void salvar_arquivo_avl(char *nome, arvore_avl a);
void salvar_auxiliar_avl(arvore_avl raiz, FILE *arq);
arvore_avl carregar_arquivo_avl(char *nome, arvore_avl a);

//RB
void inicializar_rb(arvore_rb *raiz);
void adicionar_rb(index_rb *valor, arvore_rb *raiz);
void ajustar_rb(arvore_rb *raiz, arvore_rb elemento);
void rotacao_simples_esquerda_rb(arvore_rb *raiz, arvore_rb pivo);
void rotacao_simples_direita_rb(arvore_rb *raiz, arvore_rb pivo);
enum cor cor(arvore_rb elemento);
int eh_raiz(arvore_rb elemento);
int eh_filho_esquerdo(arvore_rb elemento);
int eh_filho_direito(arvore_rb elemento);
arvore_rb irmao(arvore_rb elemento);
arvore_rb tio(arvore_rb elemento);
arvore_rb avo(arvore_rb elemento);
index_rb * maior_elemento_rb(arvore_rb raiz);
index_rb * menor_elemento_rb(arvore_rb raiz);
int altura_rb(arvore_rb raiz);
void retira_duplo_preto(arvore_rb *raiz, arvore_rb elemento);
void remover_rb(char *valor, arvore_rb *raiz);
void reajustar_rb(arvore_rb *raiz, arvore_rb elemento);
void imprimir_elemento_rb(arvore_rb raiz, tabela * tab);
void pre_order_rb(arvore_rb raiz, tabela *tab);
void pos_order_rb(arvore_rb raiz, tabela *tab);
void in_order_rb(arvore_rb raiz, tabela *tab);
arvore_rb buscar_rb(arvore_rb raiz, char *valor);

void salvar_arquivo_rb(char *nome, arvore_rb a);
void salvar_auxiliar_rb(arvore_rb raiz, FILE *arq);
arvore_rb carregar_arquivo_rb(char *nome, arvore_rb a);

//FILA
void inicializar_fila(fila f);
void exibir_fila(fila f);
fila enqueue(fila f, int valor);
fila dequeue(fila f);

void salvar_arquivo_fila(char *nome, fila f);
void salvar_auxiliar_fila(fila f, FILE *arq);
fila carregar_arquivo_fila(char *nome, fila f);

int maior(int a, int b);
dado * ler_dados();
void tirar_enter(char *string);

#endif
