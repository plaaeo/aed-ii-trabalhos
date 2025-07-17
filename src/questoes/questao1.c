#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grafo.h"
#include "questoes.h"
#include "util.h"

/**
 * Implementação da Questão 1 - Geração de grafos conexos.
 */
void questao1() {
    // Todos os possíveis tamanhos para os grafos
    size_t tamanhos[] = {8, 16, 32};

    // Todos os possíveis graus de conectividade dos grafos
    float graus[] = {0.25, 0.50, 0.75, 1.00};

    // Hack para definir n_tamanhos e n_graus como 'constantes'
    enum {
        n_tamanhos = sizeof(tamanhos) / sizeof(size_t),
        n_graus = sizeof(graus) / sizeof(float)
    };

    // Iterar por todos os grafos a serem gerados
    for (size_t t = 0; t < n_tamanhos; t++) {
        for (size_t g = 0; g < n_graus; g++) {
            grafo_t *grafo = grafo_criar_conexo(tamanhos[t], graus[g]);

            // Imprimir informações do grafo
            printf("=== QUESTÃO 1 - Grafos conexos ===\n\n");
            printf(
                "--- Grafo de tamanho %lu com %.02f%% de "
                "conectividade ---\n\n",
                tamanhos[t], graus[g] * 100);

            // Imprimir pares de arestas do grafo
            printf("> Pares de arestas:\n");
            grafo_imprimir_arestas(grafo, NULL);

            grafo_free(grafo);
            aguardar_entrada();
        }
    }
}
