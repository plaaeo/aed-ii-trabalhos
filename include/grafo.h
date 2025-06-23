#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

/// TAD para um grafo não direcionado de tamanho constante.
typedef struct grafo_t grafo_t;

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam);

/// Libera a memória alocada para o grafo dado.
void grafo_free(grafo_t *grafo);

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b);

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor);

#endif