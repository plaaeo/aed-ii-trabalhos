#include <stdio.h>

#include "grafo.h"
#include "questoes.h"
#include "util.h"

/**
 * Implementação da Questão 5 - Detecção de ciclos >= 3.
 */
void questao5() {
    // Todos os possíveis tamanhos para os grafos
    size_t tamanhos[] = {8, 16, 32};

    // Todos os possíveis graus de conectividade dos grafos
    float graus[] = {0.05, 0.15, 0.25, 0.50};

    // Hack para definir n_tamanhos e n_graus como 'constantes'
    enum {
        n_tamanhos = sizeof(tamanhos) / sizeof(size_t),
        n_graus = sizeof(graus) / sizeof(float)
    };

    for (size_t t = 0; t < n_tamanhos; t++) {
        for (size_t g = 0; g < n_graus; g++) {
            grafo_t *grafo = grafo_criar_conexo(tamanhos[t], graus[g]);

            // Imprimir informações do grafo
            printf("=== QUESTÃO 5 - BFS e DFS ===\n\n");
            printf(
                "--- Grafo de tamanho %lu com %.02f%% de "
                "conectividade ---\n\n",
                tamanhos[t], graus[g] * 100);

            // Imprimir matriz do grafo
            printf("> Matriz de adjacência:\n");
            grafo_imprimir_matriz(grafo, NULL);

            // Imprimir pares de arestas do grafo
            printf("\n> Pares de arestas:\n");
            grafo_imprimir_arestas(grafo, NULL);

            // Imprimir veredito
            if (grafo_tem_ciclo(grafo)) {
                printf("\n> O grafo possui ciclo!\n");
            } else {
                printf("\n> O grafo NÃO possui ciclo!\n");
            }

            // Limpar memória
            grafo_free(grafo);
            aguardar_entrada();
        }
    }
}
