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
#include "Caixa.h"

#define idVendaFidelidade 2
#define idVendaAvulsa 1 

void funcaoVenda();
int vendaAvulsa();
int vendaFidelidade();
float vendaProdutos(int tipoVenda, int idCli);

void funcaoVenda(){

	char menuVenda[100];
	while (menuVenda[0] != '0')
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
		leituraSwitch(menuVenda);

		switch (menuVenda[0])
		{
		case ('1') :
		{
			vendaAvulsa();
			break;
		}
		case ('2') :
		{
			 vendaFidelidade();
			break;
		}
		case ('0') :
		{
			//error("Encerrando Menu de Vendas");
			break;
		}
		default:
		{
			fflush(stdin);
			system("cls");
			error("**Valor Inválido**");
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
			vendaProdutos(idVendaAvulsa, NULL);
			return 1;
}

int vendaFidelidade(){
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("############################# Efetuar Venda Fidelidade ########################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");
	if (ClientesCadastrados > 0)
	{
		//int foundCpf = 0 , foundEmail;
		int   id = -1 ;
		int * pont = &id ;
		char busca[100];
		printf("\n*Insira o CPF/CNPJ ou Email do Cliente: \n");
		fflush(stdin);
		fgets(busca, 100, stdin);
		if (busca[0] == '0' && strlen(busca) <= 2 ) return 0;
		//scanf("%s", &busca);
		//strcat(busca, "\n");
		//Buscando o id do cliente atraves do parametro 'out'= pont da função
		if (!existeCpfCnpj(busca, pont) || !existeMail(busca, pont))
		{
			id = *pont;

			printf("\nNome: %s", Cli[id].NomeCliente);
			printf("CPF/CNPJ: %s", Cli[id].CPFCliente);
			printf("Email: %s", Cli[id].emailCliente);

			//printf("pressione Enter . . . .\n");

			if (confirmacao("Confirma os Dados do Cliente? (Y/N)", 'Y', comMensagemDeErro, NULL))
			{
				while (true)
				{
						//FUNÇÃO RESPONSÁVEL PELO VENDA E RETORNO DO VALOR
						float x = vendaProdutos(idVendaFidelidade, id);
						if (x > 0)
						{
							Cli[id].TotalVendas++;
							Cli[id].TotalGasto += x;
							printf("\Deseja efetuar nova venda para o Cliente Id: %d ? (Y/N)\n", Cli[id].IDCliente);
							if (!confirmacao("", 'Y', semMensagemDeErro, true))
							{
								break;
							}
						}
						else
						{
							return 0;
						}
				}

			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(confirmacao("Cliente não cadastrado, deseja Cadastrar Cliente? (Y/N)",'Y', comMensagemDeErro, NULL))
			{
				MenuCadastroCliente();
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
	//	ClientesCadastrados = 0;
		if (confirmacao("Nenhum Cliente cadastrado, deseja Cadastrar Cliente? (Y/N)", 'Y', comMensagemDeErro, true))
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

float vendaProdutos(int tipoVenda, int idCli){

	if (idProduto > 0)
	{
		if (diaAtual >= 0)
		{
			if (caixa[diaAtual].aberto)
			{
				system("cls");
				int id;
				char yn, maisVenda = 'Y';
				float numVenda, valorRecebido, valorVenda, trocoVenda;

				while (maisVenda == 'Y')
				{
					valorVenda = 0;
					valorRecebido = 0;
					trocoVenda = 0;
					numVenda = 0;
					//Tratamento para retorno do Id, para trabalhar variavel no indice da struct
					id = pesquisaProduto() - 1;
					if (id == -3) break;
					/*Retorno da pesquisaProduto -1 se nao encontrar produtos*/
					if (id != -2)
					{
						printf("\nQntde de Produtos Vendidos (Unidade/Litro/Kg): ");
						scanf_s("%f", &numVenda);
						if ((numVenda > 0) && (numVenda <= prod[id].qntProduto))
						{
							/*Calculo da Venda*/ 
							if (lucroProd > 0)
							{
								valorVenda = ((prod[id].valor * lucroProd) + prod[id].valor) * numVenda;
							}
							else
							{
								valorVenda = (prod[id].valor * numVenda);
							}
							/*Calculo dos descontos*/
							if (tipoVenda == idVendaFidelidade)
							{
								float descontoVenda = 0;

								if (Cli[idCli].TotalGasto + valorVenda > descQuat && descQuat > 0)
								{
									descontoVenda = ((valorVenda * percQuat) / 100);
									valorVenda = valorVenda - descontoVenda;
									printf("\n**ATENÇÃO**\nHouve um desconto de %.1f%% na compra\n", percQuat);
									system("pause");
								}
								else if (Cli[idCli].TotalGasto + valorVenda > descTres && descTres > 0)
								{
									descontoVenda = ((valorVenda * percTres) / 100);
									valorVenda = valorVenda - descontoVenda;
									printf("\n**ATENÇÃO**\nHouve um desconto de %.1f%% na compra\n", percTres);
									system("pause");
								}
								else if (Cli[idCli].TotalGasto + valorVenda > descDois && descDois > 0)
								{
									descontoVenda = ((valorVenda * percDois) / 100);
									valorVenda = valorVenda - descontoVenda;
									printf("\n**ATENÇÃO**\nHouve um desconto de %.1f%% na compra\n", percDois);
									system("pause");
								}
								else if (Cli[idCli].TotalGasto + valorVenda > descUm && descUm > 0)
								{
									descontoVenda = ((valorVenda * percUm) / 100);
									valorVenda = valorVenda - descontoVenda;
									
									printf("\n**ATENÇÃO**\nHouve um desconto de %.1f%% na compra\n", percUm);
									system("pause");
								}
								if (lucroProd > 0 && descontoVenda > 0)
								{
									printf("\nValor Venda: ( R$%.2f * %.2f ) + %.1f%%tx. - R$%.2f = R$%.2f \n", prod[id].valor, numVenda, lucroProd * 100, descontoVenda, valorVenda);
								}
								else if (lucroProd > 0)
								{
									printf("\nValor Venda: R$%.2f * %.2f + %.1f%%tx. = R$%.2f \n", prod[id].valor, numVenda, lucroProd * 100, valorVenda);
								}
								else if (descontoVenda > 0)
								{
									printf("\nValor Venda: R$%.2f * %.2f - R$%.2f = R$%.2f \n", prod[id].valor, numVenda, descontoVenda, valorVenda);
								}
								else
								{
									printf("\nValor Venda: R$%.2f * %.2f = R$%.2f \n", prod[id].valor, numVenda, valorVenda);
								}
							}
							else
							{
								if (lucroProd > 0)
								{
									printf("\nValor Venda: R$%.2f * %.2f + %.1f%%tx. = R$%.2f \n", prod[id].valor, numVenda, lucroProd * 100, valorVenda);
								}
								else
								{
									printf("\nValor Venda: R$%.2f * %.2f = R$%.2f \n", prod[id].valor, numVenda, valorVenda);
								}
							}
	
							printf("\nValor Recebido: R$");
							scanf_s("%f", &valorRecebido);

							/*Troco Cliente*/
							if (valorRecebido >= valorVenda)
							{
								trocoVenda = (valorRecebido - valorVenda);
								printf("\nTroco: R$%.2f", trocoVenda);

								if (confirmacao("Deseja confirma venda? (Y/N)", 'Y', comMensagemDeErro, true))
								{

										prod[id].qntProduto -= numVenda;
										caixa[diaAtual].totalVendaDia += valorVenda;
										caixa[diaAtual].numVendaDia++;

									/*Venda para cliente fidelidade*/
									if (tipoVenda == idVendaFidelidade)
									{
										error("Venda Confirmada");
										return valorVenda;
									}
									else if (tipoVenda == idVendaAvulsa)
									{
										error("Venda Confirmada");
										if (confirmacao("Deseja efetuar nova Venda Avulsa? (Y/N)", 'Y', comMensagemDeErro, true))
										{
											system("cls");
											continue;
										}
										else
										{
											break;
										}
									}
								}
							}
							else
							{
								system("cls");
								error("Venda cancelada, insuficiente para completar a venda");
								return 0;
							}
						}
						else
						{
							system("cls");
							error("Venda cancelada, quantidade indisponivel no momento");
						}

						return 0;
					}
				}
			}
			else
			{
				printf("\n**Abrir Caixa para Disponbilizar Venda**\n");
				system("pause");
				abrirDia();
			}
		}
		else
		{
			printf("\n**Abrir Caixa para Disponbilizar Venda**\n");
			system("pause");
			abrirDia();
		}
	}
	else
	{
		if(confirmacao("Nenhum produto cadastrado, deseja Cadastrar Produtos? (Y/N)",'Y',comMensagemDeErro, true))
		{
			menuCadastrarProduto();
		}
		else
		{
				return 0;
		}
	}
return 0;
}

#endif