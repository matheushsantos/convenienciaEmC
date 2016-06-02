#ifndef _CAIXA_H
#define _CAIXA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

struct Caixa
{
	float totalVendaDia;
	unsigned int diaAtual;
	bool aberto;
	int numVendaDia;
};

void zerarCaixa();
void totalUsado();
void verificarCaixa();
void fechaCaixa();
void FuncaoCaixa();
int abriDia();


int vendasFeitas;
float valorTotalVendas, totalVendido;
struct Caixa * caixa;

int diaAtual = -1;

void FuncaoCaixa()
{
	int funcCaixa = 1, opcaoCaixa;
	while (funcCaixa == 1)
	{
		system("cls");
		fflush(stdin);
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################# Menu de Caixa ###################################\n");
		printf("#                                                                             #\n");
		printf("#         1 - Para abrir o dia atual                                          #\n");
		printf("#         2 - Para consulta o caixa                                           #\n");
		printf("#         3 - Para fechar o caixa total                                       #\n");
		printf("#         0 - Para retornar ao menu principal                                 #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");

		scanf_s("%d", &opcaoCaixa);
		switch (opcaoCaixa)
		{
		case (1) :
		{
			//printf("chegou aqui");
			//system("pause");
			abriDia();
			break;
		}
		case (2) :
		{
			//printf("chegou aqui");
			//system("pause");
			verificarCaixa();
			break;
		}
		case (3) :
		{
			//printf("chegou aqui");
			//system("pause");
			fechaCaixa();
			break;
		}
		case (0) :
		{
			printf("**retornando ao menu principal**\n");
			funcCaixa = 0;
			getchar();
			break;
		}
		default:
		{
			printf("**insira um valor valido!**\n");
			getchar();
			break;
		}
		}
	}
}
int abriDia(){
	int opcao;
	fflush(stdin);
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("############################ Abrir Caixa do dia atual #########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	//ssystem("pause");

	printf("deseja realmente abrir o dia?, se sim, digite 1:   ");
	scanf_s("%d", &opcao);
	if (opcao == 1)
	{
		diaAtual++;
		if (diaAtual == 0)
		{
			caixa = (struct Caixa *)malloc(sizeof(struct Caixa));
			caixa[diaAtual].diaAtual = diaAtual;
			caixa[diaAtual].aberto = true;
			caixa[diaAtual].numVendaDia = 0;
			caixa[diaAtual].totalVendaDia = 0;
			printf("\n***Caixa Aberto***\n");
			system("pause");
			return 1;

		}
		else if (diaAtual >= 1)
		{
			if (!caixa[diaAtual - 1].aberto)
			{
				caixa = (struct Caixa *)realloc(caixa, (diaAtual + 1)*sizeof(struct Caixa));
				caixa[diaAtual].diaAtual = diaAtual;
				caixa[diaAtual].aberto = true;
				caixa[diaAtual].numVendaDia = 0;
				caixa[diaAtual].totalVendaDia = 0;
				printf("\n***Caixa Aberto***\n");
				system("pause");
				return 1;
			}
			else
			{
				char yn;
				printf("\Caixa Anterior Aberto, Deseje fechar? (Y/N)\n");
				getchar();
				scanf_s("%c", &yn);

				yn = toupper(yn);
				if (yn == 'Y')
				{
					fechaCaixa();
				}
			}
		}

	}
	else
	{
		printf("\n***Valor Invalido***\n");
		system("pause");
	}
	return 0;

}
void verificarCaixa()
{
	int opcao = 0;
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("######################### verificar o dia atual ###############################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	printf("\nExibindo total de vendas e total recebido");
	printf("\nO total arrecadado ate este momento foi de:  %f ", caixa[diaAtual].totalVendaDia);
	printf("\nO tota de vendas feitas ate este momento foi de: %d ", caixa[diaAtual].numVendaDia);

	printf("\nse quiser ir para o menu de encerramento do caixa, digite 1:  ");
	scanf_s("%d", &opcao);

	if (opcao == 1)
	{
		fechaCaixa();
	}
	else
	{
		printf("\n***Valor Invalido***\n");
		system("pause");
	}
}

void fechaCaixa()
{
	char yn;
	printf("\Confirma Fechamento do Caixa (Y/N)\n");
	getchar();
	scanf_s("%c", &yn);
	yn = toupper(yn);
	if (yn == 'Y')
	{
		printf("\nId do Dia: %d ", diaAtual);
		printf("\nSua venda deste dia vai ser de:  %.2f", caixa[diaAtual].totalVendaDia);
		printf("\nTotal de vendas feitas neste dia foi de: %d  \n", caixa[diaAtual].numVendaDia);
		printf("\n***Caixa fechado***\n");
		system("pause");
		caixa[diaAtual].aberto = false;
	}
	else
	{
		printf("\n***Cancelado fechamento***\n");
		system("pause");
	}

}


#endif