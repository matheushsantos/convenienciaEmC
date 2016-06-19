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
int abrirDia();
bool getCaixa();


int vendasFeitas, caixaAbertoTemp;
float valorTotalVendas, totalVendido;
struct Caixa * caixa;

int diaAtual = -1;

void FuncaoCaixa()
{
	int funcCaixa = 1,opcaoCaixa;
	char teste[100];
	while (funcCaixa == 1)
	{
		system("cls");
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
		leituraSwitch(teste);

		switch (teste[0])
		{
		case ('1') :
		{
			//printf("chegou aqui");
			//system("pause");
			abrirDia();
			break;
		}
		case ('2') :
		{
			//printf("chegou aqui");
			//system("pause");
			verificarCaixa();
			break;
		}
		case ('3') :
		{
			//printf("chegou aqui");
			//system("pause");
			fechaCaixa();
			break;
		}
		case ('0') :
		{
			//error("Encerando Menu do Caixa");
			funcCaixa = 0;
			break;
		}
		default:
		{
			fflush(stdin);
			error("Valor inv�lido");
			break;
		}
		}
	}
}
int abrirDia(){


	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("############################ Abrir Caixa do dia atual #########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	//ssystem("pause");
	/*Primeira passagem*/

		if (confirmacao("\nConfirma Abertura de Caixa? (Y/N)\n\nQualquer tecla Para cancelamento. . .", 'Y', comMensagemDeErro))
		{
			if (diaAtual == -1) diaAtual++;

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
			error("Caixa n�o foi aberto, retornando ao menu");
		}
		return 0;
}

void verificarCaixa(){

	if (getCaixa())
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("######################### Consulta Caixa Di�rio ###############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");

		printf("\nId do caixa: %d", caixa[diaAtual].diaAtual);
		printf("\nO valor total de vendas foi de:  R$%.2f ", caixa[diaAtual].totalVendaDia);
		printf("\nO numero de vendas at� o momento foi de: %d ", caixa[diaAtual].numVendaDia);
		printf("\nO valor total de gastos com produtos foi de: R$%.2f", caixa[diaAtual].entradaDiaria /**-1*/); //Descomentar caso queira exibir positivo
		printf("\nO lucro diario est� ");
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
		printf("\nTotal di�rio: R$%.2f\n", caixa[diaAtual].entradaDiaria + caixa[diaAtual].totalVendaDia);
		if (confirmacao("Deseja ir para o Fechamento de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			fechaCaixa();
		}

	}
	else
	{
		if (confirmacao("Caixa encontra-se fechado, deseja ir para Abertura de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			abrirDia();
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
	printf("######################### Fechamento de Caixa Di�rio ##########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");

	if (diaAtual >=0 && caixa[diaAtual].aberto)
	{
		//printf("\nDia: %d", diaAtual);
		printf("\nId do caixa: %d", caixa[diaAtual].diaAtual);
		printf("\nO valor total de vendas foi de:  %.2f ", caixa[diaAtual].totalVendaDia);
		printf("\nO numero de vendas at� o momento foi de: %d ", caixa[diaAtual].numVendaDia);
		printf("\nO valor total de gastos com produtos foi de: %.2f", caixa[diaAtual].entradaDiaria);
		printf("\nO lucro diario est� ");
		if (lucroProd > 0)
			printf("Habilitado em: %.2f%%\n", lucroProd * 100);
		else
		{
			printf("desabilitado");

		}
		printf("\nTotal di�rio: %.2f\n", caixa[diaAtual].entradaDiaria + caixa[diaAtual].totalVendaDia);
		
		if (confirmacao("Confirma Fechamento Di�rio? (Y/N)", 'Y', comMensagemDeErro))
		{
			caixa[diaAtual].aberto = false;
			diaAtual++;
			caixa[diaAtual].aberto = false;
			error("Caixa Fechado");
		}
		else
		{
			error("Cancelamento n�o confirmado");
		}
	}
	else
	{
		if (confirmacao("N�o existe um caixa aberto, deseja ir para Abertura de Caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			abrirDia();
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