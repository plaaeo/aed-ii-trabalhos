#pragma once

typedef struct avl_t avl_t;

int *avl_buscar(avl_t** avl, int n);

void avl_inserir(avl_t** avl, int n);

int avl_remover(avl_t** avl, int n);

int avl_altura(avl_t* avl);
