#pragma once
#include <stdbool.h>

/* --- Valores e chaves --- */

/// Define o tipo armazenado na árvore.
typedef int avl_valor_t;

/// Define o tipo da chave usada para busca por itens na árvore.
typedef int avl_chave_t;

/// Retorna um 'avl_chave_t' usado para comparar objetos do tipo 'avl_valor_t'
#define avl_chave(x) x

/* --- Definição da AVL --- */

typedef struct avl_t avl_t;

/// Insere um novo elemento numa árvore AVL,
/// retornando a nova raiz da árvore especificada.
/// Caso tente-se inserir uma árvore nula, será
/// retornada uma nova árvore com 'n' na raiz.
avl_t* avl_inserir(avl_t* avl, avl_valor_t n);

/// Busca 'n' em uma árvore AVL.
/// Retorna true se o dado for encontrado, e 
/// armazena o resultado da busca em '*valor'
bool avl_buscar(const avl_t* avl, avl_chave_t n, avl_valor_t *valor);

/// Libera a árvore AVL e todos seus nós
/// recursivamente.
void avl_liberar(avl_t* avl);

/// Retorna a altura da árvore AVL.
int avl_altura(const avl_t* avl);
