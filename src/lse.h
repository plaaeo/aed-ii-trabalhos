#pragma once
#include <stdbool.h>

#include "vetor.h"

/// TAD para um nó da lista encadeada.
typedef struct lse_no_t lse_no_t;

/// TAD para uma lista encadeada.
typedef struct lse_t lse_t;

/// Cria uma lista encadeada e preenche-a com valores aleatorios.
lse_t *lse_criar_aleatorio(int tam);

/// Esvazia e libera a memória de uma lista encadeada.
void lse_liberar(lse_t *lista);

/// Imprime os itens de uma lista encadeada em um determinado período.
void lse_imprimir(const lse_t *lista, int inicio, int fim);

/// Busca um item na lista encadeada sequencialmente.
/// Caso o valor seja encontrado, o ponteiro `indice` é atualizado e a função
/// retorna `true`.
bool lse_busca_sequencial(const lse_t *lista, int valor, int *indice);

/// Acessa um item na lista encadeada dado um índice.
/// Caso o indice exista, o ponteiro `valor` é atualizado e a função retorna
/// `true`.
bool lse_acessar(const lse_t *lista, int indice, int *valor);