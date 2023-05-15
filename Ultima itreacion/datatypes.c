/*
 * datatypes.c
 *
 *  Created on: 15 mar 2023
 *      Author: jluis
 */
#include "datatypes.h"

TYPE int_create(int i)
{
	int *new = malloc(sizeof(int));	// Pedir memoria para un entero
	*new = i;						// gaurdar el entero en memoria
	return(new);					// Regresar la dirección del entero
}

TYPE float_create(float f)
{
	float *new = malloc(sizeof(float));
	*new = f;
	return(new);
}

TYPE double_create(int d)
{
	double *new = malloc(sizeof(double));
	*new = d;
	return(new);
}

TYPE char_create(char c)
{
	char *new = malloc(sizeof(char));
	*new = c;
	return(new);
}

TYPE string_create(STRING s)
{
	int strsize=0;
	int i;
	char *new;

	while(s[strsize])
		strsize++;

	new = malloc(strsize);
	for(i=0;i<strsize+1;i++)
		new[i] = s[i];

	return(new);
}

char char_val(TYPE *e)
{
	return(*((char *) e));
}

float float_val(TYPE *e)
{
	return(*((float *) e));
}

double double_val(TYPE *e)
{
	return(*((double *) e));
}

int int_val(TYPE *e)
{
	return(*((int *) e));
}

