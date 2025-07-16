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

    size_t ordem[tam];
    grafo_dfs(grafo, origem, ordem);

    printf("Ordem de visita a partir do vértice %lu:\n", origem);
    for (size_t i = 0; i < tam; i++) {
        printf("Vértice %lu visitado na ordem %lu\n", i, ordem[i]);
    }
}
