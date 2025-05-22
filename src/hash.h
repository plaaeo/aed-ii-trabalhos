#pragma once

/* --- Valores e chaves --- */
#ifndef HASH_CUSTOM

/// Define o tipo armazenado na tabela.
typedef int hash_valor_t;

/// Define o tipo da chave usada para busca por itens na tabela.
typedef int hash_chave_t;

/// Retorna um 'hash_chave_t' usado para comparar objetos do tipo 'hash_valor_t'
#define hash_chave(x) x

/// Imprime um objeto do tipo 'hash_valor_t'
#define hash_valor_imprime(x) printf("%d", x)

#endif
/* --- Definição da hash --- */
