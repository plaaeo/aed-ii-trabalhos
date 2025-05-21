#pragma once
#include <stdbool.h>

/* --- Valores e chaves --- */

/// Define o tipo armazenado na árvore.
typedef int abp_valor_t;

/// Define o tipo da chave usada para busca por itens na árvore.
typedef int abp_chave_t;

/// Retorna um 'abp_chave_t' usado para comparar objetos do tipo 'abp_valor_t'
#define abp_chave(x) x

/// Imprime um objeto do tipo 'abp_valor_t'
#define abp_valor_imprime(x) printf("%d", x)

/* --- Definição da AVL --- */

typedef struct abp_t abp_t;

// cria uma abp usando um vetor ordenado
abp_t* abp_criar_por_vetor(abp_valor_t *vetor, int tam);

// insere um valor na árvore
abp_t* abp_inserir(abp_t* raiz, abp_valor_t valor);

// busca um valor na árvore
bool abp_buscar(abp_t* raiz, abp_chave_t chave, abp_valor_t *valor);

// remove um valor da arvore
abp_t* abp_remover(abp_t* raiz, abp_chave_t chave, abp_valor_t *valor);

// Pré fixado
void abp_pre_ordem(abp_t* raiz);

// fixado
void abp_em_ordem(abp_t* raiz);

// pos fixado
void abp_pos_ordem(abp_t* raiz);

// calcula a altura da árvore
int abp_altura(abp_t* raiz);

// libera a árvore
void abp_liberar(abp_t *raiz);
