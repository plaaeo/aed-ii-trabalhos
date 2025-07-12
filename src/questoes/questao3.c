#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "grafo.h"

/**
 * Implementação da Questão 3 - Busca em Profundidade
 * Marca a ordem de visita de cada nó no vetor `visita[]`.
 */
void questao3(const grafo_t *grafo, size_t origem, size_t *visita) {
    if (!grafo || !visita) return;

    size_t tam = grafo_tamanho(grafo);
    if (origem >= tam) return;

    // Inicializa todos os nós como não visitados
    for (size_t i = 0; i < tam; i++)
        visita[i] = 0;

    size_t ordem = 1;

    void dfs(size_t atual) {
        visita[atual] = ordem++;

        for (size_t vizinho = 0; vizinho < tam; vizinho++) {
            if (grafo_tem_aresta(grafo, atual, vizinho) && visita[vizinho] == 0) {
                dfs(vizinho);
            }
        }
    }

    dfs(origem);
}

/**
 * Função de teste para a Questão 3
 */
void teste_questao3() {
    printf("\n=== QUESTÃO 3 - BUSCA EM PROFUNDIDADE ===\n");

    grafo_t *grafo = grafo_criar_conexo(8, 0.6);
    if (!grafo) {
        printf("Erro ao criar o grafo.\n");
        return;
    }

    size_t ordem[8];
    questao3(grafo, 0, ordem);

    printf("Ordem de visita a partir do vértice 0:\n");
    for (size_t i = 0; i < 8; i++) {
        printf("Vértice %lu visitado na ordem %lu\n", i, ordem[i]);
    }

    grafo_free(grafo);
}
