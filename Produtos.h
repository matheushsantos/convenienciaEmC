#ifndef _PRODUTOS_H_
#define _PRODUTOS_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#include "Funcoes.h"
#include "Caixa.h"
//#include "Clientes.h"
//#include "Venda.h"

#define combustivel 1 
#define bebida 2
#define comida 3
#define diversos 4

struct Produtos
{
	char nomeProduto[100];
	char fornecedor[100];
	float valor;
	int qntProduto;
	int id;
	int categoria;
};

/*Declaração de Variaveis e funções dos produtos*/

void funcaoProduto();
void estoqueProdutos();
int menuCadastrarProduto();
int menuAlterarValorProduto();
bool menuAlterarTaxa();
int listarCategoria( bool pause);
int listarGeral();
int entradaProd();
int saidaProd();
struct Produtos * prod;

/*Variaveis de controle*/
int idProduto = 0;
/*Functions*/

void funcaoProduto()
{
	char opcaoMenuProduto[100];
	while (opcaoMenuProduto[0] != '0')
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################# Menu de Produtos ################################\n");
		printf("#                                                                             #\n");
		printf("#         1 - Para acessar o estoque                                          #\n");
		printf("#         2 - Para Cadastrar (Adquirir) produto                               #\n");
		printf("#         3 - Para alterar o valor de algum produto                           #\n");
		printf("#         4 - Para alterar o valor da taxa de lucro                           #\n");
		printf("#         0 - Para retornar ao menu principal                                 #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		leituraSwitch(opcaoMenuProduto);

		switch (opcaoMenuProduto[0])
		{
		case ('1') :
		{
			system("cls");
			estoqueProdutos();
			//getchar();
			break;
		}
		case ('2') :
		{
			menuCadastrarProduto();
			//getchar();
			break;
		}
		case ('3') :
		{
			system("cls");
			menuAlterarValorProduto();
			break;
		}
		case ('4') :
		{
			system("cls");

			if (menuAlterarTaxa())
			{
				error("Taxa cadastrada com sucesso");
			}
			else
			{
				error("Taxa não cadastrada");
			}
			break;
		}
		case ('0') :
		{
			//error("Encerrando Menu de Produtos");
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



void estoqueProdutos()
{
	char menu[100];
	while (menu[0] != '0')
	{
		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################ Estoque de Produto ###############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");

		printf("1-Listar por Categoria\n");
		printf("2-Listagem Geral\n");
		printf("3-Entrada de Produtos\n");
		printf("4-Baixa de Produtos (Cortesias/Furtos)\n");
		printf("0-Retorno ao Menu de Produtos\n");
		leituraSwitch(menu);

		switch (menu[0])
		{
		case ('1') :
		{
			system("cls");
			listarCategoria(true);
			break;
		}
		case ('2') :
		{
			system("cls");
			listarGeral();
			break;
		}
		case ('3') :
		{
			system("cls");
			entradaProd();
			break;
		}
		case ('4') :
		{
			system("cls");
			saidaProd();
			break;
		}
		case('0') :
		{
			break;
		}
		default:
		{
			error("Valores inválidos");
			break;
		}

		}
	}
}

int menuCadastrarProduto(){

	if (getCaixa())
	{
		bool continua = true;
		while (continua)
		{

			system("cls");
			printf("###############################################################################\n");
			printf("#                                                                             #\n");
			printf("############################ Cadastro de Produto ##############################\n");
			printf("#                                                                             #\n");
			printf("###############################################################################\n");

			//############################## ALOCANDO MEMÓRIA##############################################
			if (idProduto == 0)
			{
				prod = (struct Produtos *)malloc(sizeof(struct Produtos));

			}
			else if (idProduto >= 1)
			{
				prod = (struct Produtos *)realloc(prod, (idProduto + 1)*sizeof(struct Produtos));
			}
			//############################################################################################

			/*Mensagens de Auxilio*/
			printf("\n****0- Para Cancelar****\n");
			printf("\n*** Id Produto: %d ***\n", idProduto + 1);

			/*NOME DO PRODUTO*/
			printf("Nome do Prod.: ");
			fflush(stdin);
			fgets(prod[idProduto].nomeProduto, 100, stdin);
			if (prod[idProduto].nomeProduto[0] == '0') return 0;
			if (!validarNomePrd(prod[idProduto].nomeProduto, comMensagemDeErro)) return 0;

			/*Função Criada para Converter String p/ UpperCase*/
			convertToUpper(prod[idProduto].nomeProduto);

			/*Fornecedor*/
			printf("\nNome do Fornecedor/Marca: ");
			fflush(stdin);
			fgets(prod[idProduto].fornecedor, 100, stdin);
			if (prod[idProduto].fornecedor[0] == '0') return 0;
			if (!validarNomePrd(prod[idProduto].fornecedor, comMensagemDeErro)) return 0;
			convertToUpper(prod[idProduto].fornecedor);

			/*Valor do Produto recebido*/
			printf("\nValor de Tabela: R$");
			scanf_s("%f", &prod[idProduto].valor);
			if (prod[idProduto].valor == 0) return 0;
			if (prod[idProduto].valor < 0)
			{
				error("Valor do Produto Inválido");
				return 0;
			}

			/*Quantidade de Produtos*/
			printf("\nQndt Produtos: ");
			scanf_s("%d", &prod[idProduto].qntProduto);
			if (prod[idProduto].qntProduto == 0)  return 0;
			if (prod[idProduto].qntProduto < 0)
			{
				error("Quantidade de Produtos Inválida");
				return 0;
			}

			/*Categoria do Produto*/
			char catAux[100];
			printf("Categoria do Produto: \n1-Combustivel\n2-Bebida\n3-Alimentos\n4-Diversos\n0-Sair\n");
			scanf("%s", &catAux);

			int cat = validaCat(catAux, comMensagemDeErro);
			if (cat == 0)
			{
				error("Cadastro Cancelado");
				return 0;
			}
			else prod[idProduto].categoria = cat;
			//if (prod[idProduto].categoria == 0) return 0;



			/*Calculo para descontar produtos do caixa*/

			float totalEntrada = 0;
			totalEntrada = prod[idProduto].qntProduto * prod[idProduto].valor;
			printf("\nConfirma baixa de R$%.2f no caixa? (Y/N)\n", totalEntrada);
			if (confirmacao("", 'Y', semMensagemDeErro))
			{
				caixa[diaAtual].entradaDiaria -= totalEntrada;
			}
			else
			{
				error("Cadastro cancelado");
				return 0;
			}


			
			prod[idProduto].id = idProduto+1 ;

			printf("\nId do Produto: %d\n***Cadastro Concluido***\n\n", prod[idProduto].id);
			idProduto++;
			system("pause");
			
			if (confirmacao("Deseja efetuar um novo cadastro/entrada de produto? (Y/N)", 'Y', comMensagemDeErro))
			{
				continua = true;
			}
			else
			{
				continua = false;
			}
		}
		return 1;
	}
	else
	{
		error("O caixa encontra-se fechado");
		if (confirmacao("Deseja ir para tela de abertura do caixa? (Y/N)", 'Y', comMensagemDeErro))
		{
			abrirDia();
		}
		else
		{
			error("Retorno ");
		}
	}
}

int menuAlterarValorProduto(){

	if (idProduto >= 1)
	{

		int codProd;
		float newValue;
		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("######################## Alterar Valor de Produto #############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		if (listarCategoria(false) == 0) return 0;
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);
		if (codProd > 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			printf("Valor Cadastrado: R$%.2f\n", prod[codProd].valor);

			printf("Insira novo preco: R$");
			scanf_s("%f", &newValue);
			if (newValue > 0)
			{
				printf("\nConfirma alteracao de: R$%.2f para: R$%.2f ao Produto (Y/N)\n", prod[codProd].valor, newValue);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					prod[codProd].valor = newValue;
					printf("\nValor Atual: R$%.2f\n", prod[codProd].valor);
					error("Alteração confirmada");
				}
				else
				{
					error("Alteração cancelada");
				}

			}
			else
			{
				error("Preço inválido, favor inserir um valor maior que zero (0)");
			}
		}
		else
		{
			error("Id inserido inexistente");

		}

	}
	else
	{
		printf("\n**Nenhum produto cadastrado**\n");
		if (confirmacao("Deseja ir para o Cadastro de Produtos? (Y/N)", 'Y', comMensagemDeErro))
		{
			menuCadastrarProduto();
		}
		else
		{
			error("Encaminhamento para tela de produtos não confirmado");
			return 0;
		}
	}


	return 1;
}



int listarCategoria(bool pause){

	int i;
	char catAux[100];
	if (idProduto >= 1)
	{

		printf("Insira o Id da Categoria:\n1-Combustivel\n2-Bebida\n3-Alimentos\n4-Diversos\n0-Sair\n");
		scanf("%s", &catAux);
		int cat = validaCat(catAux, comMensagemDeErro);
		if (cat != 0)
		{
			bool auxEncontrou = false;

			system("cls");
			for (i = 0; i < idProduto; i++)
			{
				if (prod[i].categoria == cat)
				{
					auxEncontrou = true;
					printf("Nome do Produto: %s", prod[i].nomeProduto);
					printf("Id do Produto: %d\n", prod[i].id);
					printf("Fornecedor: %s", prod[i].fornecedor);
					printf("Qntd Disponivel: %d\n", prod[i].qntProduto);

					if (prod[i].categoria == combustivel)
					{
						printf("Categoria: Combustivel\n\n");
					}
					if (prod[i].categoria == bebida)
					{
						printf("Categoria: Bebida\n\n");
					}
					if (prod[i].categoria == comida)
					{
						printf("Categoria: Alimentos\n\n");
					}
					if (prod[i].categoria == diversos)
					{
						printf("Categoria: Diversos\n\n");
					}
				}
			}
			
			if (auxEncontrou)
			{
				if (pause) system("pause");
				return 1;
			}
			else
			{
				error("Não foram encontrados produtos com essa categoria");
				return 0;
			}
			
		}
		else
		{	
			return 0;
		}
	}
	else
	{
		
		printf("\n**Nenhum produto cadastrado**\n");
		if (confirmacao("Deseja ir para o Cadastro de Produtos? (Y/N)", 'Y', comMensagemDeErro))
		{
			menuCadastrarProduto();
		}
		else
		{
			error("Encaminhamento para tela de produtos não confirmado");
			return 0;
		}
	}

	return 1;
}

int listarGeral(){

	int i;

	if (idProduto >= 1)
	{


		for (i = 0; i < idProduto; i++)
		{

			printf("Nome do Produto: %s", prod[i].nomeProduto);
			printf("Id do Produto: %d\n", prod[i].id);
			printf("Fornecedor: %s", prod[i].fornecedor);
			printf("Qntd Disponivel: %d\n", prod[i].qntProduto);

			if (prod[i].categoria == combustivel)
			{
				printf("Categoria: Combustivel\n\n");
			}
			if (prod[i].categoria == bebida)
			{
				printf("Categoria: Bebida\n\n");
			}
			if (prod[i].categoria == comida)
			{
				printf("Categoria: Alimentos\n\n");
			}
			if (prod[i].categoria == diversos)
			{
				printf("Categoria: Diversos\n\n");
			}


		}
		system("pause");
	}
	else
	{
		error("Nenhum produto cadastro");
		if(confirmacao("Deseja Cadastrar Produtos? (Y/N)", 'Y', comMensagemDeErro))
		{
			if (menuCadastrarProduto()) return 0;
		}
		else
		{
			return 0;
		}
	}
	return 1 ;
}

int entradaProd(){
	int codProd, qnt;
	if (idProduto >= 1)
	{
		printf("#################### ENTRADA DE PRODUTOS ####################\n");
		if (!listarCategoria(false))
		{
			//error("Categoria Inválida");
			return 0;
		}
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);

		if (codProd > 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			printf("Qntd Disponivel: %d\n", prod[codProd].qntProduto);

			printf("Insira qntd Entrada: ");
			scanf_s("%d", &qnt);
			if (qnt > 0)
			{
				float totalEntrada = 0;
				totalEntrada = qnt * prod[codProd].valor;
				printf("\nConfirma entrada de: %d unid. ao Produto?", qnt);
				printf("\nConfirma baixa de R$%.2f no caixa? (Y/N)\n", totalEntrada);
				if (confirmacao("",'Y', semMensagemDeErro))
				{
					
					caixa[diaAtual].entradaDiaria -= totalEntrada;
					prod[codProd].qntProduto += qnt;

					printf("\nValor Atual de Unid.: %d\n", prod[codProd].qntProduto);
					error("Entrada Confirmada");
				}
				else
				{
					error("Entrada Cancelada");
				}
			}
			else
			{
				error("Quantidade Inválida");
			}
		}
		else
		{
			error("Id Inválido");
		}
	}
	else
	{
		error("Nenhum produto cadastro");
		if (confirmacao("Deseja Cadastrar Produtos? (Y/N)", 'Y', comMensagemDeErro))
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
int saidaProd(){


	int codProd, qnt;
	if (idProduto >= 1)
	{
		printf("#################### ENTRADA DE PRODUTOS ####################\n");
		if (!listarCategoria(false))
		{
			//error("Categoria Inválida");
			return 0;
		}
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);

		if (codProd > 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			printf("Qntd Disponivel: %d\n", prod[codProd].qntProduto);

			printf("Insira qntd Saida: ");
			scanf_s("%d", &qnt);
			if (qnt > 0 && ( (prod[codProd].qntProduto - qnt) >= 0 ) )
			{	
				printf("\nConfirma saida de: %d ao Produto (Y/N)\n", qnt);
				if (confirmacao("", 'Y', semMensagemDeErro))
				{
					prod[codProd].qntProduto -= qnt;
					printf("\nValor Atual: %d\n", prod[codProd].qntProduto);
					error("Baixa Confirmada");
				}
				else
				{
					system("cls");
					error("Baixa Cancelada");
				}
			}
			else
			{
				error("Alteração Cancelada, valores insuficientes para baixa");
			}
		}
		else
		{
			error("Id Invalido");
		}
	}
	else
	{
		error("Nenhum produto cadastro");
		printf("\n");
		
		if (confirmacao("Deseja Cadastrar Produtos? (Y/N)", 'Y', comMensagemDeErro))
		{
			menuCadastrarProduto();
		}
		else
		{
			return  0;
		}
	}
	return 1;
}

int pesquisaProduto(){
	int pesquisa;
	printf("\n******Pesquisar Produto: ******\n1-Id\n2-Nome\n0-Cancelar\n");
	scanf_s("%d", &pesquisa);

	switch (pesquisa)
	{
	case (1) : 
	{
		int idPesquisa;
		printf("Informe o Id: ");
		scanf_s("%d", &idPesquisa);
		if ((idPesquisa > 0 && idProduto > 0) && (idPesquisa <= idProduto))
		{
			idPesquisa -- ;
			printf("\nNome: %s", prod[idPesquisa].nomeProduto);
			printf("Id Produto: %d\n", prod[idPesquisa].id);
			printf("Valor: R$%.2f", prod[idPesquisa].valor);
			getchar();
			//getchar();
			return prod[idPesquisa].id;
		}
		else
		{
			printf("***Id Nao Encontrado***");
			getchar();
			getchar();
			return -1;
		}
		break;
	}
	case (2) :
	{
		char nomePesquisa[100];
		int i, aux = 0 ;

		printf("Informe o Nome para Consulta: ");
		fflush(stdin);
		fgets(nomePesquisa, 100, stdin);
	
		convertToUpper(nomePesquisa);

		for (i = 0; i < idProduto; i++)
		{
			if (strcmp(prod[i].nomeProduto, nomePesquisa) == 0)
			{
				printf("\nNome: %s", prod[i].nomeProduto);
				printf("Id Produto: %d\n", prod[i].id);
				printf("Valor: R$%.2f", prod[i].valor);
				//getchar();
				//getchar();
				aux = 1 ;
				return prod[i].id;
			}
		}
		if (aux == 0)
		{
			printf("***Id Nao Encontrado***");
			getchar();
			// getchar();
			return -1;
		}
		
		break;
	}
	case (0) :
	{
		return -2;
		break;
	}
	default:
		printf("**Valor Invalido**");
		getchar();
		getchar();
		getchar();
		return -1;
		break;
	}
	return 0;
}

#endif