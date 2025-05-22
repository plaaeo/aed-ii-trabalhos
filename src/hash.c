#include "hash.h"

/* --- Gerar TAD para a lista encadeada usada na tabela hash --- */

#define LSE(x) lse_hash_##x
typedef hash_valor_t lse_valor_t;
typedef hash_chave_t lse_chave_t;
#define lse_chave(x) hash_chave(x)
#define lse_valor_imprime(x) hash_valor_imprime(x)
#include "lse.c"

/* --- Definição da tabela hash --- */
