#include <stdio.h>
#include <time.h>

#include "fila.h"
#include "grafo.h"

/// Teste de criação de grafo conexo (remover na entrega)
void teste_grafo() {}

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

            if (res)
                printf("(ok, %lu)\n", item);
            else
                printf("(vazio)\n");
        }
    }

    // Remover todos os itens da fila até esvaziar
    while (fila_remover(fila, &item)) {
        printf("-> removendo sobras (%lu)\n", item);
    }

    printf("-> fim do teste\n");
}

extern void questao2(const grafo_t *grafo, size_t origem);
extern void questao3(const grafo_t *grafo, size_t origem);

int main() {
    srand(time(NULL));

    // Todos os possíveis graus de conectividade dos grafos
    float graus[] = {0.0, 0.25, 0.50, 0.75, 1.00};
    size_t n_graus = sizeof(graus) / sizeof(float);
    for (size_t g = 0; g < n_graus; g++) {
        printf("%f\n", graus[g]);
        grafo_t *grafo = grafo_criar_conexo(20, graus[g]);
        grafo_imprimir_arestas(grafo, NULL);

        questao2(grafo, 0);
        questao3(grafo, 0);

        grafo_free(grafo);
    }

    // for (size_t i = 0; i < grafo_tamanho(grafo); i++)
    //     printf("%lu\n", i);
}
