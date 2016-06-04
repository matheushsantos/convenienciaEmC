#ifndef _CAIXA_H
#define _CAIXA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#include "Funcoes.h"

struct Caixa
{
	bool aberto;
	float totalVendaDia;
	unsigned int diaAtual;
	int numVendaDia;
	float entradaDiaria;
};

void zerarCaixa();
void totalUsado();
void verificarCaixa();
void fechaCaixa();
void FuncaoCaixa();
int abriDia();
bool getCaixa();


int vendasFeitas, caixaAbertoTemp;
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


	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("############################ Abrir Caixa do dia atual #########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	//ssystem("pause");
	/*Primeira passagem*/
	if (diaAtual == -1) diaAtual++;

		if (confirmacao("\n1 - Abertura de Caixa\n\nQualquer tecla Para cancelamento. . .", '1', comMensagemDeErro))
		{
			
			if (diaAtual == 0)
			{	
				if (caixaAbertoTemp == 0)
				{
					caixa = (struct Caixa *)malloc(sizeof(struct Caixa));
					caixa[diaAtual].diaAtual = 1;
					caixa[diaAtual].aberto = true;
					caixa[diaAtual].numVendaDia = 0;
					caixa[diaAtual].totalVendaDia = 0;
					caixa[diaAtual].entradaDiaria = 0;
					printf("\n***Caixa Aberto 0***\n      Id: %d\n", caixa[diaAtual].diaAtual);
					system("pause");
					if (caixaAbertoTemp == 0) caixaAbertoTemp++;
					return 1;
				}
				else if (caixa[diaAtual].aberto)
				{
					if (confirmacao("Caixa atual encontra-se aberto, deseja fechar? (Y/N)", 'Y', comMensagemDeErro))
					{
						fechaCaixa();
					}
					else
					{
						error("Retornando ao menu");
					}
				}
				

			}
			else if (diaAtual >= 1)
			{
				if (!caixa[diaAtual].aberto)
				{
					caixa = (struct Caixa *)realloc(caixa, (diaAtual + 1)*sizeof(struct Caixa));
					caixa[diaAtual].diaAtual = diaAtual + 1;
					caixa[diaAtual].aberto = true;
					caixa[diaAtual].numVendaDia = 0;
					caixa[diaAtual].totalVendaDia = 0;
					caixa[diaAtual].entradaDiaria = 0;
					printf("\n***Caixa Aberto***\n      Id: %d\n", caixa[diaAtual].diaAtual);
					system("pause");
					return 1;
				}
				else
				{
					if (confirmacao("Caixa anterior encontra-se aberto, deseja fechar? (Y/N)", 'Y', comMensagemDeErro))
					{
						fechaCaixa();
					}
					else
					{
						error("Retorno ao Menu");
					}
				}
			}

		}
		else
		{
			error("Caixa não foi aberto, retornando ao menu");
		}
		return 0;
}

void verificarCaixa(){

	if (getCaixa())
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("######################### Consulta Caixa Diário ###############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");

		printf("\nId do caixa: %d", caixa[diaAtual].diaAtual);
		printf("\nO valor total de vendas foi de:  %.2f ", caixa[diaAtual].totalVendaDia);
		printf("\nO numero de vendas até o momento foi de: %d ", caixa[diaAtual].numVendaDia);
		printf("\nO valor total de gastos com produtos foi de: %.2f", caixa[diaAtual].entradaDiaria);
		printf("\nO lucro diario está ");
		if (lucroProd > 0)
			printf("Habilitado em: %.2f%%\n", lucroProd*100);
		else
		{
			printf("desabilitado");
			if (confirmacao("\nDeseja ir para tela de Lucro? (Y/N)" , 'Y', comMensagemDeErro))
			{
				if (menuAlterarTaxa())
				{
					error("Taxa cadastrada com sucesso");
				}
			}
		}
		printf("\nTotal diário: %.2f\n", caixa[diaAtual].entradaDiaria + caixa[diaAtual].totalVendaDia);
		if (confirmacao("Deseja ir para o Fechamento de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			fechaCaixa();
		}

	}
	else
	{
		if (confirmacao("Caixa encontra-se fechado, deseja ir para Abertura de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			abriDia();
		}
		else
		{
			error("Retornando ao menu");
		}
	}
}
		


void fechaCaixa(){
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("######################### Fechamento de Caixa Diário ##########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	if (diaAtual >=0 && caixa[diaAtual].aberto)
	{
		//printf("\nDia: %d", diaAtual);
		printf("\nId do caixa: %d", caixa[diaAtual].diaAtual);
		printf("\nO valor total de vendas foi de:  %.2f ", caixa[diaAtual].totalVendaDia);
		printf("\nO numero de vendas até o momento foi de: %d ", caixa[diaAtual].numVendaDia);
		printf("\nO valor total de gastos com produtos foi de: %.2f", caixa[diaAtual].entradaDiaria);
		printf("\nO lucro diario está ");
		if (lucroProd > 0)
			printf("Habilitado em: %.2f%%\n", lucroProd * 100);
		else
		{
			printf("desabilitado");

		}
		printf("\nTotal diário: %.2f\n", caixa[diaAtual].entradaDiaria + caixa[diaAtual].totalVendaDia);
		
		if (confirmacao("Confirma Fechamento Diário? (Y/N)", 'Y', comMensagemDeErro))
		{
			caixa[diaAtual].aberto = false;
			diaAtual++;
			caixa[diaAtual].aberto = false;
			error("Caixa Fechado");
		}
		else
		{
			error("Cancelamento não confirmado");
		}
	}
	else
	{
		if (confirmacao("Não existe um caixa aberto, deseja ir para Abertura de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			abriDia();
		}
		else
		{
			error("Retornando ao Menu");
		}
	}
}

bool getCaixa(){

	if (diaAtual < 0) return false;
	else if (!caixa[diaAtual].aberto) return false;
	return true;
}
#endif