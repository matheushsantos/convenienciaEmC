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

/*Valores Definidos por default que poderão ser alterados*/
float percUm = 10, percDois = 20, percTres = 30, percQuat = 50;
float descUm = 2000, descDois = 5000, descTres = 10000, descQuat = 100000;

int  ClientesCadastrados = 0;
void funcaoClientes();
int setupCliente();
void MenuCadastroCliente();     
void MenuHistoricoCliente();
bool existeCpfCnpj(char * cpf, int * id); // id 0 para exibição de mensagem de invalidez
bool existeMail(char * email, int * id); // id 0 para exibição de mensagem de invalidez

struct Clientes * Cli;

void funcaoClientes(){
	
	int menuCli = 1;
	char leitura[100];

	while (menuCli != 0)
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################# Menu de Cliente #################################\n");
		printf("#                                                                             #\n");
		printf("#         1 - Cadastro de Clientes Fidelidade                                 #\n");
		printf("#         2 - Consultar Saldo Clientes Fidelidade                             #\n");
		printf("#         3 - Listagem de Clientes                                            #\n");
		printf("#         4 - Setup                                                           #\n");
		printf("#         0 - Sair                                                            #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		leituraSwitch(leitura);

		switch (leitura[0])
		{
		case('1') :
		{
			MenuCadastroCliente();
			break;
		}
		case('2') :
		{
			break;
		}
		case('3') :
		{
			break;
		}
		case('4') :
		{
			setupCliente();
			break;
		}
		case('0') :
		{
			menuCli = 0;
			break;
		}
		default:
			fflush(stdin);
			system("cls");
			error("**Valor Inválido**");
			break;
		}
	}
}

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

		
		/*Informações dos clientes para cadastro*/

		/*Nome*/
		printf("Insira o nome do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].NomeCliente, 100, stdin);
		if (Cli[ClientesCadastrados].NomeCliente[0] == 'x')  break;
		if (!validaNomeClie(Cli[ClientesCadastrados].NomeCliente, comMensagemDeErro)) break;

		/*E-mail*/
		printf("\nInsira o email do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].emailCliente, 50, stdin);
		if (Cli[ClientesCadastrados].emailCliente[0] == 'x')  break;
		if (!validaEmail(Cli[ClientesCadastrados].emailCliente, comMensagemDeErro)) break;;

		/*Telefone do Cliente*/
		printf("\n**Somente Numeros**\nInsira o telefone do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].TelefoneCliente, 20, stdin);
		if (Cli[ClientesCadastrados].TelefoneCliente[0] == 'x')  break;
		if (!validaTel(Cli[ClientesCadastrados].TelefoneCliente, comMensagemDeErro)) break;

		printf("\n**Somente Numeros**\nInsira o CPF/CNPJ do Cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].CPFCliente,20, stdin);
		if (Cli[ClientesCadastrados].CPFCliente[0] == 'x')  break;
		if (!validaCpfCnpj(Cli[ClientesCadastrados].CPFCliente, comMensagemDeErro)) break;
		
			if (existeMail(Cli[ClientesCadastrados].emailCliente, 0) && existeCpfCnpj(Cli[ClientesCadastrados].CPFCliente, 0))
			{
				
				Cli[ClientesCadastrados].IDCliente = ClientesCadastrados + 1;
				Cli[ClientesCadastrados].TotalGasto = 0;
				Cli[ClientesCadastrados].TotalVendas = 0;
				printf("\nCliente Cadastrado, ID do Cliente:  %d\n", Cli[ClientesCadastrados].IDCliente);
				ClientesCadastrados++ ;
			}
			else
			{
				error("Cadastro Invalidado");
				
			}

			if (!confirmacao("\nDeseja efetuar cadastro de um novo cliente?", 'Y', comMensagemDeErro))
			{
				continua = 0;
			}
	}
	
}

int setupCliente()
{
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("################      Setup de desconto dos Clientes      #####################\n");
	printf("#                                                                             #\n");
	printf("#   É possivel por regra alterar valor default da régua de desconto para      #\n");
	printf("#    todos os clientes fidelidade cadastrados e também o percentual de        #\n");
	printf("#   descontos que os clientes terão para compras apartir desse saldo.         #\n");
	printf("#                                                                             #\n");
	printf("#     ---------------------  Painel de desconto  ------------------           #\n");
	printf("#     /  Acima de R$%.f\tgastos\t          %.1f%% desc.\t  /           #\n", descUm, percUm);
	printf("#     /  Acima de R$%.f\tgastos\t          %.1f%% desc.\t  /           #\n", descDois,percDois);
	printf("#     /  Acima de R$%.f\tgastos\t          %.1f%% desc.\t  /           #\n",descTres,percTres);
	printf("#     /  Acima de R$%.f\tgastos\t          %.1f%% desc.\t  /           #\n",descQuat,percQuat);
	printf("#     -------------------------------------------------------------           #\n");
	printf("###############################################################################\n");

	if (confirmacao("Deseja alterar valores padronizados? (Y/N)", 'Y', comMensagemDeErro))
	{
		system("cls");
		printf("Informe o valor a ser alterado:\n\n");
		printf("0- Cancelar\n\n");
		char auxDes[100];
		float auxDesconto, auxPercentual;
		printf("1- Acima de R$%2.f   gastos                %.1f%% desc.\n", descUm, percUm);
		printf("2- Acima de R$%2.f   gastos                %.1f%% desc.\n", descDois, percDois);
		printf("3- Acima de R$%2.f  gastos                %.1f%% desc.\n", descTres, percTres);
		printf("4- Acima de R$%2.f gastos                %.1f%% desc.\n", descQuat, percQuat);
		leituraSwitch(auxDes);

			switch (auxDes[0])
		{
			case '1':
			{
				printf("Insira novo valor da régua: ");
				scanf_s("%f", &auxDesconto);
				if (auxDesconto < 0)
				{
					error("Valor da régua não pode ser negativo");
					break;
				}
				printf("Insira novo valor do percentual: ");
				scanf_s("%f", &auxPercentual);
				if (auxPercentual < 0)
				{
					error("Valor do percentual não pode ser negativo");
					break;
				}
				printf("\nConfirma alteração da régua de: R$%.1f para: R$%.1f\n",descUm, auxDesconto);
				printf("Confirma alteração do percentual de: %.2f%% para: %.2f%% ? (Y/N)\n", percUm, auxPercentual);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					descUm = auxDesconto;
					percUm = auxPercentual;
					error("Valores alterados");
				}
				else
				{
					error("Valores não alterados");
				}
				break;
			}
			case '2':
			{

				printf("Insira novo valor da régua: ");
				scanf_s("%f", &auxDesconto);
				if (auxDesconto < 0)
				{
					error("Valor da régua não pode ser negativo");
					break;
				}
				printf("Insira novo valor do percentual: ");
				scanf_s("%f", &auxPercentual);
				if (auxPercentual < 0)
				{
					error("Valor do percentual não pode ser negativo");
					break;
				}
				printf("\nConfirma alteração da régua de: R$%.1f para: R$%.1f\n", descDois, auxDesconto);
				printf("Confirma alteração do percentual de: %.2f%% para: %.2f%% ? (Y/N)\n", percDois, auxPercentual);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					descDois = auxDesconto;
					percDois = auxPercentual;
					error("Valores alterados");
				}
				else
				{
					error("Valores não alterados");
				}
				break;
			}
			case '3':
			{
				printf("Insira novo valor da régua: ");
				scanf_s("%f", &auxDesconto);
				if (auxDesconto < 0)
				{
					error("Valor da régua não pode ser negativo");
					break;
				}
				printf("Insira novo valor do percentual: ");
				scanf_s("%f", &auxPercentual);
				if (auxPercentual < 0)
				{
					error("Valor do percentual não pode ser negativo");
					break;
				}
				printf("\nConfirma alteração da régua de: R$%.1f para: R$%.1f\n", descTres, auxDesconto);
				printf("Confirma alteração do percentual de: %.2f%% para: %.2f%% ? (Y/N)\n", percTres, auxPercentual);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					descTres = auxDesconto;
					percTres = auxPercentual;
					error("Valores alterados");
				}
				else
				{
					error("Valores não alterados");
				}
				break;
			}
			case '4':
			{
				printf("Insira novo valor da régua: ");
				scanf_s("%f", &auxDesconto);
				if (auxDesconto < 0)
				{
					error("Valor da régua não pode ser negativo");
					break;
				}
				printf("Insira novo valor do percentual: ");
				scanf_s("%f", &auxPercentual);
				if (auxPercentual < 0)
				{
					error("Valor do percentual não pode ser negativo");
					break;
				}
				printf("\nConfirma alteração da régua de: R$%.1f para: R$%.1f\n", descQuat, auxDesconto);
				printf("Confirma alteração do percentual de: %.2f%% para: %.2f%% ? (Y/N)\n", percQuat, auxPercentual);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					descQuat = auxDesconto;
					percQuat = auxPercentual;
					error("Valores alterados");
				}
				else
				{
					error("Valores não alterados");
				}
				break;
			}
			case '0':
			{
				break;
			}
			default:
				error("Valor inválido");
				break;
		}
	}
	return 1;

}

bool existeCpfCnpj(char * cpf, int * id){

	int  i;

	for (i = 0; i < ClientesCadastrados; i++)
	{
		if (strcmp(cpf, Cli[i].CPFCliente) == 0)
		{
			if (id == 0)
			{
				error( strcat("O CPF/CNPJ informado já esta cadastrado para o Cliente: ", Cli[i].NomeCliente) );
			}

			*id = i; 
			// passando o ID do cliente cujo dado foi encontrado
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
				error( strcat("O EMAIL informado já esta cadastrado para o Cliente: ", Cli[i].NomeCliente) ) ;
			}
			 * id =  i ;
			 // passando o ID do cliente cujo dado foi encontrado

			return false;
		}
	}

	return true;
}

#endif