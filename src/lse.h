/**
 * lse.h
 *
 * Define uma lista simplesmente encadeada, ou seja, uma lista
 * encadeada onde cada nó tem um ponteiro para o próximo.
 */
#pragma once
#include <stdbool.h>
#include "registro.h"

/* --- Valores e chaves --- */
#ifndef LSE_CUSTOM

/// Define o tipo armazenado na lista encadeada.
typedef registro_t lse_valor_t;

/// Define o tipo da chave usada para busca por itens na lista encadeada.
typedef double lse_chave_t;

/// Retorna um 'lse_chave_t' usado para comparar objetos do tipo 'lse_valor_t'
#define lse_chave(x) ((lse_chave_t)((x).matricula_ou_cr))

/// Imprime um objeto do tipo 'lse_valor_t'
#define lse_valor_imprime(x) printf("%lf", (x).matricula_ou_cr)

#endif
/* --- Definição da lista encadeada --- */

typedef struct lse_t lse_t;

/// Esvazia e libera a memória de uma lista encadeada.
void lse_liberar(lse_t *lista);

/// Insere um ítem no início da lista encadeada. Retorna a nova
/// cabeça da lista encadeada.
lse_t *lse_inserir_inicio(lse_t *lista, lse_valor_t valor);

/// Insere um ítem no fim da lista encadeada. Retorna a nova
/// cabeça da lista encadeada.
lse_t *lse_inserir_fim(lse_t *lista, lse_valor_t valor);

/// Imprime os itens de uma lista encadeada em um determinado período.
void lse_imprimir(const lse_t *lista, int inicio, int fim);

/// Busca um item na lista encadeada sequencialmente.
/// Caso o valor seja encontrado, o ponteiro '*valor' é atualizado.
bool lse_busca_sequencial(const lse_t *lista, lse_chave_t chave,
                           lse_valor_t *valor);

/// Recebe uma lista e retorna o proximo
lse_t* acessar_prox(lse_t* lista);

/// Retorna valor da cabeca
lse_valor_t lse_cabeca(lse_t *lista);
