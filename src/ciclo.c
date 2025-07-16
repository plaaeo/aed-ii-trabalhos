#include "ciclo.h"
#include <stdlib.h>

#define max_vertices 100

static bool visitado[max_vertices];
static bool encontrouCiclo = false;

static void inicializarVisitados(int n) {
    for (int i = 0; i < n; i++) {
        visitado[i] = false;
    }
}

static void dfsDetectaCiclo(int atual, int pai, int **grafo, int n) {
    visitado[atual] = true;

    for (int i = 0; i < n; i++) {
        if (grafo[atual][i]) {
            if (!visitado[i]) {
                dfsDetectaCiclo(i, atual, grafo, n);
            } else if (i != pai) {
                encontrouCiclo = true;
            }
        }
    }
}

bool possuiCiclo(int **grafo, int n) {
    inicializarVisitados(n);
    encontrouCiclo = false;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfsDetectaCiclo(i, -1, grafo, n);
            if (encontrouCiclo) return true;
        }
    }

    return false;
}
