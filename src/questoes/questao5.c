#include <stdio.h>
#include <stdlib.h>
#include "ciclo.c"

int q5() {
    int n = 4;

    // Criando grafo com ciclo: 0-1-2-0
    int **grafo = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo[i] = calloc(n, sizeof(int));
    }

    grafo[0][1] = grafo[1][0] = 1;
    grafo[1][2] = grafo[2][1] = 1;
    grafo[2][0] = grafo[0][2] = 1;

    printf("O grafo possui ciclo? %s\n", possuiCiclo(grafo, n) ? "Sim" : "Não");

    // Liberação da memória
    for (int i = 0; i < n; i++) {
        free(grafo[i]);
    }
    free(grafo);

    return 0;
}
