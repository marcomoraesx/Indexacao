#include <stdio.h>
#include <stdlib.h>
#include "indexing.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao;
	inicializarTabela(&tab);

	while(1) {
        printf("\n================ Controle de registros para Discentes de Biblioteca =================\n");
        printf("[1] Adicionar registro\n");
        printf("[2] Buscar registro por CPF\n");
        printf("[3] Buscar registro por matrícula\n");
        printf("[4] Buscar registro por email\n");
        printf("[5] Ordenar registros por CPF\n");
        printf("[6] Ordenar registros por matrícula\n");
        printf("[7] Ordenar registros por email\n");
        printf("[8] Remover registro pelo CPF\n");
        printf("[9] Remover registro pela matrícula\n");
        printf("[10] Remover registro pelo email\n");
        printf("[99] Sair e Salvar\n");
        printf("========================================================================\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

		switch(opcao) {
                char cpf[20];
				int matricula;
				char email[127];

				case 1:
                        printf("Você escolheu adicionar registro.\n");
						adicionarEstudante(&tab, ler_dados());
						break;
				case 2:
                        printf("Você escolheu buscar registro por CPF.\n");
                        printf("Informe o CPF ao qual será consultado: ");
                        __fpurge(stdin);
                        fgets(cpf, 20,  stdin);
                        tirar_enter(cpf);
                        buscarEstudantePeloCpf(&tab, &cpf, tab.indices_cpf);
						break;
				case 3:
                        printf("Informe a MATRICULA a qual será consultada: ");
                        scanf("%d", &matricula);
						buscarEstudantePelaMatricula(&tab, matricula, tab.indices_matricula);
						break;
				case 4:
                        printf("Informe o EMAIL ao qual será consultado: ");
                        __fpurge(stdin);
                        fgets(email, 127,  stdin);
                        tirar_enter(email);
						buscarEstudantePeloEmail(&tab, &email, tab.indices_email);
						break;
				case 5:
						ordenarEstudantesPeloCpf(tab.indices_cpf, &tab);
						printf("\n");
						break;
				case 6:
						ordenarEstudantesPelaMatricula(tab.indices_matricula, &tab);
						printf("\n");
						break;
				case 7:
						ordenarEstudantesPeloEmail(tab.indices_email, &tab);
						printf("\n");
						break;
                case 8:
                        printf("Informe o CPF do registro que deve ser removido: ");
                        __fpurge(stdin);
                        fgets(cpf, 20,  stdin);
                        tirar_enter(cpf);
                        removerEstudantePeloCpf(&tab, &cpf, tab.indices_cpf);
                        break;
                case 9:
                        printf("Informe a MATRICULA do registro que deve ser removido: ");
                        scanf("%d", &matricula);
                        removerEstudantePelaMatricula(&tab, matricula, tab.indices_matricula);
                        break;
                case 10:
                        printf("Informe o EMAIL do registro que deve ser removido: ");
                        __fpurge(stdin);
                        fgets(email, 127,  stdin);
                        tirar_enter(email);
                        removerEstudantePeloEmail(&tab, &email, tab.indices_email);
                        break;
				case 99:
						finalizar(&tab);
						exit(0);
                default:
                        printf("\nOpção inválida. Tente novamente.\n\n");
		}
	}
}
