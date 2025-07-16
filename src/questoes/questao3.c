#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

/**
 * Implementação da Questão 3 - Busca em Profundidade
 * Marca a ordem de visita de cada nó no vetor `ordem[]`.
 */
void questao3(const grafo_t *grafo, size_t origem) {
    if (!grafo) return;

    size_t tam = grafo_tamanho(grafo);

    printf("\n=== QUESTÃO 3 - BUSCA EM PROFUNDIDADE ===\n");

    // Realizar busca por profundidade
    size_t dist[tam], ordem[tam];
    grafo_dfs(grafo, origem, dist, ordem);

    printf("Ordem de visita a partir do vértice %lu:\n", origem);
    printf("%lu", origem);
    for (size_t i = 1; i < tam; i++) {
        printf(" -> %lu", ordem[i]);
    }
    printf("\n");
}
