#include <time.h>
#include <stdio.h>

#include "grafo.h"
#include "fila.h"

/// Teste de criação de grafo conexo (remover na entrega)
void teste_grafo() {
}

/// Teste do funcionamento da fila (remover na entrega)
void teste_fila() {
    size_t item;
    fila_t *fila = fila_criar(8);

    printf("testando funcionamento da fila\n");

    for (size_t j = 0; j < 10; j++) {
        // Inserir 8 elementos
        for (size_t i = 0; i < 8; i++) {
            bool res = fila_inserir(fila, i + 1);
            printf("-> inserindo %lu (%s)\n", i + 1, res ? "ok" : "cheio");
        }

        // Remover uma quantidade cada vez menor de elementos (de 10 a 2)
        for (size_t i = 10; j < i; i--) {
            bool res = fila_remover(fila, &item);
            printf("-> removendo item %lu ", 11 - i);

            if (res) printf("(ok, %lu)\n", item);
            else     printf("(vazio)\n");
        }
    }

    // Remover todos os itens da fila até esvaziar
    while (fila_remover(fila, &item)) {
        printf("-> removendo sobras (%lu)\n", item);
    }

    printf("-> fim do teste\n");
}

int main() {
    srand(time(NULL));

    teste_fila();

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
