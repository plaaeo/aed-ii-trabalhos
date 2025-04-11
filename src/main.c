#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lse.h"
#include "vetor.h"

// A quantidade de clocks em 1 microsegundo
#define CLOCKS_PER_US (CLOCKS_PER_SEC / 1000000)

// Tamanho do Vetor
#define N 1000000

// Quantidade de repetições da busca binária/sequencial
#define I 30

void medir_inicio(double *medicoes, int i) { medicoes[i] = clock(); }

void medir_fim(double *medicoes, int i) {
    medicoes[i] = (double)(clock() - medicoes[i]) / CLOCKS_PER_US;
}

int main(int argc, char **argv) {
    // Salvar a seed aleatória para re-gerar os vetores da Q1 na Q2
    unsigned int seed = time(NULL);

    // Questão 1
    srand(seed);

    double tempos_sequencial[I], tempos_binaria[I];
    double soma_sequencial = 0, soma_binaria = 0;

    // Busca sequencial 30 vezes
    for (int i = 0; i < I; i++) {
        int vet_sequencial[N];
        vetor_gerar_aleatorio(vet_sequencial, N); // Gera vetor aleatorio

        // Medir busca sequencial
        int valor_busca = 1 + (rand() % 1000000); // Gera valor aleatorio

        medir_inicio(tempos_sequencial, i);
        vetor_busca_sequencial(vet_sequencial, N, valor_busca);
        medir_fim(tempos_sequencial, i);

        soma_sequencial += tempos_sequencial[i];
    }

    // Busca binaria 30 vezes
    for (int i = 0; i < I; i++) {
        int vet_binario[N];
        vetor_gerar_ordenado(vet_binario, N); // Gera vetor aleatório ordenado

        // Medir busca binária
        int valor_busca = 1 + (rand() % 1000000); // Gera valor aleatorio
        
        medir_inicio(tempos_binaria, i);
        vetor_busca_binaria(vet_binario, N, valor_busca);
        medir_fim(tempos_binaria, i);

        soma_binaria += tempos_binaria[i];
    }

    // Calcular a media sequencial e binária
    double media_sequencial = soma_sequencial / I;
    double media_binaria = soma_binaria / I;

    // Calcular desvio padrao sequencial e binário
    double soma_quadrados_sequencial = 0;
    double soma_quadrados_binario = 0;

    for (int i = 0; i < I; i++) {
        soma_quadrados_sequencial +=
            pow(tempos_sequencial[i] - media_sequencial, 2);

        soma_quadrados_binario += pow(tempos_binaria[i] - media_binaria, 2);
    }

    // Calcular desvio padrao sequencial e binario
    double desvio_sequencial = sqrt(soma_quadrados_sequencial / I);
    double desvio_binario = sqrt(soma_quadrados_binario / I);

    // Exibição de teste
    printf("Dados da Q1:\n");

    printf("* Busca Sequencial: \n");
    printf("  Media do tempo: %.6f us\n", media_sequencial);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_sequencial);

    printf("* Busca Binaria: \n");
    printf("  Media do tempo: %.6f us\n", media_binaria);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_binario);
    
    // Questão 2

    printf("Dados da Q2:\n");

    // Questão 3

    // .....
    printf("Dados da Q3:\n");
}
