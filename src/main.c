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

extern void questao2(const grafo_t *grafo);
extern void questao3(const grafo_t *grafo);

int main() {
    srand(time(NULL));

    teste_fila();

    grafo_t *grafo = grafo_criar_conexo(10, 0.60);

    for (size_t i = 0; i < grafo_tamanho(grafo); i++)
        grafo_imprimir_no(grafo, i);

    questao2(grafo);
    questao3(grafo);

    // for (size_t i = 0; i < grafo_tamanho(grafo); i++)
    //     printf("%lu\n", i);
}
