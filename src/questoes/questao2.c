#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

/**
 * Implementação da Questão 2 - Busca em Largura (BFS)
 * Usando apenas as funções públicas das interfaces
 */
void questao2(const grafo_t *grafo, size_t origem) {
    if (!grafo) return;

    size_t tam = grafo_tamanho(grafo);
    size_t dist[tam];

    printf("\n=== QUESTÃO 2 - BUSCA EM LARGURA (BFS) ===\n");

    grafo_bfs(grafo, origem, dist);

    printf("Distâncias a partir do nó %lu:\n", origem);
    for (size_t i = 0; i < tam; i++) {
        printf("Nó %zu: %zu\n", i, dist[i]);
    }
}
