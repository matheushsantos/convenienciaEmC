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
void gravarDados();
void restaurarSessao();
int varIntGlobais(char * nomeArquivo);


int main()
{

	setlocale(LC_CTYPE, "Portuguese");
	 restaurarSessao();
	char menuPrincipal[100];
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
		leituraSwitch(menuPrincipal);

		switch (menuPrincipal[0])
		{
		case ('1') :
		{
			funcaoVenda();
			break;
		}
		case ('2') :
		{
			funcaoClientes();
			break;
		}
		case ('3') :
		{
			funcaoProduto();
			break;
		}
		case ('4') :
		{
			FuncaoCaixa();
			break;
		}
		case ('0') :
		{
			//gravarDados();
			system("cls");
			printf("Encerrando: \n");
			printf("3");
			_sleep(1000);
			system("cls");
			printf("Encerrando: \n");
			printf("2");
			_sleep(1000);
			system("cls");
			printf("Encerrando: \n");
			printf("1");
			_sleep(1000);
			exit(0);
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


void gravarDados(){

	if (confirmacao("Deseja Gravar Operações dessa sessão?(Y/N)", 'Y', comMensagemDeErro, 0))
	{
		

		if (diaAtual >= 0)
		{
			salvaCaixaArq();
		}
		/*if (ClientesCadastrados > 0)
		{
			arq = fopen("clientes.bin", "wb");
			if (arq != NULL)
			{
				fwrite(&Cli[0], sizeof(struct Clientes), ClientesCadastrados + 1, arq);
				fclose(arq);
			}
			else
			{
				error("Erro ao salvar dados");
			}
		}*/
			if (escreveVarGlobais("numCli.txt", ClientesCadastrados))
				{
					system("cls");
					error("Dados Salvos com Sucesso");
				}
	
		
	}
	else
	{
		error("Dados não armazenados, sessão não salva");
	}


}


void restaurarSessao(){
	FILE * arq;
	float aux = 0;
	if (confirmacao("Deseja restaurar sessão anterior? (Y/N)\nCaso não queira restaurar todos os dados salvos até então serão perdidos.", 'Y', comMensagemDeErro, 0)){
	
		diaAtual = varIntGlobais("idCaixa.txt");
		ClientesCadastrados = varIntGlobais("numCli.txt");
		idProduto = varIntGlobais("idProduto.txt");
		lucroProd = varIntGlobaisFloat("txLucro.txt");
		
		importaDescontosCli();

		arq = fopen("caixa.bin", "rb");
		if (arq != NULL){
			if (diaAtual == -1)
			{
				diaAtual++;
				caixa = (struct Caixa *)malloc(sizeof(struct Caixa));
				caixa[diaAtual].aberto = false;
			}
			else
			{
				caixa = (struct Caixa *)malloc(sizeof(struct Caixa));
				caixa = (struct Caixa *)realloc(caixa, (diaAtual + 1)*sizeof(struct Caixa));
				fread(&caixa[0], sizeof(struct Caixa), diaAtual + 1, arq);
				fcloseall;
			}
		}
		else
		{
			arq = fopen("caixa.bin", "wb");
			fcloseall;
			error("Problema ao ler arquivo, no qual foi criado um com o mesmo nome zerado.");
		}

		arq = fopen("clientes.bin", "rb");
		if (arq != NULL)
		{
			if (ClientesCadastrados == 0)
			{
				//error("clientes 0");
				Cli = (struct Clientes *)malloc(sizeof(struct Clientes));
			}
			if (ClientesCadastrados >= 1)
			{
				Cli = (struct Clientes *)malloc(sizeof(struct Clientes));
				Cli = (struct Clientes *)realloc(Cli, (ClientesCadastrados)*sizeof(struct Clientes));
				arq = fopen("clientes.bin", "rb");
				fread(&Cli[0], sizeof(struct Clientes), ClientesCadastrados, arq);
				
			}
			fcloseall;
		}
		else
		{
			arq = fopen("clientes.bin", "wb");
			fcloseall;
			error("Problema ao ler arquivo, no qual foi criado um com o mesmo nome zerado.");
		}

		arq = fopen("produtos.bin", "rb");
		if (arq != NULL)
		{
			if (idProduto == 0)
			{
				//error("produto 0");
				prod = (struct Produtos *)malloc(sizeof(struct Produtos));
			}
			else
			{
				//error("produto mais de 0");
				prod = (struct Produtos *)malloc(sizeof(struct Produtos));
				prod = (struct Produtos *)realloc(prod, (idProduto)*sizeof(struct Produtos));
				arq = fopen("produtos.bin", "rb");
				fread(&prod[0], sizeof(struct Produtos), idProduto, arq);
			}
		
			fcloseall;
		}
		else
		{
		//	arq = fopen("produtos.bin", "wb");
			//fcloseall;
			error("Problema ao ler arquivo, no qual foi criado um com o mesmo nome zerado.");
		}
		sessaoArquivo = true;
		
	}
	else if (confirmacao("Você confirma deletar todos os dados? (Y/N)",'Y',comMensagemDeErro, 0))
	{
		truncaArquivos();

		system("cls");
		error("TODOS OS DADOS FORAM EXCLUÍDOS COM SUCESSO");
	}

}