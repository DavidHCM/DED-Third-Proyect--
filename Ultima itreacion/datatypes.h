/*
 * datatypes.h
 *
 *  Created on: 15 mar 2023
 *      Author: jluis
 */

#ifndef DATATYPES_H_

#include <stdlib.h>

typedef void * TYPE;
typedef int BOOL;
typedef char * STRING;

TYPE int_create(int i);
TYPE float_create(float f);
TYPE double_create(int d);
TYPE char_create(char c);
TYPE string_create(STRING s);

char char_val(TYPE *e);
float float_val(TYPE *e);
double double_val(TYPE *e);
int int_val(TYPE *e);

typedef int (*COMPAREFUNC)(TYPE,TYPE);
typedef void (*PRINTFUNC)(TYPE);

#define DATATYPES_H_



#endif /* DATATYPES_H_ */
