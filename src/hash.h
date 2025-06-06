#pragma once
#include <stdbool.h>

#include "registro.h"

/* --- Valores e chaves --- */
#ifndef HASH_CUSTOM

/// Define o tipo armazenado na tabela.
typedef registro_t hash_valor_t;

/// Define o tipo da chave usada para busca por itens na tabela.
typedef int hash_chave_t;

/// Retorna um 'hash_chave_t' usado para comparar objetos do tipo 'hash_valor_t'
#define hash_chave(x) ((hash_chave_t)((x).matricula_ou_cr))

/// Imprime um objeto do tipo 'hash_valor_t'
#define hash_valor_imprime(x) printf("registro {\n  'matricula_ou_cr': %lf,\n  'posicao': %ld\n};", (x).matricula_ou_cr, (x).posicao)

#endif
/* --- Definição da hash --- */

typedef struct hash_t hash_t;

// Cria uma tabela hash com o tamanho dado.
hash_t *hash_criar(int tam);

// Insere o valor dado na tabela hash.
// Retorna 'true' se ocorrer uma colisão.
bool hash_inserir(hash_t *hash, hash_valor_t valor);

// Busca um elemento na tabela hash por chave.
// Caso o elemento exista na tabela, a função retorna 'true'
// e atualiza o ponteiro 'hash_valor_t'.
bool hash_buscar(hash_t *hash, hash_chave_t chave, hash_valor_t *valor);

// Libera a tabela hash e seus elementos.
void hash_liberar(hash_t *hash);