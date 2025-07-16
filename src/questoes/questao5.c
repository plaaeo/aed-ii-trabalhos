#include <stdio.h>
#include "grafo.h"
#include "ciclo.h"

int main() {
    grafo_t *g = grafo_criar(4);
    grafo_definir_aresta(g, 0, 1, true);
    grafo_definir_aresta(g, 1, 2, true);
    grafo_definir_aresta(g, 2, 0, true); // forma ciclo 0-1-2-0

    if (grafo_tem_ciclo(g)) {
        printf("Grafo possui ciclo\n");
    } else {
        printf("Grafo NÃO possui ciclo\n");
    }

    grafo_free(g);
    return 0;
}
