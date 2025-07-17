#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grafo.h"

/**
 * Implementação da Questão 3 - Busca em Profundidade
 * Marca a ordem de visita de cada nó no vetor `ordem[]`.
 * Retorna o tempo de execução do algorítmo em `clock_t`s.
 */
clock_t questao3(const grafo_t *grafo, size_t origem) {
    size_t tam = grafo_tamanho(grafo);

    printf("\n=== QUESTÃO 3 - Busca em profundidade (DFS) ===\n");

    // Realizar busca por profundidade
    size_t dist[tam], ordem[tam];

    clock_t tempo = clock();
    grafo_dfs(grafo, origem, dist, ordem);
    tempo = clock() - tempo;

    printf("Ordem de visita a partir do vértice %lu:\n", origem);
    printf("%lu", origem);
    for (size_t i = 1; i < tam; i++) {
        printf(", %lu", ordem[i]);
    }
    printf("\n");

    return tempo;
}
