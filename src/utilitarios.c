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
    double acc = 0;
    for (int i = 0; i < tam; i++)
        acc += medicoes[i];
    return acc / tam;
}

// Retorna o desvio padrão do vetor de medições passado.
double desvio_padrao(double media, double* medicoes, int tam) {
    double soma_quadrados = 0;

    for (int i = 0; i < tam; i++)
        soma_quadrados += pow(medicoes[i] - media, 2);

    return sqrt(soma_quadrados / tam);
}
