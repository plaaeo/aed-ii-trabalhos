#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

/// TAD para um grafo não direcionado de tamanho constante.
typedef struct grafo_t grafo_t;

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam);

/// Libera a memória alocada para o grafo dado.
void grafo_free(grafo_t *grafo);

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor);

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b);

/// Executa busca por largura, ou 'breadth-first search', a partir de um nó 'a'.
/// O resultado é armazenado no vetor passado no argumento 'dist', que deve ter
/// o mesmo tamanho que o numero de nós do grafo.
void grafo_bfs(const grafo_t *grafo, size_t a, size_t *dist);

/// Executa busca por profundidade, ou 'depth-first search', a partir de um nó 'a'.
/// O resultado é armazenado no vetor passado no argumento 'dist', que deve ter
/// o mesmo tamanho que o numero de nós do grafo.
void grafo_dfs(const grafo_t *grafo, size_t a, size_t *dist);

/// Imprime todos os nós adjacentes ao nó dado.
void grafo_imprimir_no(const grafo_t *grafo, size_t a);

/// Retorna a quantidade de nós no grafo.
size_t grafo_tamanho(const grafo_t *grafo);