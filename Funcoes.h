#ifndef _FUNCOES_H_
#define _FUNCOES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


/*Tipo/Categoria de Produtos*/
#define combustivel 1 
#define bebida 2
#define comida 3
#define diversos 4

#define comMensagemDeErro true
#define semMensagemDeErro false

bool leituraSwitch(char * string);

/*Variaves globais*/
float lucroProd = 0;

void stringSemQuebraLinha(char * string)
{
	strtok(string, "\n");
}
void error(char * mensagem)
{
	stringSemQuebraLinha(mensagem);
	printf("\n***%s***\n", mensagem);
	system("pause");
}


bool leituraSwitch(char * string)
{
	scanf("%s", string);
	if (strlen(string) > 1)
	{
		string[0] = 'A';
		return false;
	}
	return true;
}

bool confirmacao(char * msg, char letra, bool mensagem, bool scan)
{
	if (scan) getchar();
	
	char aux[100] ;
	if (mensagem)
	{
		//stringSemQuebraLinha(msg);
		printf("\n%s\n", msg);
	}
	scanf("%s", &aux);

	aux[0] = toupper(aux[0]);
	letra = toupper(letra);

	if (strlen(aux) > 1)
	{
		if (mensagem)
		{
			error("Valor inválido, favor inserir somente um caracter");
		}
		fflush(stdin);
		return false;
	}

	if (aux[0] == letra)
	{
		return true;
	}
	else
	{
		fflush(stdin);
		return false;
	}
}





bool validarNomePrd(char * nome, bool mensagem){

	int numeros = 1, i;
	if (strlen(nome) > 100 || strlen(nome) < 3)
	{
		if (mensagem)
		{
			error("Numero de Letras Invalido");
		}
		return false;
	}

	for (i = 0; i < strlen(nome); i++)
	{
		if (isdigit(nome[i]))
		{
			numeros++;
		}
	}
	if (numeros == strlen(nome))
	{
		if (mensagem)
		{
			error("O campo não deve conter somente numeros");
		}
		return false;
	}
	return true;
}

int validaCat(char * produto, bool mensagem){

	if (strlen(produto) > 1)
	{
		if (mensagem) error("Categoria Inválida");
		return 0;
	}

	if ((produto[0] == '1'))		return 1;
	else if ((produto[0] == '2'))	return 2;
	else if ((produto[0] == '3'))	return 3;
	else if ((produto[0] == '4'))	return 4;
	else if ((produto[0] == '0'))	return 0; //OPÇÃO DE SAIR-CANCELAR 
	else if (mensagem)				error("Categoria Inválida");
	return 0;
}

void convertToUpper(char * string){
	int i;
	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] == -121)
		{
			string[i] = 'Ç';
		}
		else 
		{
		string[i] = toupper(string[i]);
		}
	}
}

bool validaNomeClie(char* strNomeCli, bool mensagem){
	int i = 0, aux = 0;
	if (strlen(strNomeCli)-1 > 100 || strlen(strNomeCli)-1 <= 2)
	{
		if (mensagem)
		{
			error("O campo: NOME é obrigatório possuir pelo menos 2 caracteres");
			return false;
		}
	}
	for (i = 0; i < strlen(strNomeCli); i++)
	{
		if (isspace(strNomeCli[i]))
		{
			aux++;
		}
	}
	if ((aux + 2) >= strlen(strNomeCli))
	{
		if (mensagem)
		{
			error("O campo: NOME não deve possuir somente espaços em branco");
			return false;
		}
	}
	return true;
}

bool validaEmail(char* email, bool mensagem)
{
	int i = 0, numValido = 0, at = -50, dot = -50;
	if (strlen(email) > 50 || strlen(email) < 5)
	{
		if (mensagem)
		{
			error("Campo e-mail deve conter entre 5 e 50 caracteres");
		}
		return false;
	}
	for (i = 0; i < strlen(email); i++)
	{
		if (email[i] == '@')
		{
			at = i;
			numValido++;
		}
		
		else if (email[i] == '.')
		{
			dot = i;
			if ((dot - at) <= 2)
			{
				if (mensagem)
				{
					error("O campo: EMAIL é obrigatório possuir @ e . com espaço minimo de 2 caracteres entre um e outro");
				}
				return false;
			}
			numValido++;
		}
	}
	if ((numValido >= 2) && (dot > at) )
	{
		
		return true;

	}
	if (mensagem)
	{
		error("O campo: EMAIL é obrigatório possuir @ e . ");
	}
	return false;
	
}

bool validaCpfCnpj(char* cpf, bool mensagem)
{
	int i = 0;

	if ((strlen(cpf) - 1 == 11) || (strlen(cpf) - 1 == 14))
	{
	}
	else
	{
		if (mensagem)
		{
			printf("Valor do campo : %d", strlen(cpf) );
			error("O campo: CPF/CNPJ é obrigatório possuir 11 ou 14 caracteres");
		}
		return false;
	}

	for (i = 0; i < strlen(cpf); i++)
	{
		if (isalpha(cpf[i]))
		{
			if (mensagem)
			{
				error("O campo: CPF é obrigatório possuir somente números");
			}
			return false;
		}
	}
	return true;
}

bool validaTel(char* tel, bool mensagem)
{
	int i = 0;

	if (strlen(tel)-1 < 8 )
	{
		if (mensagem)
		{
			error("O campo: TEL. é obrigatório possuir pelo menos 8 digitos");
		}
		return false;
	}
	else if (strlen(tel)-1 > 12)
	{
		if (mensagem)
		{
			error("O campo: TEL. é obrigatório possuir no máximo 12 digitos");
		}
		return false;
	}

	for (i = 0; i < strlen(tel); i++)
	{
		if (isalpha(tel[i]))
		{
			if (mensagem)
			{
				error("O campo: TEL. é obrigatório possuir somente números");
			}
			return false;
		}
	}
	return true;
}


bool  menuAlterarTaxa()
{
	float auxTaxa;
	char yn;
	if (lucroProd == 0)
	{

		if (confirmacao("Taxa não cadastrada, deseja cadastrar uma taxa de lucro? (Y/N)", 'Y', comMensagemDeErro, true))
		{
			printf("Insira o percentual da taxa: (Ex. 20,2 = 20,2%%): ");
			scanf_s("%f", &auxTaxa);
			if (auxTaxa > 0)
			{
				printf("Confirma inclusao de: %.2f%% de taxa (Y/N)\n", auxTaxa);
				if (confirmacao("", 'Y', semMensagemDeErro, true))
				{
					lucroProd = auxTaxa / 100;
					return true;
				}
				else
				{
					false;
				}
			}
			else
			{
				fflush(stdin);
				error("Valor do Lucro deve ser maior que zero (0)");
				false;
			}
		}
		else
		{
			false;
		}
	}
	else
	{
		printf("\nValor da Taxa atual: %.2f%%\nDeseja alterar valor atual? (Y/N)\n", lucroProd * 100);
		if (confirmacao("", 'Y', semMensagemDeErro, true))
		{
			printf("Insira novo valor de taxa: (Ex. 2,2 = 2,2%%): ");
			scanf_s("%f", &auxTaxa);
			if (auxTaxa > 0)
			{
				printf("Confirma alteracao de: %.2f%% para: %.2f%% da taxa? (Y/N)\n", lucroProd * 100, auxTaxa);
				if (confirmacao("",'Y', semMensagemDeErro, true))
				{
					lucroProd = auxTaxa/100;				
					return true;
				}
				else
				{
					false;
				}
			}
			else
			{
				fflush(stdin);
				error("Valor do Lucro deve ser maior que zero (0)");
				false;
			}
		}
		else
		{
			false;
		}
	}
	false;
}


#endif