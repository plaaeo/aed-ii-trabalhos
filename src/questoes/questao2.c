#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grafo.h"

/**
 * Implementação da Questão 2 - Busca em Largura (BFS)
 * Usando apenas as funções públicas das interfaces
 * Retorna o tempo de execução do algorítmo em `clock_t`s.
 */
clock_t questao2(const grafo_t *grafo, size_t origem) {
    size_t tam = grafo_tamanho(grafo);

    printf("\n=== QUESTÃO 2 - Busca em largura (BFS) ===\n");

    // Realizar busca em largura
    size_t dist[tam];

    clock_t tempo = clock();
    grafo_bfs(grafo, origem, dist);
    tempo = clock() - tempo;

    // Matriz onde cada linha equivale a um nível da árvore
    size_t *arvore = calloc(tam * tam, sizeof(size_t));

    // Vetor onde cada posição `i` equivale ao tamanho do nível `i` da árvore.
    size_t tamanhos[tam];
    for (size_t i = 0; i < tam; i++) {
        tamanhos[i] = 0;
    }

    // Preencher árvore com os dados da BFS
    for (size_t i = 0; i < tam; i++) {
        size_t nivel = dist[i];
        size_t coluna = tamanhos[nivel];
        size_t idx = (nivel * tam) + coluna;

        arvore[idx] = i;
        tamanhos[nivel]++;
    }

    // Imprimir árvore
    for (size_t n = 0; tamanhos[n] > 0; n++) {
        if (n == 0) {
            printf("Raíz: ");
        } else {
            printf("Nível %lu: ", n);
        }

        for (size_t i = 0; i < tamanhos[n]; i++) {
            printf("%lu ", arvore[n * tam + i]);
        }

        printf("\n");
    }

    free(arvore);
    return tempo;
}
