#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// Inclui os headers originais com caminho relativo
#include "../fila.h"
#include "../grafo.h"

/**
 * Implementação da Questão 2 - Busca em Largura (BFS)
 * Usando apenas as funções públicas das interfaces
 */
void questao2(const grafo_t *grafo, size_t a, size_t *dist) {
    if (!grafo || !dist) return;
    
    size_t tam = grafo_tamanho(grafo);
    if (a >= tam) return;

    // Inicializa distâncias
    for (size_t i = 0; i < tam; i++) {
        dist[i] = SIZE_MAX;
    }
    dist[a] = 0;

    fila_t *fila = fila_criar(tam);
    if (!fila) return;

    if (!fila_inserir(fila, a)) {
        fila_liberar(fila);
        return;
    }

    while (1) {
        size_t atual;
        if (!fila_remover(fila, &atual)) break;

        for (size_t vizinho = 0; vizinho < tam; vizinho++) {
            if (grafo_tem_aresta(grafo, atual, vizinho)) {
                if (dist[vizinho] == SIZE_MAX) {
                    dist[vizinho] = dist[atual] + 1;
                    if (!fila_inserir(fila, vizinho)) {
                        fila_liberar(fila);
                        return;
                    }
                }
            }
        }
    }

    fila_liberar(fila);
}

/**
 * Função de teste
 */
void teste_questao2() {
    printf("\n=== QUESTÃO 2 - BUSCA EM LARGURA (BFS) ===\n");

    grafo_t *grafo = grafo_criar_conexo(5, 0.5);
    if (!grafo) {
        printf("Erro ao criar grafo!\n");
        return;
    }

    size_t dist[5];
    questao2(grafo, 0, dist);

    printf("Distâncias a partir do nó 0:\n");
    for (size_t i = 0; i < 5; i++) {
        printf("Nó %zu: %zu\n", i, dist[i]);
    }

    grafo_free(grafo);
}

int main() {
    srand(time(NULL));
    teste_questao2();
    return 0;
}