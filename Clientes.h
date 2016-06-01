#ifndef _CLIENTES_H_
#define _CLIENTES_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>

//Lib Criada para auxilio na chamadas das funções
#include "Funcoes.h"
//#include "Produtos.h"
//#include "Venda.h"


struct Clientes
{
	char NomeCliente[100];
	char emailCliente[50];
	char CPFCliente[20];
	char TelefoneCliente[20];
	unsigned int IDCliente;
	float TotalGasto;              //total acumulado de gastos pelo cliente
	unsigned int TotalVendas;      // quantidade de compras
};


int  ClientesCadastrados = 0;
void MenuCadastroCliente();     
void MenuAcharCliente();        
void MenuHistoricoCliente();
bool existeCpfCnpj(char * cpf, int * id); // id 0 para exibição de mensagem de invalidez
bool existeMail(char * email, int * id); // id 0 para exibição de mensagem de invalidez

struct Clientes * Cli;



void MenuCadastroCliente() {


	//fflush(stdin);
	int continua = 1;
	while (continua == 1)
	{
		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("###################### Cadastrar Cliente Fidelidade ###########################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		printf("\nPressione 'x' + Enter para cancelar\n\n");
		printf("\n**Id Cliente: %d **\n", ClientesCadastrados+1);


		//############################## ALOCANDO MEMÓRIA##############################################
		if (ClientesCadastrados == 0)
		{
			Cli = (struct Clientes *)malloc(sizeof(struct Clientes));

		}
		else if (ClientesCadastrados >= 1)
		{
			Cli = (struct Clientes *)realloc(Cli, (ClientesCadastrados + 1)*sizeof(struct Clientes));
		}
		//############################################################################################

		
		//printf("Insira os dados do cliente!\n\n");
		printf("Insira o nome do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].NomeCliente, 100, stdin);
		if (Cli[ClientesCadastrados].NomeCliente[0] == 'x')  break;
		printf("\nInsira o email do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].emailCliente, 50, stdin);
		if (Cli[ClientesCadastrados].emailCliente[0] == 'x')  break;
		printf("\n**Somente Numeros**\nInsira o telefone do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].TelefoneCliente, 20, stdin);
		if (Cli[ClientesCadastrados].TelefoneCliente[0] == 'x')  break;
		printf("\n**Somente Numeros**\nInsira o CPF/CNPJ do Cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].CPFCliente,20, stdin);
		if (Cli[ClientesCadastrados].CPFCliente[0] == 'x')  break;
		if (validaNomeClie(Cli[ClientesCadastrados].NomeCliente) && validaEmail(Cli[ClientesCadastrados].emailCliente) && validaTel(Cli[ClientesCadastrados].TelefoneCliente) && validaCpfCnpj(Cli[ClientesCadastrados].CPFCliente) )
		{
			if (existeMail(Cli[ClientesCadastrados].emailCliente, 0) && existeCpfCnpj(Cli[ClientesCadastrados].CPFCliente, 0))
			{
				
				Cli[ClientesCadastrados].IDCliente = ClientesCadastrados + 1;
				printf("\nCliente Cadastrado, ID do Cliente:  %d\n", Cli[ClientesCadastrados].IDCliente);
				ClientesCadastrados++ ;
			}
			else
			{
				printf("\n***Cadastro Invalidado***\n");
				system("pause");
			}
		}
		else
		{
			printf("\n***Cadastro Invalidado***\n");
			system("pause");
		}
		printf("\nDeseja cadastrar/recadastrar um novo cliente?");
		printf("\n 1 - sim  /  0 - nao:  ");
		scanf_s("%d", &continua);

		switch (continua)
		{
		case (0) :
		{
			//printf("\nretornando ao menu principal\n");
			//system("pause");
			break;
		}
		case (1) :
		{
			//printf("\n Novo Cadastro\n");
			//system("pause");
			break;
		}
		default:
		{
			printf("**\nInsira um caracter valido**\n");
			//system("pause");
			break;
		}
		}
	}
}



bool existeCpfCnpj(char * cpf, int * id){

	int  i;

	for (i = 0; i < ClientesCadastrados; i++)
	{
		if (strcmp(cpf, Cli[i].CPFCliente) == 0)
		{
			if (id == 0)
			{
				printf("\n***O CPF/CNPJ informado já esta cadastrado para o Cliente: %s***\n", Cli[i].NomeCliente);
			}

			*id = i; // passando o ID do cliente cujo dado foi encontrado

			//printf("id p: %d  id v: %d i: %d\n",&id , id, i);
			//system("pause");
			return false;
		}
	}

	return true;
}

bool existeMail(char * email, int * id){

	int  i;

	for (i = 0; i < ClientesCadastrados; i++)
	{
		if (strcmp(email, Cli[i].emailCliente) == 0)
		{
			
			if (id == 0)
			{
				printf("\n***O EMAIL informado já esta cadastrado para o Cliente: %s***\n", Cli[i].NomeCliente);
			}
			 * id =  i ;
			 // passando o ID do cliente cujo dado foi encontrado

			return false;
		}
	}

	return true;
}

#endif