/*
 * use_set.c
 *
 *  Created on: 28 abr 2023
 *      Author: jluis
 */
#include <stdio.h>
#include <string.h>
#include "set.h"

#define FIN 0

int comparador_enteros(TYPE a,TYPE b);
void print_entero(TYPE data);

int main()
{
	SET s1 = set_create(comparador_enteros,
			print_entero);

	int arr[] = {500,250,750,125,375,625,875,62,190,310,560,680,813,930,960,30,180,FIN};
	int borrar[] ={500,750,625,310,813,FIN};
	int i;

	for(i=0;arr[i];i++) 
		set_add(s1,&arr[i]);


	printf("Tamaño del conjunto %d\n",set_size(s1));
	set_print(s1);

	for(i=0;borrar[i];i++)
	{
		printf("Presiona enter...");
		getchar();
		printf("Borrando elemento %d\n",borrar[i]);
		set_remove(s1,&borrar[i]);

		printf("Tamaño del conjunto %d\n",set_size(s1));
		set_print(s1);
	}
}

/*
 * Esta función regresa
 * 	Un valor positivo si a es mayor que b
 * 	Un valor negativo si a es menor que b
 * 	0 si a y b son iguales
 */
int comparador_enteros(TYPE a,TYPE b)
{
	int ia = *((int *) a);
	int ib = *((int *) b);
	return ia - ib;
}

void print_entero(TYPE data)
{
	printf("%d\n", *((int *)data));
}
