#define LSE_C
#include "lse.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

struct lse_t {
    lse_valor_t valor;
    lse_t *prox;
};

/// Cria um nó da lista encadeada.
lse_t *lse_criar(lse_valor_t valor) {
    lse_t *no = malloc(sizeof(lse_t));

    if (no) {
        no->valor = valor;
        no->prox = NULL;
    }

    return no;
};

/// Insere um ítem no início da lista encadeada.
lse_t *lse_inserir_inicio(lse_t *lista, lse_valor_t valor) {
    lse_t *no = lse_criar(valor);

    if (no) {
        no->prox = lista;
    }

    return no;
};

/// Insere um ítem no fim da lista encadeada.
lse_t *lse_inserir_fim(lse_t *lista, lse_valor_t valor) {
    lse_t *no = lse_criar(valor);

    if (!lista) return no;

    while (lista->prox) lista = lista->prox;

    lista->prox = no;
    return no;
};

/// Libera toda a lista encadeada.
void lse_liberar(lse_t *lista) {
    while (lista) {
        lse_t *no = lista;
        lista = lista->prox;
        free(no);
    }
};

/// Imprime os elementos selecionados da lista encadeada.
void lse_imprimir(const lse_t *lista, int inicio, int fim) {
    int idx = 0;

    printf("[ ");

    if (inicio != 0) printf("..., ");

    while (lista && idx < fim) {
        if (idx >= inicio) {
            lse_valor_imprime(lista->valor);

            // Printar vírgula caso ainda hajam mais elementos para imprimir
            if ((idx + 1) < fim) {
                printf(", ");
            }
        }

        idx++;
        lista = lista->prox;
    }

    if (lista) printf(", ...");
    printf(" ]\n");
};

/// Busca um valor na lista encadeada por chave.
bool lse_busca_sequencial(const lse_t *lista, lse_chave_t chave,
                          lse_valor_t *valor) {
    while (lista) {
        // Retornar quando o primeiro valor for encontrado.
        if (lse_chave(lista->valor) == chave) {
            if (valor) *valor = lista->valor;

            return true;
        }

        lista = lista->prox;
    }

    return false;
};

/// Acessa a lista encadeada por índice.
bool lse_acessar(const lse_t *lista, int indice, lse_valor_t *valor) {
    int idx = 0;
    while (lista) {
        // Retornar quando o valor no índice dado for encontrado.
        if (idx == indice) {
            *valor = lista->valor;
            return true;
        }

        idx++;
        lista = lista->prox;
    }

    return false;
};
