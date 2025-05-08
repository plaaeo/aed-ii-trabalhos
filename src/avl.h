#pragma once

typedef struct avl_t avl_t;

// Insere um novo elemento numa árvore AVL,
// retornando a nova raiz da árvore especificada.
// Caso tente-se inserir uma árvore nula, será
// retornada uma nova árvore com 'n' na raiz.
avl_t* avl_inserir(avl_t* avl, int n);

// Busca 'n' em uma árvore AVL.
// Retorna um ponteiro para o dado encontrado,
// ou NULL se o dado não for encontrado.
int *avl_buscar(avl_t* avl, int n);

// Libera a árvore AVL e todos seus nós
// recursivamente.
void avl_liberar(avl_t* avl);

// Retorna a altura da árvore AVL.
int avl_altura(avl_t* avl);

void avl_em_ordem(avl_t *avl);
