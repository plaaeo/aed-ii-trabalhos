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

void lse_liberar(lse_t *lista) {
    while (lista) {
        lse_t *no = lista;
        lista = lista->prox;
        free(no);
    }
};

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

lse_t* acessar_prox(lse_t* lista){
    return lista->prox;
}

lse_valor_t lse_cabeca(lse_t *lista) {
    return lista->valor;
}
