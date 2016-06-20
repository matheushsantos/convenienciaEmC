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
void consultaSaldo();
void exibirClientes();
int setupCliente();
void MenuCadastroCliente();     
void MenuHistoricoCliente();

bool existeCpfCnpj(char * cpf, int * id); // id 0 para exibição de mensagem de invalidez
bool existeMail(char * email, int * id); // id 0 para exibição de mensagem de invalidez
bool alteraDescontosCli(char numero);
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
			consultaSaldo();
			break;
		}
		case('3') :
		{
			exibirClientes();
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
		if (Cli[ClientesCadastrados].NomeCliente[0] == 'x' && (strlen(Cli[ClientesCadastrados].NomeCliente) <= 2))  break;
		if (!validaNomeClie(Cli[ClientesCadastrados].NomeCliente, comMensagemDeErro)) break;

		/*DEIXANDO MAIUSCULO*/
		convertToUpper(Cli[ClientesCadastrados].NomeCliente);


		/*E-mail*/
		printf("\nInsira o email do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].emailCliente, 50, stdin);
		if (Cli[ClientesCadastrados].emailCliente[0] == 'x' && (strlen(Cli[ClientesCadastrados].emailCliente) <= 2 ))  break;
		if (!validaEmail(Cli[ClientesCadastrados].emailCliente, comMensagemDeErro)) break;

		/*Telefone do Cliente*/
		printf("\n**Somente Numeros**\nInsira o telefone do cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].TelefoneCliente, 20, stdin);
		if (Cli[ClientesCadastrados].TelefoneCliente[0] == 'x' && (strlen(Cli[ClientesCadastrados].TelefoneCliente) <= 2))  break;
		if (!validaTel(Cli[ClientesCadastrados].TelefoneCliente, comMensagemDeErro)) break;

		printf("\n**Somente Numeros**\nInsira o CPF/CNPJ do Cliente: ");
		fflush(stdin);
		fgets(Cli[ClientesCadastrados].CPFCliente,20, stdin);
		if (Cli[ClientesCadastrados].CPFCliente[0] == 'x' && (strlen(Cli[ClientesCadastrados].CPFCliente) <= 2))  break;
		if (!validaCpfCnpj(Cli[ClientesCadastrados].CPFCliente, comMensagemDeErro)) break;
		
			if (existeMail(Cli[ClientesCadastrados].emailCliente, 0) && existeCpfCnpj(Cli[ClientesCadastrados].CPFCliente, 0))
			{
				
				Cli[ClientesCadastrados].IDCliente = ClientesCadastrados + 1;
				Cli[ClientesCadastrados].TotalGasto = 0;
				Cli[ClientesCadastrados].TotalVendas = 0;
				system("cls");
				printf("\nID:\t%d\n", Cli[ClientesCadastrados].IDCliente);
				printf("Nome:\t%s", Cli[ClientesCadastrados].NomeCliente);
				printf("CPF:\t%s", Cli[ClientesCadastrados].CPFCliente);
				printf("E-mail:\t%s\n\n", Cli[ClientesCadastrados].emailCliente);
				printf("***********Cadastro concluído com sucesso***********\n\n");
				system("pause");
				ClientesCadastrados++ ;
			}
			else
			{
				error("Cadastro Invalidado");
				
			}

			if (!confirmacao("\nDeseja efetuar cadastro de um novo cliente? (Y/N)", 'Y', comMensagemDeErro))
			{
				continua = 0;
			}
	}
	
}
void consultaSaldo(){
	if (ClientesCadastrados > 0)
	{
		int   id = -1;
		int * pont = &id;
		char busca[100];
		printf("\nInsira o CPF/CNPJ ou Email do Cliente: \n");
		fflush(stdin);
		fgets(busca, 100, stdin);

		if (!existeCpfCnpj(busca, pont) || !existeMail(busca, pont))
		{
			system("cls");
			id = *pont;
			printf("\n\nId: %d\n", Cli[id].TotalGasto);
			printf("Nome: %s", Cli[id].NomeCliente);
			printf("CPF/CNPJ: %s", Cli[id].CPFCliente);
			printf("Saldo: R$%.2f\n\n\n", Cli[id].TotalGasto);

			system("pause");
		}
		else
		{
			error("Nenhum cliente encontrado");
		}
	}
	else
	{
		error("Nenhum cliente cadastrado");
		if (confirmacao("Deseje ir para Menu de Cadastro do Clientes? (Y/N)", 'Y', comMensagemDeErro))
		{
			MenuCadastroCliente();
		}
	}

}

void exibirClientes(){
	
	if (ClientesCadastrados > 0)
	{
		int i , id = ClientesCadastrados;

		system("cls");
		printf("Listagem geral das informações cadastradas de Clientes:\n\n");
		for (i = 0; i < id; i++)
		{
			printf("Nome: %s", Cli[i].NomeCliente);
			printf("Id: %d\n", Cli[i].IDCliente);
			printf("CPF/CNPJ: %s", Cli[i].CPFCliente);
			printf("Email: %s", Cli[i].emailCliente);
			printf("Telefone: %s\n", Cli[i].TelefoneCliente);
			printf("Informações sobre Vendas do(a): %s \n", Cli[i].NomeCliente);
			printf("Valor saldo gasto: R$%.2f\n", Cli[i].TotalGasto);
			printf("Numero de vendas: %d\n", Cli[i].TotalVendas);

			printf("\n\n");

		}
		system("pause");
	}
	else
	{
		error("Nenhum cliente cadastrado");
		if (confirmacao("Deseje ir para Menu de Cadastro do Clientes? (Y/N)", 'Y', comMensagemDeErro))
		{
			MenuCadastroCliente();
		}
	}


}

int setupCliente()
{
	while (true)
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
		printf("#     /  Acima de R$%2.f\tgastos         %.1f%%\tdesc.\t  /           #\n", descUm, percUm);
		printf("#     /  Acima de R$%2.f\tgastos         %.1f%%\tdesc.\t  /           #\n", descDois, percDois);
		printf("#     /  Acima de R$%2.f\tgastos         %.1f%%\tdesc.\t  /           #\n", descTres, percTres);
		printf("#     /  Acima de R$%2.f\tgastos         %.1f%%\tdesc.\t  /           #\n", descQuat, percQuat);
		printf("#     -------------------------------------------------------------           #\n");
		printf("###############################################################################\n");

		if (confirmacao("Deseja alterar valores padronizados? (Y/N)", 'Y', comMensagemDeErro))
		{
			system("cls");
			printf("Informe o valor a ser alterado:\n\n");
			printf("0- Cancelar\n\n");
			char auxDes[100];
			printf("1- Acima de R$%2.f\tgastos    %.1f%%\tdesc.\n", descUm, percUm);
			printf("2- Acima de R$%2.f\tgastos    %.1f%%\tdesc.\n", descDois, percDois);
			printf("3- Acima de R$%2.f\tgastos    %.1f%%\tdesc.\n", descTres, percTres);
			printf("4- Acima de R$%2.f\tgastos    %.1f%%\tdesc.\n", descQuat, percQuat);
			leituraSwitch(auxDes);

			switch (auxDes[0])
			{
			case '1':
			{
				alteraDescontosCli('1');
				break;
			}
			case '2':
			{
				alteraDescontosCli('2');
				break;
			}
			case '3':
			{
				alteraDescontosCli('3');
				break;
			}
			case '4':
			{
				alteraDescontosCli('4');
				break;
			}
			case '0':
			{
				break;
			}
			default:
				fflush(stdin);
				error("Valor inválido");
				break;
			}
		}
		else
		{
			return 0;
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
bool alteraDescontosCli(char numero){

	float auxDesconto, auxPercentual;

	printf("Insira novo valor da régua: ");
	scanf_s("%f", &auxDesconto);
	if (auxDesconto < 0)
	{
		error("Valor da régua não pode ser negativo");
		return false;
	}

	printf("Insira novo valor do percentual: ");
	scanf_s("%f", &auxPercentual);
	if (auxPercentual < 0)
	{
		error("Valor do percentual não pode ser negativo");
		return false;
	}

	printf("\nConfirma alteração da régua %c para: R$%.f\n", numero, auxDesconto);
	printf("Confirma alteração do percentual %c para: %.1f%% ? (Y/N)\n", numero, auxPercentual);
	if (confirmacao("", 'Y', semMensagemDeErro))
	{
		if (numero == '1')
		{
			descUm = auxDesconto;
			percUm = auxPercentual;

		}
		else if (numero == '2')
		{
			descDois = auxDesconto;
			percDois = auxPercentual;
		}
		else if (numero == '3')
		{
			descTres = auxDesconto;
			percTres = auxPercentual;
		}
		else if (numero == '4')
		{
			descQuat = auxDesconto;
			percQuat = auxPercentual;
		}
		else
		{
			error("Valor passado no parâmetro de alteração está incorreto, favor informar o responsável pelo sistema.");
			return false;
		}
		error("Valores alterados com sucesso");
		return true;
	}
	else
	{ 
		error("Valores não alterados");
	}
	return false;
}

#endif