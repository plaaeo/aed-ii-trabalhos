#include <stdio.h>

#include "grafo.h"

/// TAD para um grafo não direcionado de tamanho constante.
struct grafo_t {
    /// Matriz de adjacência para cada nó do grafo.
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

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor) {
    if (a >= grafo->tam || b >= grafo->tam)
        return;
    
    grafo->adj[indice(grafo, a, b)] = valor;
    grafo->adj[indice(grafo, b, a)] = valor;
}

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b) {
    if (a >= grafo->tam || b >= grafo->tam)
        return false;
    
    return grafo->adj[indice(grafo, a, b)];
}

/// Executa busca por largura, ou 'breadth-first search', a partir de um nó 'a'.
void grafo_bfs(const grafo_t *grafo, size_t a, size_t *dist) {
    (void)grafo;
    (void)a;
    (void)dist;
    return;
};

/// Executa busca por profundindade, ou 'depth-first search', a partir de um nó 'a'.
void grafo_dfs(const grafo_t *grafo, size_t a, size_t *dist) {
    (void)grafo;
    (void)a;
    (void)dist;
    return;
};

/// Imprime todos os nós adjacentes ao nó dado.
void grafo_imprimir_no(const grafo_t *grafo, size_t a) {
    if (a >= grafo->tam)
        return;

    printf("%02lu -> [ ", a);
    
    for (size_t b = 0; b < grafo->tam; b++) {
        bool adj = grafo->adj[indice(grafo, a, b)];
        
        // Imprime o nó adjacente ao 'a'
        if (adj)
            printf("%02lu ", b);
    }
    
    printf("]\n");
}

/// Retorna a quantidade de nós no grafo.
size_t grafo_tamanho(const grafo_t *grafo) {
    return grafo->tam;
}