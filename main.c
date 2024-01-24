#include <stdio.h>
#include <stdlib.h>
#include "indexing.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao;
	inicializarTabela(&tab);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
                char cpf[20];
				int matricula;
				char email[127];

				case 1:
						adicionarEstudante(&tab, ler_dados());
						break;
				case 2:
                        printf("Informe o CPF ao qual será consultado: ");
                        fgets(cpf, 20,  stdin);
                        tirar_enter(cpf);
                        buscarEstudantePeloCpf(&tab, &cpf);
						break;
				case 3:
                        printf("Informe a MATRICULA a qual será consultada: ");
                        scanf("%d", &matricula);
						buscarEstudantePelaMatricula(&tab, matricula);
						break;
				case 4:
                        printf("Informe o EMAIL ao qual será consultado: ");
                        fgets(email, 127,  stdin);
                        tirar_enter(email);
						buscarEstudantePeloEmail(&tab, &email);
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
				case 99:
						finalizar(&tab);
						exit(0);
		}
	}
}
