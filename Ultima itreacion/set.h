/*
 * set.h
 *
 *  Created on: 19 abr 2023
 *      Author: jluis
 */

#ifndef SET_H_

#include "datatypes.h"

struct STRTNODE {
  TYPE elem;
  struct STRTNODE *left;
  struct STRTNODE *right;
};

struct STRSET {
  struct STRTNODE *tree_root;
  int size;
  COMPAREFUNC cf;
  PRINTFUNC pf;
};

typedef struct STRSET *SET;

void set_remove(SET set, TYPE e);
void tree_remove(struct STRTNODE **root, TYPE e, COMPAREFUNC cf);
SET set_create(COMPAREFUNC cf, PRINTFUNC pf);
void set_add(SET set, TYPE e);
int set_size(SET set);
void set_print(SET set);

#define SET_H_

#endif /* SET_H_ */
