#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "indexing.h"
#include <string.h>

int inicializarTabela(tabela *tab) {
	inicializar_bst(tab->indices_cpf);
	inicializar_avl(tab->indices_matricula);
	inicializar_rb(&tab->indices_email);
	tab->arquivo_dados = fopen("dados.ext", "a+b");
	tab->indices_cpf = carregar_arquivo_bst("indices_cpf.ext", tab->indices_cpf);
	tab->indices_matricula = carregar_arquivo_avl("indices_matricula.ext", tab->indices_matricula);
	tab->indices_email = carregar_arquivo_rb("indices_email.ext", tab->indices_email);
	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}

void finalizar(tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo_bst("indices_cpf.ext", tab->indices_cpf);
	salvar_arquivo_avl("indices_matricula.ext", tab->indices_matricula);
	salvar_arquivo_rb("indices_email.ext", tab->indices_email);
}

void adicionarEstudante(tabela *tab, dado *estudante){
	if(tab->arquivo_dados != NULL) {
			index_bst * novo_bst = (index_bst *) malloc(sizeof(index_bst));
			index_avl * novo_avl = (index_avl *) malloc(sizeof(index_avl));
			index_rb * novo_rb = (index_rb *) malloc(sizeof(index_rb));

			fseek(tab->arquivo_dados, 0L, SEEK_END);

			//Adicionar indice para CPF
			novo_bst->indice = ftell(tab->arquivo_dados);
			//Adicionar indice para MATRICULA
			novo_avl->indice = ftell(tab->arquivo_dados);
			//Adicionar indice para EMAIL
			novo_rb->indice = ftell(tab->arquivo_dados);

			fwrite(estudante, sizeof(dado), 1, tab->arquivo_dados);

			//Adicionar chave para CPF
			strcpy(novo_bst->chave, estudante->cpf);
			tab->indices_cpf = adicionar_bst(novo_bst, tab->indices_cpf);
			//Adicionar chave para MATRICULA
            novo_avl->chave = estudante->matricula;
            int cresceu = 0;
			tab->indices_matricula = adicionar_avl(tab->indices_matricula, novo_avl, &cresceu);
			//Adicionar chave para EMAIL
			strcpy(novo_rb->chave, estudante->email);
			adicionar_rb(novo_rb, &tab->indices_email);
	}
}

void removerEstudantePeloCpf(tabela *tab, char *valor, arvore_bst raiz_bst, arvore_avl raiz_avl, arvore_rb raiz_rb) {
    if (tab->arquivo_dados != NULL) {
        arvore_bst registro = buscar_bst(raiz_bst, valor);
        if (registro) {
            int caiu = 0;
            dado * temp = (dado *) malloc (sizeof(dado));
            fseek(tab->arquivo_dados, registro->dado->indice, SEEK_SET);
            fread(temp, sizeof(dado), 1, tab->arquivo_dados);
            raiz_bst = remover_bst(valor, raiz_bst);
            raiz_avl = remover_avl(raiz_avl, temp->matricula, &caiu);
            remover_rb(&temp->email, &raiz_rb);
            free(temp);
        } else {
            printf("Registro não encontrado!\n");
        }
    }
}

void removerEstudantePelaMatricula(tabela *tab, int valor, arvore_avl raiz_avl, arvore_bst raiz_bst, arvore_rb raiz_rb) {
    if (tab->arquivo_dados != NULL) {
        arvore_avl registro = buscar_avl(raiz_avl, valor);
        if (registro) {
            int caiu = 0;
            dado * temp = (dado *) malloc (sizeof(dado));
            fseek(tab->arquivo_dados, registro->dado->indice, SEEK_SET);
            fread(temp, sizeof(dado), 1, tab->arquivo_dados);
            raiz_bst = remover_bst(&temp->cpf, raiz_bst);
            raiz_avl = remover_avl(raiz_avl, valor, &caiu);
            remover_rb(&temp->email, &raiz_rb);
            free(temp);
        } else {
            printf("Registro não encontrado!\n");
        }
    }
}

void removerEstudantePeloEmail(tabela *tab, char *valor, arvore_rb raiz_rb, arvore_avl raiz_avl, arvore_bst raiz_bst) {
    if (tab->arquivo_dados != NULL) {
        arvore_rb registro = buscar_rb(raiz_rb, valor);
        if (registro) {
            int caiu = 0;
            dado * temp = (dado *) malloc (sizeof(dado));
            fseek(tab->arquivo_dados, registro->dado->indice, SEEK_SET);
            fread(temp, sizeof(dado), 1, tab->arquivo_dados);
            raiz_bst = remover_bst(&temp->cpf, raiz_bst);
            raiz_avl = remover_avl(raiz_avl, temp->matricula, &caiu);
            remover_rb(valor, &raiz_rb);
            free(temp);
        } else {
            printf("Registro não encontrado!\n");
        }
    }
}

void buscarEstudantePeloCpf(tabela *tab, char *valor, arvore_bst raiz) {
    arvore_bst registro = buscar_bst(raiz, valor);
    if (registro) {
        imprimir_elemento_bst(registro, tab);
    } else {
        printf("Registro não encontrado!\n");
    }
}

void buscarEstudantePelaMatricula(tabela *tab, int valor, arvore_avl raiz) {
    arvore_avl registro = buscar_avl(raiz, valor);
    if (registro) {
        imprimir_elemento_avl(registro, tab);
    } else {
        printf("Registro não encontrado!\n");
    }
}

void buscarEstudantePeloEmail(tabela *tab, char *valor, arvore_rb raiz) {
    arvore_rb registro = buscar_rb(raiz, valor);
    if (registro) {
        imprimir_elemento_rb(registro, tab);
    } else {
        printf("Registro não encontrado!\n");
    }
}

void ordenarEstudantesPeloCpf(arvore_bst raiz, tabela *tab) {
    if (raiz != NULL) {
        in_order_bst(raiz, tab);
    }
}

void ordenarEstudantesPelaMatricula(arvore_avl raiz, tabela *tab) {
    if (raiz != NULL) {
        in_order_avl(raiz, tab);
    }
}

void ordenarEstudantesPeloEmail(arvore_rb raiz, tabela *tab) {
    if (raiz != NULL) {
        in_order_rb(raiz, tab);
    }
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
	/*strcpy(novo->nome, "Marco Antônio");
	strcpy(novo->cpf, "4397294354");
	novo->debito = 0;
	strcpy(novo->email, "marcomoraes@teste");
	strcpy(novo->telefone, "45634534");
	strcpy(novo->curso, "bcc");
	novo->matricula = 234234;*/

	//__fpurge(stdin);
	getchar();
	printf("Nome: ");
	fgets(novo->nome, 255,  stdin);
	tirar_enter(novo->nome);
	printf("CPF: ");
	fgets(novo->cpf, 20,  stdin);
	tirar_enter(novo->cpf);
	printf("Matricula: ");
	scanf("%d", &novo->matricula);
	__fpurge(stdin);
	printf("Telefone: ");
	fgets(novo->telefone, 20,  stdin);
	tirar_enter(novo->telefone);
	printf("Email: ");
	fgets(novo->email, 127,  stdin);
	tirar_enter(novo->email);
	printf("Curso: ");
	fgets(novo->curso, 50,  stdin);
	tirar_enter(novo->curso);
	printf("Débito: ");
	scanf("%d", &novo->debito);
	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}
