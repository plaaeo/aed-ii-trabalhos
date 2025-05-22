#pragma once
#include <stdbool.h>

/* --- Valores e chaves --- */
#ifndef LSE
#define LSE(x) lse_##x

/// Define o tipo armazenado na lista encadeada.
typedef int lse_valor_t;

/// Define o tipo da chave usada para busca por itens na lista encadeada.
typedef int lse_chave_t;

/// Retorna um 'lse_chave_t' usado para comparar objetos do tipo 'lse_valor_t'
#define lse_chave(x) x

/// Imprime um objeto do tipo 'lse_valor_t'
#define lse_valor_imprime(x) printf("%d", x)
#endif

/* --- Substituição de nomes --- */

#define lse_t LSE(t)
#define lse_criar LSE(criar)
#define lse_liberar LSE(liberar)
#define lse_inserir_inicio LSE(inserir_inicio)
#define lse_inserir_fim LSE(inserir_fim)
#define lse_imprimir LSE(imprimir)
#define lse_busca_sequencial LSE(busca_sequencial)
#define lse_acessar LSE(acessar)

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

/// Acessa um item na lista encadeada dado um índice.
/// Caso o indice exista, o ponteiro `valor` é atualizado e a função retorna
/// `true`.
bool lse_acessar(const lse_t *lista, int indice, lse_valor_t *valor);

/* --- Des-substituição de nomes --- */

#ifndef LSE_C
#undef LSE
#undef lse_chave
#undef lse_valor_imprime
#undef lse_t
#undef lse_criar
#undef lse_liberar
#undef lse_inserir_inicio
#undef lse_inserir_fim
#undef lse_imprimir
#undef lse_busca_sequencial
#undef lse_acessar
#endif
