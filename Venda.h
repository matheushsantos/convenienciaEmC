#ifndef _VENDA_H_
#define _VENDA_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>

#include "Funcoes.h"
#include "Produtos.h"
#include "Clientes.h"

#define idVendaFidelidade 2
#define idVendaAvulsa 1 

void funcaoVenda();
int vendaAvulsa();
int vendaFidelidade();
int vendaProdutos(int tipoVenda);
int menuVenda = -1 ;
void funcaoVenda(){

	menuVenda = -1;
	while (menuVenda != 0)
	{
		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################# Menu de Vendas ##################################\n");
		printf("#                                                                             #\n");
		printf("#         1 - Para Venda Avulsa                                               #\n");
		printf("#         2 - Para Cliente Fidelidade                                         #\n");
		printf("#         0 - Para Retornar ao Menu Principal                                 #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		scanf_s("%d", &menuVenda);

		switch (menuVenda)
		{
		case (1) :
		{
			vendaAvulsa();
			break;
		}
		case (2) :
		{
			 vendaFidelidade();
			break;
		}
		case (0) :
		{
			
			break;
		}
		default:
		{
			printf("**Valores Invalidos**");
			getchar();
			break;
		}
		}
	}
}



int vendaAvulsa() {
				system("cls");
			printf("###############################################################################\n");
			printf("#                                                                             #\n");
			printf("############################# Efetuar Venda Avulsa ############################\n");
			printf("#                                                                             #\n");
			printf("###############################################################################\n");
			vendaProdutos(idVendaAvulsa);
			return 1;
}

int vendaFidelidade(){

	if (ClientesCadastrados > 0)
	{
		//int foundCpf = 0 , foundEmail;
		int   id = -1 ;
		int * pont = &id ;
		char busca[100];
		printf("\n*Insira o CPF/CNPJ ou Email do Cliente: \n");
		fflush(stdin);
		fgets(busca, 100, stdin);

		//Buscando o id do cliente atraves do parametro 'out'= pont da função
		if (!existeCpfCnpj(busca, pont) || !existeMail(busca, pont))
		{
			id = *pont;

			printf("\nNome: %s", Cli[id].NomeCliente);
			printf("CPF/CNPJ: %s", Cli[id].CPFCliente);
			printf("Email: %s", Cli[id].emailCliente);
			
			char yn;
			printf("\Confirma os Dados do Cliente? (Y/N)\n");
			getchar();
			scanf_s("%c", &yn);
			yn = toupper(yn);

			if (yn == 'Y')
			{
				vendaProdutos(idVendaFidelidade);
			}
			else
			{
				return 0;
			}
			
		}
		else
		{
			printf("**Cliente não cadastrado***");
			system("pause");
		}

	}
	else
	{
	//	ClientesCadastrados = 0;
		printf("\n**Nenhum Cliente cadastrado**\n\n");
		char yn;
		printf("\nDeseja Cadastrar Cliente? (Y/N)\n");
		getchar();
		scanf_s("%c", &yn);

		yn = toupper(yn);
		if (yn == 'Y')
		{
			MenuCadastroCliente();
		}
		else
		{
			return 0;
		}
	}
	return 1;

}

int vendaProdutos( int tipoVenda){

	if (idProduto > 0)
	{
		system("cls");
		int id;
		char yn, maisVenda = 'Y';
		float numVenda, valorRecebido, valorVenda, trocoVenda;

		while (maisVenda == 'Y')
		{
			//Tratamento para retorno do Id, para trabalhar variavel no indice da struct
			id = pesquisaProduto() - 1;
			if (id == -3) break;
			//Retorno da pesquisaProduto -1 se nao encontrar produtos
			if (id != -2)
			{
				printf("\nQntde de Produtos Vendidos (Unidade/Litro/Kg): ");
				scanf_s("%f", &numVenda);
				if ((numVenda > 0) && (numVenda <= prod[id].qntProduto))
				{
					//Calculo da Venda

					valorVenda = (prod[id].valor * numVenda);
					printf("\nValor Venda: R$%.2f * %.2f = R$%.2f\n", prod[id].valor, numVenda, valorVenda);

					printf("\nValor Recebido: R$");
					scanf_s("%f", &valorRecebido);

					//Troco Cliente

					if (valorRecebido >= valorVenda)
					{
						trocoVenda = (valorRecebido - valorVenda);
						printf("\nTroco: R$%.2f", trocoVenda);


						printf("\nConfirma Venda? (Y/N)\n");
						getchar();
						scanf_s("%c", &yn);

						yn = toupper(yn);
						if (yn == 'Y')
						{
							//Açao do Caixa
							printf("\n**Venda Confirmada**\n\n");
							prod[id].qntProduto -= numVenda;

							//Venda para cliente fidelidade
							if (tipoVenda == idVendaFidelidade)
							{
								return valorVenda;
							}
							else if (tipoVenda == idVendaAvulsa)
							{
								printf("\Deseja efetuar nova Venda Avulsa? (Y/N)\n");
								getchar();
								scanf("%c", &maisVenda);
								yn = toupper(maisVenda);
							}
							if (maisVenda == 'Y')
							{

								continue;
							}
							else
							{
								break;
							}
						}
						else
						{
							maisVenda = 'N';
							system("cls");
							printf("\n**Venda Cancelada**\n");
							system("pause");

							return 0;
						}
					}
					else
					{
						system("cls");
						printf("\n**Venda cancelada**\n**Valor insuficiente para completar a venda**\n");
						system("pause");
						return 0;
					}
				}
				else
				{
					system("cls");
					printf("\n**Venda cancelada quantidade indisponivel no momento**\n");
					system("pause");
				}
				//getchar();

				//getchar();
				return 1;
			}
		}
	}
	else
	{
		printf("\n**Nenhum produto cadastrado**\n\n");
		char yn;
		printf("\nDeseja Cadastrar Produtos? (Y/N)\n");
		getchar();
		scanf_s("%c", &yn);

		yn = toupper(yn);
		if (yn == 'Y')
		{
			menuCadastrarProduto();
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

#endif