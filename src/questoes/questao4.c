#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grafo.h"
#include "util.h"

/**
 * Implementação da Questão 4 - Geração de todos os caminhos
 * usando DFS.
 */
void questao4() {
    // Todos os possíveis graus de conectividade dos grafos
    float graus[] = {0.25, 0.50, 0.75, 1.00};

    // Hack para definir n_graus como 'constante'
    enum {
        n_graus = sizeof(graus) / sizeof(float)
    };

    // Iterar por todos os grafos a serem gerados
    for (size_t g = 0; g < n_graus; g++) {
        grafo_t *grafo = grafo_criar_conexo(6, graus[g]);

        printf("=== QUESTÃO 4 - Geração de caminhos usando DFS ===\n\n");
        printf(">- Mini-grafo de tamanho 6 com %.02f%% de conectividade -<\n",
               graus[g] * 100);

        // Imprime os pares de arestas do grafo.
        printf("\n> Pares de arestas do grafo:\n");
        grafo_imprimir_arestas(grafo, NULL);

        // Calcular todos os caminhos do grafo
        size_t quantos = 0;
        size_t **matriz = grafo_calcular_caminhos(grafo, 0, &quantos);

        printf("\n> Caminhos gerados:\n");
        for (size_t i = 0; i < quantos; i++) {
            printf("  %lu", matriz[i][0]);
            for (size_t j = 1; j < grafo_tamanho(grafo); j++) {
                // Fim do caminho gerado
                if (matriz[i][j] == SIZE_MAX) {
                    free(matriz[i]);
                    break;
                }

                printf(" -> %lu", matriz[i][j]);
            }
            printf("\n");
        }

        printf("\n");
        free(matriz);
        grafo_free(grafo);
        aguardar_entrada();
    }
}
