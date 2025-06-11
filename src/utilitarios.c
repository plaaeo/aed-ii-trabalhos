#include <math.h>
#include <time.h>

#include "utilitarios.h"

// Inicia uma medição, guardando t_inicio em `medicoes[i]`.
void medir_inicio(double *medicoes, int i) {
    medicoes[i] = clock();
}

// Finaliza a medição e armazena (t_fim - t_inicio) em `medicoes[i]`, em microsegundos.
void medir_fim(double *medicoes, int i) {
    medicoes[i] = (double)(clock() - medicoes[i]) / (double) CLOCKS_POR_MEDIDA;
}

// Retorna a media do vetor de medições passado.
double media(double* medicoes, int tam) {
    int cont = 0;
    double acc = 0;

    for (int i = 0; i < tam; i++) {
        if (!isnan(medicoes[i])) {
            acc += medicoes[i];
            cont++;
        }
    }

    return acc / cont;
}

// Retorna o desvio padrão do vetor de medições passado.
double desvio_padrao(double media, double* medicoes, int tam) {
    int cont = 0;
    double soma_quadrados = 0;

    for (int i = 0; i < tam; i++) {
        if (!isnan(medicoes[i])) {
            soma_quadrados += pow(medicoes[i] - media, 2);
            cont++;
        }
    }

    return sqrt(soma_quadrados / cont);
}
