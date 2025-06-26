#include "fila.h"

struct fila_t {
    /// O vetor circular com os elementos da fila.
    fila_valor_t *vec;

    /// A capacidade total do vetor, a quantidade de elementos
    /// usados e o índice do primeiro elemento respectivamente.
    size_t cap, tam, idx;
};

/// Cria uma fila de 'fila_valor_t's com a dada capacidade máxima.
fila_t *fila_criar(size_t capacidade) {
    if (capacidade == 0)
        return NULL;

    fila_t *fila = malloc(sizeof(fila_t));

    fila->vec = malloc(sizeof(fila_valor_t) * capacidade);
    fila->tam = fila->idx = 0;
    fila->cap = capacidade;

    return fila;
};

/// Libera a fila.
void fila_liberar(fila_t *fila) {
    if (!fila) return;
    free(fila->vec);
    free(fila);
};

/// Insere um elemento no final da fila. Retorna 'false'
/// se a fila estiver cheia e o elemento não for inserido.
bool fila_inserir(fila_t* fila, fila_valor_t valor) {
    if (fila->tam == fila->cap)
        return false;

    size_t i = fila->idx + fila->tam++;
    fila->vec[i % fila->cap] = valor;
    return true;
};

/// Remove o elemento atualmente na frente da fila.
bool fila_remover(fila_t* fila, fila_valor_t *resultado) {
    if (fila->tam == 0)
        return false;

    *resultado = fila->vec[fila->idx];
    fila->idx = (fila->idx + 1) % fila->cap;
    fila->tam--;
    return true;
};
