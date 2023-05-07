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
#include <stdlib.h>
#include <stdio.h>
#include "set.h"

//████████████████████████████████████████████████████████


void set_remove(SET set, TYPE e)
{
    tree_remove(&set->tree_root, e, set->cf);
    set->size--;
}

void tree_remove(struct STRTNODE **root, TYPE e, COMPAREFUNC cf)
{
    // Si el arbol esta vacio
    if (*root == NULL)
    {
        return;
    }

    // Linea izquierdo
    if (cf(e, (*root)->elem) < 0)
    {
        tree_remove(&(*root)->left, e, cf);
    }

    // Linea derecha
    else if (cf(e, (*root)->elem) > 0)
    {
        tree_remove(&(*root)->right, e, cf);
    }

    else
    {
        // Los dos hijos son null por lo tanto es el ultimo
        if ((*root)->left == NULL && (*root)->right == NULL)
        {
            free(*root);
            *root = NULL;
        }
        // Solo tiene un hijo
        // Tiene hijo derecho
        else if ((*root)->left == NULL)
        {
            struct STRTNODE *temp = *root;
            *root = (*root)->right;
            free(temp);
        }
        // Tiene hijo izquierdo
        else if ((*root)->right == NULL)
        {
            struct STRTNODE *temp = *root;
            *root = (*root)->left;
            free(temp);
        }
        // Tiene los dos hijos por no haber llegado a los anteriores
        else
        {
            struct STRTNODE *temp = (*root)->left;
            while (temp->right != NULL)
                temp = temp->right;
            (*root)->elem = temp->elem;
            tree_remove(&(*root)->left, temp->elem, cf);
        }
    }
}


//████████████████████████████████████████████████████████

/* Funciones para el manejo de los árboles */

int tree_insert(struct STRTNODE **root,TYPE e,COMPAREFUNC cf)
{
    int inserted = 0;
    if(*root==NULL)
    {
        *root = malloc(sizeof(struct STRTNODE));
        (*root)->elem = e;
        (*root)->left = NULL;
        (*root)->right = NULL;
        inserted = 1;
    }
    else if(cf(e,(*root)->elem)<0)  // e < (*root)->elem
        inserted = tree_insert(&(*root)->left,e,cf);
    else if(cf(e,(*root)->elem)>0)  // e > (*root)->elem
        inserted = tree_insert(&(*root)->right,e,cf);

    return inserted;
}


void tree_print(int level,struct STRTNODE *root,PRINTFUNC pf)
{
    int i;
    if(root!=NULL)
    {
        tree_print(level+1,root->right,pf);

        for(i=0;i<level;i++)
            printf("\t");
        pf(root->elem);

        tree_print(level+1,root->left,pf);
    }
}


SET set_create(COMPAREFUNC cf,PRINTFUNC pf)
{
    SET new_set = malloc(sizeof(struct STRSET));
    new_set->tree_root = NULL;	//Inicia con el árbol vacío
    new_set->size = 0;
    new_set->cf = cf;
    new_set->pf = pf;

    return new_set;
}

void set_add(SET set,TYPE e)
{
    if(tree_insert(&set->tree_root,e,set->cf))
        set->size = set->size + 1;
}

int set_size(SET set)
{
    return set->size;
}

void set_print(SET set)
{
    tree_print(0,set->tree_root,set->pf);
}
