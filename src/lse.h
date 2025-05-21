#pragma once
#include <stdbool.h>

/* --- Valores e chaves --- */

/// Define o tipo armazenado na lista encadeada.
typedef int lse_valor_t;

/// Define o tipo da chave usada para busca por itens na lista encadeada.
typedef int lse_chave_t;

/// Retorna um 'lse_chave_t' usado para comparar objetos do tipo 'lse_valor_t'
#define lse_chave(x) x

/// Imprime um objeto do tipo 'lse_valor_t'
#define lse_valor_imprime(x) printf("%d", x)

/* --- Definição da lista encadeada --- */

typedef struct lse_t lse_t;

/// Cria uma lista encadeada vazia.
lse_t *lse_criar();

/// Esvazia e libera a memória de uma lista encadeada.
void lse_liberar(lse_t *lista);

/// Insere um ítem no início da lista encadeada.
bool lse_inserir_inicio(lse_t *lista, lse_valor_t valor);

/// Insere um ítem no fim da lista encadeada.
bool lse_inserir_final(lse_t *lista, lse_valor_t valor);

/// Imprime os itens de uma lista encadeada em um determinado período.
void lse_imprimir(const lse_t *lista, int inicio, int fim);

/// Busca um item na lista encadeada sequencialmente.
/// Caso o valor seja encontrado, o ponteiro '*valor' é atualizado.
bool lse_busca_sequencial(const lse_t *lista, lse_chave_t chave, lse_valor_t *valor);

/// Acessa um item na lista encadeada dado um índice.
/// Caso o indice exista, o ponteiro `valor` é atualizado e a função retorna
/// `true`.
bool lse_acessar(const lse_t *lista, int indice, lse_valor_t *valor);
