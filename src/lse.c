#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "lse.h"

struct lse_no_t {
    int valor;
    lse_no_t *prox;
};

struct lse_t {
    lse_no_t *cabeca;
    lse_no_t *cauda;
    int tamanho;
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
        lista->cauda = (lista->cabeca = no);
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
        lista->cabeca = (lista->cauda = no);
    } else {
        lista->cauda->prox = no;
        lista->cauda = no;
        lista->tamanho++;
    }

    return true;
};

/// Cria uma lista encadeada vazia.
lse_t *lse_criar() {
    lse_t *lse = malloc(sizeof(lse_t));

    if (lse) {
        lse->cabeca = NULL;
        lse->cauda = NULL;
        lse->tamanho = 0;
    }

    return lse;
};

lse_t *lse_criar_aleatorio(int tam) {
    lse_t *lista = lse_criar();

    // Inserir itens aleatórios entre 1 e 1 milhão na LSE
    for (int i = 0; i < tam; i++) {
        int val = rand() % 1000000;
        lse_inserir_final(lista, val + 1);
    }

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

void lse_imprimir(const lse_t *lista, int inicio, int fim) {
    int idx = 0;
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

bool lse_busca_sequencial(const lse_t *lista, int valor, int *indice) {
    int idx = 0;
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

bool lse_acessar(const lse_t *lista, int indice, int *valor) {
    int idx = 0;
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