/*
 * set.c
 *
 *  Created on: 19 abr 2023
 *      Author: jluis
 */

/*
    1. SET_remove(set, dato)
    2. Remover nodo con tree_remove(nodo (raíz), dato, comparador)
        a. Recorrer el árbol hasta encontrar el dato (comparar número
            o desplazarse)
        b. Dato encontrado: este dato será el "root" del nuevo subárbol
        c. Detectar las condiciones
        d. Encontrar el más derecho, izquierdo o nada
        e. Hacer swap del root con el más derecho, izquierdo o nada
    3. Disfrutar
*/
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

//████████████████████████████████████████████████████████

void set_remove(SET set, TYPE e) {
  tree_remove(&set->tree_root, e, set->cf);
  set->size--;
}

void tree_remove(struct STRTNODE **root, TYPE e, COMPAREFUNC cf) {
  // Si el arbol esta vacio entoces no entrará al resto de la función
  if (*root == NULL) {
    return;
  }
  /*
        Utilizando la función comparador, se buscará el elemento
        antes de realizar la función de eliminación, garantizando
        que el elemento existe.
  */
  // Si el elemento es menor, desplazarse hacia la izquierda
  if (cf(e, (*root)->elem) < 0) {
    tree_remove(&(*root)->left, e, cf);
  }

  // Si el elemento es mayor, desplazarse hacia la derecha
  else if (cf(e, (*root)->elem) > 0) {
    tree_remove(&(*root)->right, e, cf);
  }

  /*
      El programa entra a la siguiente condición una vez ya encontró el elemento
      Esto es, la función del comparador regresará 0 por lo que no entrará
      a las condiciones anteriores
  */
  else {
    // Los dos hijos son null por lo tanto es el ultimo y representa una hoja
    if ((*root)->left == NULL && (*root)->right == NULL) {
      free(*root);  // Se libera root
      *root = NULL; // Su dirección pasa a ser NULL
    }
    /*
        Primera condición: Se comprueba si tiene un hijo derecho
        pero no tiene un hijo izquierdo
    */
    else if ((*root)->left == NULL) {
      struct STRTNODE *temp = *root;
      *root = (*root)->right; // La dirección del nodo derecho pasa a ser la del
                              // nodo derecho
      free(temp); // Se libera el nodo del número que se desa eliminar
    }
    /*
    Segunda condición: Se comprueba si tiene un hijo izquierdo
    pero no tiene un hijo derecho
*/
    else if ((*root)->right == NULL) {
      struct STRTNODE *temp = *root;
      *root = (*root)->left;
      free(temp);
    }
    /*
        Tercera condición: El nodo a eliminar tiene dos hijos
        Se realizará una recursión de esta misma función donde se
        elegirá el nodo izquierdo. Al elegir el lado izquierdo, se buscará
        el elemento "más derecho" y, una vez encontrado,
        se realizará un swap de los elementos (El elemento del root por
        el valor encontrado = "más derecho")


    */
    else {
      struct STRTNODE *temp = (*root)->right;
      while (temp->left != NULL)
        temp = temp->left;
      (*root)->elem = temp->elem;
      /*
          Una vez realizado el swap de elementos, se eliminará
      */
      tree_remove(&(*root)->right, temp->elem, cf);
    }
  }
}

//████████████████████████████████████████████████████████

/* Funciones para el manejo de los árboles */

/*
    Funcion de tree_insert que cumple la funcion de insertar elementos al
   arbol, en el que al iniciar el arbol y estar en null, allocamos una raiz de
   memoria dinamica estableciendo las raicez y sus elementos, por otro lado, de
   ya existir algun elemento entonces hacemos comparaciones dentro del arbol
   donde iremos haciendo comparaciones con el COMPAREFUNC restando el primer
   valor con el segundo y de ser menor a 0, entonces el elemento a insertar sera
   de izquierda, donde el mismo principio aplica al insertar de lado derecho
   pero en este caso a ser mayor a 0.
*/
int tree_insert(struct STRTNODE **root, TYPE e, COMPAREFUNC cf) {
  int inserted = 0;
  if (*root == NULL) {
    *root = malloc(sizeof(struct STRTNODE));
    (*root)->elem = e;
    (*root)->left = NULL;
    (*root)->right = NULL;
    inserted = 1;
  } else if (cf(e, (*root)->elem) < 0) // e < (*root)->elem
    inserted = tree_insert(&(*root)->left, e, cf);
  else if (cf(e, (*root)->elem) > 0) // e > (*root)->elem
    inserted = tree_insert(&(*root)->right, e, cf);

  return inserted;
}

/*
    tree_print es tal funcion que de manera recursiva vamos subiendo
   nieveles hasta que sea diferente de null para llegar hasta el punto deseado
   de lado derecho e ir imprimiento uno por uno de los nieveles.
*/

void tree_print(int level, struct STRTNODE *root, PRINTFUNC pf) {
  int i;
  if (root != NULL) {
    tree_print(level + 1, root->right, pf);

    for (i = 0; i < level; i++)
      printf("\t");
    pf(root->elem);

    tree_print(level + 1, root->left, pf);
  }
}

/*
        set_create es la funcion SET que basicamente inicializa el arbol binario
        en un estado vacio alocando su memoria. Al igual que, tambien se aloca
        la memoria para los comparadores y su tamaño.
*/

SET set_create(COMPAREFUNC cf, PRINTFUNC pf) {
  SET new_set = malloc(sizeof(struct STRSET));
  new_set->tree_root = NULL; // Inicia con el árbol vacío
  new_set->size = 0;
  new_set->cf = cf;
  new_set->pf = pf;

  return new_set;
}

/*
        set_add solo añade un set al arbol.
*/

void set_add(SET set, TYPE e) {
  if (tree_insert(&set->tree_root, e, set->cf))
    set->size = set->size + 1;
}

/*
        set_size solo regresamos el tamñano del set.
*/
int set_size(SET set) { return set->size; }

/*
        set_print imprimimos de manera recursiva el arbol del set
        desde el root.
*/
void set_print(SET set) { tree_print(0, set->tree_root, set->pf); }
