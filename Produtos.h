#ifndef _PRODUTOS_H_
#define _PRODUTOS_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

//#include "Funcoes.h"
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

/*Declara��o de Variaveis e fun��es dos produtos*/

void funcaoProduto();
void estoqueProdutos();
int menuCadastrarProduto();
int menuAlterarValorProduto();
void menuAlterarTaxa();
int listarCategoria();
int listarGeral();
int entradaProd();
int saidaProd();
struct Produtos * prod;

/*Variaveis de controle*/
int idProduto = 0;
float lucroProd = 0;
/*Functions*/

void funcaoProduto()
{
	int opcaoMenuProduto = -1;
	while (opcaoMenuProduto != 0)
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################# Menu de Produtos ################################\n");
		printf("#                                                                             #\n");
		printf("#         1 - Para acessar o estoque                                          #\n");
		printf("#         2 - Para Cadastrar um produto                                       #\n");
		printf("#         3 - Para alterar o valor de algum produto                           #\n");
		printf("#         4 - Para alterar o valor da taxa de lucro                           #\n");
		printf("#         0 - Para retornar ao menu principal                                 #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		scanf_s("%d", &opcaoMenuProduto);

		switch (opcaoMenuProduto)
		{
		case (1) :
		{
			system("cls");
			estoqueProdutos();
			//getchar();
			break;
		}
		case (2) :
		{
			menuCadastrarProduto();
			//getchar();
			break;
		}
		case (3) :
		{
			system("cls");
			menuAlterarValorProduto();
			break;
		}
		case (4) :
		{
			system("cls");
			menuAlterarTaxa();
			break;
		}
		default:
		{
			printf("\n***Valor Invalido***\n");
			getchar();
			break;
		}
		}
	}
}



void estoqueProdutos()
{
	int menu = -1;
	while (menu != 0)
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
		scanf_s("%d", &menu);
		printf("Valor Menu: %d\n", menu);
		switch (menu)
		{
		case (1) :
		{
			system("cls");
			listarCategoria();
			break;
		}
		case (2) :
		{
			system("cls");
			listarGeral();
			break;
		}
		case (3) :
		{
			system("cls");
			entradaProd();
			break;
		}
		case (4) :
		{
			system("cls");
			saidaProd();
			break;
		}
		case(0) :
		{
			break;
		}
		default:
		{
			printf("**Valores Invalidos**\n");
			getchar();
			break;
		}

		}
	}
}

int menuCadastrarProduto(){

	int continua = 1;
	while (continua)
	{

		system("cls");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("############################ Cadastro de Produto ##############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");

		//############################## ALOCANDO MEM�RIA##############################################
		if (idProduto == 0)
		{
			prod = (struct Produtos *)malloc(sizeof(struct Produtos));

		}
		else if (idProduto >= 1)
		{
			prod = (struct Produtos *)realloc(prod, (idProduto + 1)*sizeof(struct Produtos));
		}
		//############################################################################################
		printf("\n****0- Para Cancelar****\n");
		printf("\n*** Id Produto: %d ***\n", idProduto + 1);
		printf("Nome do Prod.: ");
		fflush(stdin);
		fgets(prod[idProduto].nomeProduto, 100, stdin);
		if (prod[idProduto].nomeProduto[0] == '0') return 0;
		convertToUpper(prod[idProduto].nomeProduto);/*Fun��o Criada para Converter String p/ UpperCase*/
		printf("\nNome do Fornecedor/Marca: ");
		fflush(stdin);
		fgets(prod[idProduto].fornecedor, 100, stdin);
		if (prod[idProduto].fornecedor[0] == '0') return 0;
		convertToUpper(prod[idProduto].fornecedor);
		printf("\nValor de Tabela: R$");
		scanf_s("%f", &prod[idProduto].valor);
		if (prod[idProduto].valor == 0) return 0;
		printf("\nQndt Produtos: ");
		scanf_s("%d", &prod[idProduto].qntProduto);
		if (prod[idProduto].qntProduto == 0)  return 0;
		printf("Categoria do Produto: \n1-Combustivel\n2-Bebida\n3-Alimentos\n4-Diversos\n");
		scanf_s("%d", &prod[idProduto].categoria);
		if (prod[idProduto].categoria == 0) return 0;
		if (validarNomePrd(prod[idProduto].nomeProduto) && validarNomePrd(prod[idProduto].fornecedor) && (prod[idProduto].valor > 0) && (prod[idProduto].qntProduto >= 0) && (validaCat(prod[idProduto].categoria)))
		{
			prod[idProduto].id = idProduto + 1;
			printf("\nId: %d\n***Cadastro Concluido***\n\n", prod[idProduto].id);
			getchar();
			idProduto++;
		}
		else
		{
			/*Mensagem pra invalidar cadastro*/
			printf("**Cadastro nao concluido**\n");
		}
		printf("Press: Qualquer Tecla - Cadastrar/Recadastrar Produto\n");
		printf("Press: 0 - Retornar ao Menu de Produtos\n");
		scanf_s("%d", &continua);
		if (continua == 0) return 0;

	}
	return 1;

}

int menuAlterarValorProduto()
{

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
		if (listarCategoria() == 0) return 0;
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);
		if (codProd > 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			//printf("Id do Produto: %d\n", prod[i].id);
			//printf("Fornecedor: %s", prod[i].fornecedor);
			printf("Valor Cadastrado: R$%.2f\n", prod[codProd].valor);

			printf("Insira novo preco: R$");
			scanf_s("%f", &newValue);
			if (newValue > 0)
			{
				char yn;
				printf("\nConfirma alteracao de: R$%.2f para: R$%.2f ao Produto (Y/N)\n", prod[codProd].valor, newValue);
				getchar();
				scanf_s("%c", &yn);

				yn = toupper(yn);
				if (yn == 'Y')
				{
					prod[codProd].valor = newValue;
					printf("\nValor Atual: R$%.2f\n\n** Alteracao de Confirmada **", prod[codProd].valor);
					getchar();
					getchar();
				}
				else
				{
					system("cls");
					printf("**Alteracao Cancelada**");
					getchar();
					getchar();
				}

			}
		}
		else
		{
			printf("\n*** Id Invalido ***\n");
			getchar();
			getchar();
			getchar();
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

void menuAlterarTaxa()
{
	float auxTaxa;
	char yn;
	system("cls");
	printf("###############################################################################\n");
	printf("#                                                                             #\n");
	printf("######################## Alterar taxa de lucro ################################\n");
	printf("#                                                                             #\n");
	printf("###############################################################################\n");
	if (lucroProd == 0)
	{

		printf("\n**Taxa nao cadastrada**\n\nDeseja Cadastrar Taxa de Lucro? (Y/N)\n");
		getchar();
		scanf_s("%c", &yn);

		yn = toupper(yn);
		if (yn == 'Y')
		{
			printf("Insira o percentual da taxa: (Ex. 2.2%%): ");
			scanf_s("%f", &auxTaxa);
			if (auxTaxa > 0)
			{
				printf("Confirma inclusao de: %.2f%% de taxa (Y/N)\n", auxTaxa);
				getchar();
				scanf_s("%c", &yn);
				yn = toupper(yn);

				if (yn == 'Y')
				{
					lucroProd = auxTaxa;
					system("cls");
					printf("**Inclusao Confirmada: %.2f%% de Taxa**\n", lucroProd);
					getchar();
					getchar();
				}
				else
				{
					system("cls");
					printf("**Inclusao Cancelada**");
					getchar();
					getchar();
				}
			}
		}
		else
		{
			system("cls");
			printf("**Inclusao Cancelada**");
			getchar();
			getchar();
		}
	}
	else
	{
		printf("\nValor da Taxa atual: %.2f%%\nDeseja alterar valor atual? (Y/N)\n", lucroProd);
		getchar();
		scanf_s("%c", &yn);
		yn = toupper(yn);

		if (yn == 'Y')
		{
			printf("Insira novo valor de taxa: (2.2%%): ");
			scanf_s("%f", &auxTaxa);
			if (auxTaxa > 0)
			{
				printf("Confirma alteracao de: %.2f%% para: %.2f%% da taxa? (Y/N)\n", lucroProd, auxTaxa);
				getchar();
				scanf_s("%c", &yn);
				yn = toupper(yn);

				if (yn == 'Y')
				{
					lucroProd = auxTaxa;
					system("cls");
					printf("**Alteracao Confirmada: %.2f%% de Taxa**", lucroProd);
					getchar();
					getchar();
				}
				else
				{
					system("cls");
					printf("**Alteracao Cancelada**");
					getchar();
					getchar();
				}
			}
		}
		else
		{
			system("cls");
			printf("**Alteracao Cancelada**");
			getchar();
			getchar();
		}
	}

}


int listarCategoria(){

	int i, cat;
	if (idProduto >= 1)
	{

		printf("Insera o Id da Categoria:\n1-Combustivel\n2-Bebida\n3-Alimentos\n4-Diversos\n");
		scanf_s("%d", &cat);
		if (cat > 0 && cat < 5)
		{

			system("cls");
			for (i = 0; i < idProduto; i++)
			{
				if (prod[i].categoria == cat)
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
			}
			getchar();
			getchar();
		}
		else
		{
			printf("\n*** Categoria Invalida ***\n");
			getchar();
			return 0;
		}

	}
	else
	{
		printf("**\n\nNenhum produto cadastrado**\n\n");
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
		printf("\n\n**Nenhum produto cadastro**\n\n");
		char yn;
		printf("\nDeseja Cadastrar Produtos? (Y/N)\n");
		getchar();
		scanf_s("%c", &yn);

		yn = toupper(yn);
		if (yn == 'Y')
		{
			if (menuCadastrarProduto() == 0) return 0;
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
		if (listarCategoria() == 0) return 0;
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);
		if (codProd >= 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			//printf("Id do Produto: %d\n", prod[i].id);
			//printf("Fornecedor: %s", prod[i].fornecedor);
			printf("Qntd Disponivel: %d\n", prod[codProd].qntProduto);

			printf("Insira qntd Entrada: ");
			scanf_s("%d", &qnt);
			if (qnt > 0)
			{
				char yn;
				printf("\nConfirma entrada de: %d ao Produto (Y/N)\n", qnt);
				getchar();
				scanf_s("%c", &yn);

				yn = toupper(yn);
				if (yn == 'Y')
				{
					prod[codProd].qntProduto += qnt;
					printf("\nValor Atual: %d\n\n** Inclusao de Confirmada ** ", prod[codProd].qntProduto);
					getchar();
					getchar();
				}
				else
				{
					system("cls");
					printf("**Inclusao Cancelada**");
					getchar();
					getchar();
				}

			}
		}
		else
		{
			printf("\n*** Id Invalido ***\n");
			getchar();
			getchar();
			getchar();
		}
	}
	else
	{
		printf("\n\n**Nenhum produto cadastro**\n\n");
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
int saidaProd(){


	int codProd, qnt;
	if (idProduto >= 1)
	{
		printf("#################### ENTRADA DE PRODUTOS ####################\n");
		if (listarCategoria() == 0) return 0;
		printf("\n\nInsira o Id do Produto: ");
		scanf_s("%d", &codProd);
		if (codProd >= 0 && codProd <= idProduto)
		{
			codProd--;
			printf("Nome do Produto: %s", prod[codProd].nomeProduto);
			//printf("Id do Produto: %d\n", prod[i].id);
			//printf("Fornecedor: %s", prod[i].fornecedor);
			printf("Qntd Disponivel: %d\n", prod[codProd].qntProduto);

			printf("Insira qntd Saida: ");
			scanf_s("%d", &qnt);
			if (qnt > 0)
			{
				char yn;
				printf("\nConfirma saida de: %d ao Produto (Y/N)\n", qnt);
				getchar();
				scanf_s("%c", &yn);

				yn = toupper(yn);
				if (yn == 'Y')
				{
					prod[codProd].qntProduto -= qnt;
					printf("\nValor Atual: %d\n\n** Baixa Confirmada ** ", prod[codProd].qntProduto);
					getchar();
					getchar();
				}
				else
				{
					system("cls");
					printf("**Alteracao Cancelada**");
					getchar();
					getchar();
				}

			}
		}
		else
		{
			printf("\n*** Id Invalido ***\n");
			getchar();
			getchar();
			getchar();
		}
	}
	else
	{
		printf("\n\n**Nenhum produto cadastro**\n\n");
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