#include <time.h>
#include <stdio.h>

#include "grafo.h"

int main() {
    srand(time(NULL));

    grafo_t *grafo = grafo_criar(16);
    size_t tamanho = grafo_tamanho(grafo);

    // Definir um grafo aleatório com 50% de chance de conexão
    int chance_conexao = 50;
    for (size_t a = 0; a < tamanho; a++) {
        for (size_t b = 0; b < tamanho; b ++) {
            if ((rand() % 100) < chance_conexao) {
                // Definir aresta única
                grafo_definir_aresta(grafo, a, b, true);
            }
        }
    }

    for (size_t i = 0; i < tamanho; i++)
        grafo_imprimir_no(grafo, i);
}