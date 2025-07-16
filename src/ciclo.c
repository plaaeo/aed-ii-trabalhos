#include "ciclo.h"

#include <stddef.h>
#include <stdlib.h>

/// Função auxiliar de DFS para detecção de ciclos
static bool dfs_ciclo(const grafo_t *grafo, size_t atual, size_t pai, bool *visitado) {
    visitado[atual] = true;

    for (size_t vizinho = 0; vizinho < grafo_tamanho(grafo); vizinho++) {
        if (grafo_tem_aresta(grafo, atual, vizinho)) {
            if (!visitado[vizinho]) {
                if (dfs_ciclo(grafo, vizinho, atual, visitado)) {
                    return true;
                }
            } else if (vizinho != pai) {
                return true; // Encontrou um ciclo (tamanho ≥ 3)
            }
        }
    }

    return false;
}

bool grafo_tem_ciclo(const grafo_t *grafo) {
    size_t n = grafo_tamanho(grafo);
    bool *visitado = calloc(n, sizeof(bool));
    if (!visitado) return false;

    for (size_t i = 0; i < n; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(grafo, i, (size_t)-1, visitado)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}
