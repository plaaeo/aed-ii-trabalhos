#include <malloc.h>
#include <stdio.h>

#include "lse.h"

struct lse_no_t {
    int valor;
    lse_no_t *prox;
};

struct lse_t {
    lse_no_t *cabeca;
    lse_no_t *cauda;
    size_t tamanho;
};

/// Cria um nó da lista encadeada.
lse_no_t *lse_no_criar(int valor) {
    lse_no_t *no = malloc(sizeof(lse_no_t));

    if (no) {
        no->valor = valor;
        no->prox = NULL;
    }

    return no;
};

/// Insere um ítem no início da lista encadeada.
bool lse_inserir_inicio(lse_t *lista, int valor) {
    lse_no_t *no = lse_no_criar(valor);

    if (!no)
        return false;

    if (!lista->cauda) {
        lista->cauda = lista->cabeca = no;
    } else {
        no->prox = lista->cabeca;
        lista->cabeca = no;
        lista->tamanho++;
    }

    return true;
};

/// Insere um ítem no fim da lista encadeada.
bool lse_inserir_final(lse_t *lista, int valor) {
    lse_no_t *no = lse_no_criar(valor);

    if (!no)
        return false;

    if (!lista->cauda) {
        lista->cabeca = lista->cauda = no;
    } else {
        lista->cauda->prox = no;
        lista->tamanho++;
    }

    return true;
};

lse_t *lse_criar() {
    lse_t *lse = malloc(sizeof(lse_t));

    if (lse) {
        lse->cabeca = NULL;
        lse->cauda = NULL;
        lse->tamanho = 0;
    }

    return lse;
};

lse_t *lse_criar_com_vetor(const vetor_t *vetor) {
    lse_t *lista = lse_criar();

    // TODO: Fazer quando a implementação do vetor estiver completa.

    return lista;
};

void lse_liberar(lse_t *lista) {
    while (lista->cabeca) {
        lse_no_t *no = lista->cabeca;
        lista->cabeca = lista->cabeca->prox;

        free(no);
    }

    free(lista);
};

void lse_imprimir(const lse_t *lista, size_t inicio, size_t fim) {
    size_t idx = 0;
    lse_no_t *no = lista->cabeca;

    printf("[ ");

    if (inicio != 0)
        printf("..., ");

    while (no) {
        if (idx >= inicio && idx < fim) {
            printf("%d", no->valor);

            // Printar vírgula caso ainda hajam mais elementos para imprimir
            if ((idx + 1) < fim) {
                printf(", ");
            }
        }

        idx++;
        no = no->prox;
    }

    if (fim != lista->tamanho)
        printf(", ...");

    printf(" ]\n");
};

bool lse_buscar_seq(const lse_t *lista, int valor, size_t *indice) {
    size_t idx = 0;
    lse_no_t *no = lista->cabeca;

    while (no) {
        // Retornar quando o primeiro valor for encontrado.
        if (no->valor == valor) {
            *indice = idx;
            return true;
        }

        idx++;
        no = no->prox;
    }

    return false;
};

bool lse_acessar(const lse_t *lista, size_t indice, int *valor) {
    size_t idx = 0;
    lse_no_t *no = lista->cabeca;

    while (no) {
        // Retornar quando o valor no índice dado for encontrado.
        if (idx == indice) {
            *valor = no->valor;
            return true;
        }

        idx++;
        no = no->prox;
    }

    return false;
};