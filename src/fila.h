#pragma once

#include <stdlib.h>
#include <stdbool.h>

/// Um TAD para uma fila de elementos 'fila_valor_t' de capacidade fixa.
typedef struct fila_t fila_t;

/// O tipo do valor armazenado na fila.
typedef size_t fila_valor_t;

/// Cria uma fila de 'fila_valor_t's com a dada capacidade máxima.
fila_t *fila_criar(size_t capacidade);

/// Libera a fila.
void fila_liberar(fila_t *fila);

/// Insere um elemento no final da fila. Retorna 'false'
/// se a fila estiver cheia e o elemento não for inserido.
bool fila_inserir(fila_t* fila, fila_valor_t valor);

/// Remove o elemento atualmente na frente da fila e armazena-o
/// em '*resultado'. Retorna 'false' se a fila estiver vazia.
bool fila_remover(fila_t* fila, fila_valor_t *resultado);
