#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <locale.h>
#include <stdbool.h>

/*Lib Criadas para auxilio de chamadas das funções*/
#include "Funcoes.h"
#include "Produtos.h"
#include "Venda.h"
#include "Clientes.h"
#include "Caixa.h"

//#include "Include.cpp"

void funcaoProduto();


int main()
{

	setlocale(LC_ALL, "Portuguese");

	int menuPrincipal;
	while (true)
	{
		printf("\n");
		system("cls");
		printf("   #                         #####                           ##   ##   #   ##  \n");
		printf("   #            #             #   #            #            #  # #  # ##  #  # \n");
		printf("  # #   ## ##  ###   ###      #   #  ###   ## ###   ###        # #  #  #  #    \n");
		printf("  ###    #  #   #   #   #     ####  #   # #    #   #   #      #  #  #  #  ###  \n");
		printf(" #   #   #  #   #   #   #     #     #   #  #   #   #   #     #   #  #  #  #  # \n");
		printf(" #   #   #  #   #   #   #     #     #   #   #  #   #   #    #    #  #  #  #  # \n");
		printf("### ###   ####   ##  ###     ###     ###  ##    ##  ###     ####  ##  ###  ##  \n");
		printf("\n\n");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("#####################   Insira a opcao desejada    ############################\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		printf("#                                                                             #\n");
		printf("#          1 - Para Vendas                                                    #\n");
		printf("#          2 - Para Clientes                                                  #\n");
		printf("#          3 - Para Produtos                                                  #\n");
		printf("#          4 - Para Caixa                                                     #\n");
		printf("#          0 - Para Sair                                                      #\n");
		printf("#                                                                             #\n");
		printf("###############################################################################\n");
		scanf_s("%d", &menuPrincipal);

		switch (menuPrincipal)
		{
		case (1) :
		{
			funcaoVenda();
			break;
		}
		case (2) :
		{
			MenuCadastroCliente();
			break;
		}
		case (3) :
		{
			funcaoProduto();
			break;
		}
		case (4) :
		{
			FuncaoCaixa();
			break;
		}
		case (0) :
		{
			exit(0);
			break;
		}
		default:
		{

			system("cls");
			printf("**Valor Invalido**");
			getchar();
			getchar();
			break;
		}
		}
	}
}