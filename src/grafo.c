#include "grafo.h"

/// TAD para um grafo não direcionado de tamanho constante.
struct grafo_t {
    /// Matriz de adjacência do grafo.
    uint8_t *adj;

    /// A quantidade de nós do grafo.
    size_t tam;
};

/// Calcula o índice da aresta a->b na matriz de adjacência do grafo.
size_t indice(const grafo_t *grafo, size_t a, size_t b) {
    return a * grafo->tam + b;
}

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam) {
    grafo_t *grafo = (grafo_t*) malloc(sizeof(grafo_t));
    grafo->adj = malloc(tam * tam * sizeof(uint8_t));
    grafo->tam = tam;
    return grafo;
}

/// Libera a memória alocada para o grafo dado.
void grafo_free(grafo_t *grafo) {
    if (!grafo)
        return;

    free(grafo->adj);
    free(grafo);
}

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b) {
    if (a >= grafo->tam || b >= grafo->tam)
        return false;
    
    return grafo->adj[indice(grafo, a, b)];
}

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor) {
    if (a >= grafo->tam || b >= grafo->tam)
        return;
    
    grafo->adj[indice(grafo, a, b)] = valor;
    grafo->adj[indice(grafo, b, a)] = valor;
}