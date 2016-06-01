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

bool validarNomePrd(char * nome){

	int numeros = 1, i;
	if (strlen(nome) > 100 || strlen(nome) < 2)
	{
		printf("\n**Numero de Letras Invalido**\n");
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
		printf("\n**O campo n�o deve conter somente numeros**\n");
		return false;
	}
	return true;
}

bool validaCat(int produto){

	if ((produto == combustivel) || (produto == bebida) || (produto == comida) || (produto == diversos))
	{
		return true;
	}

	return false;
}

void convertToUpper(char * string){
	int i;
	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] == -121)
		{
			string[i] = '�';
		}
		else 
		{
			string[i] = toupper(string[i]);
		}
	}
}

int validaNomeClie(char* strNomeCli){
	int i = 0, aux = 0;
	if (strlen(strNomeCli)-1 > 100 || strlen(strNomeCli)-1 <= 2)
	{
		printf("\n***O campo: NOME � obrigat�rio possuir pelo menos 2 caracteres***\n");
		return 0;
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
		printf("\n***O campo: NOME n�o deve possuir somente espa�os em branco***\n");
		return 0;
	}
	return 1;
}

int validaEmail(char* email)
{
	int i = 0, numValido = 0, at = -50, dot = -50;
	if (strlen(email) > 50 || strlen(email) <= 5)
	{
		return 0;
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
				printf("\n***O campo: EMAIL � obrigat�rio possuir @ e . com espa�o minimo de 2 caracteres entre um e outro***\n");
				return 0;
			}
			numValido++;
		}
	}
	if ((numValido >= 2) && (dot > at) )
	{
		
		return 1;

	}
	printf("\n***O campo: EMAIL � obrigat�rio possuir @ e . ***\n");
	return 0;
	
}

int validaCpfCnpj(char* cpf)
{
	int i = 0;

	if ((strlen(cpf) - 1 == 11) || (strlen(cpf) - 1 == 14))
	{
		//Condi��o simples
	}
	else
	{
		printf("\n***O campo: CPF/CNPJ � obrigat�rio possuir 11 ou 14 caracteres***\n");
		return 0;
	}

	for (i = 0; i < strlen(cpf); i++)
	{
		if (isalpha(cpf[i]))
		{
			printf("\n***O campo: CPF � obrigat�rio possuir somente n�meros***\n");
			return 0;
		}
	}
	return 1;
}

int validaTel(char* tel)
{
	int i = 0;

	if (strlen(tel)-1 < 8 )
	{
		printf("\n***O campo: TEL. � obrigat�rio possuir pelo menos 8 digitos***\n");
		return 0;
	}
	else if (strlen(tel)-1 > 12)
	{
		printf("\n***O campo: TEL. � obrigat�rio possuir no m�ximo 12 digitos***\n");
		return 0;
	}

	for (i = 0; i < strlen(tel); i++)
	{
		if (isalpha(tel[i]))
		{
			printf("\n***O campo: TEL. � obrigat�rio possuir somente n�meros***\n");
			return 0;
		}
	}
	return 1;
}



#endif