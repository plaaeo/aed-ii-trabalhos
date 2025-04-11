#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lse.h"
#include "vetor.h"

// Defina "true" para imprimir os valores usados para busca nas questões
const bool debug_imprimir_vetores = false;

// A quantidade de clocks em 1 microsegundo
#define CLOCKS_PER_US (CLOCKS_PER_SEC / 1000000)

void medir_inicio(double *medicoes, int i) { medicoes[i] = clock(); }

void medir_fim(double *medicoes, int i) {
    medicoes[i] = (double)(clock() - medicoes[i]) / CLOCKS_PER_US;
}

// Imprime os dados da questão 1
// - `seed` é a semente usada para gerar os vetores aleatórios; 
// - `N` é o tamanho dos vetores aleatórios; 
// - `I` é a quantidade de repetições de cada algorítmo de busca.
void questao1(unsigned int seed, int N, int I) {
    printf("Dados da Q1:\n");
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

        if (debug_imprimir_vetores) {
            printf("  <Vetor seq. %d> (x = %d) [ %d, %d, ... ]\n", i + 1, valor_busca, vet_sequencial[0], vet_sequencial[1]);
        }

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

        if (debug_imprimir_vetores) {
            printf("  <Vetor bin. %d> (x = %d) [ %d, %d, ... ]\n", i + 1, valor_busca, vet_binario[0], vet_binario[1]);
        }

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

    double desvio_sequencial = sqrt(soma_quadrados_sequencial / I);
    double desvio_binario = sqrt(soma_quadrados_binario / I);

    // Exibição de teste
    printf("* Busca Sequencial: \n");
    printf("  Media do tempo: %.6f us\n", media_sequencial);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_sequencial);

    printf("* Busca Binaria: \n");
    printf("  Media do tempo: %.6f us\n", media_binaria);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_binario);
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar as listas aleatórias; 
// - `N` é o tamanho das listas aleatórias; 
// - `I` é a quantidade de repetições da busca sequencial.
void questao2(unsigned int seed, int N, int I) {
    printf("Dados da Q2:\n");
    srand(seed);

    double tempos[I];
    double soma_tempos = 0;
    
    for (int i = 0; i < I; i++) {
        // Gerar lista com itens aleatórios
        lse_t *lse = lse_criar_aleatorio(N);

        // Gerar valor aleatorio
        int valor_busca = 1 + (rand() % 1000000); 

        // Medir busca sequencial
        medir_inicio(tempos, i);
        
        int resultado = 0;
        bool _encontrado = lse_busca_sequencial(lse, valor_busca, &resultado);

        medir_fim(tempos, i);

        if (debug_imprimir_vetores) {

            printf("  <LSE %d> (x = %d) ", i + 1, valor_busca);
            lse_imprimir(lse, 0, 2);
        }

        soma_tempos += tempos[i];
    }

    // Calcular a media dos tempos
    double media_tempos = soma_tempos / I;

    // Calcular desvio padrao dos tempos
    double soma_quadrados = 0;

    for (int i = 0; i < I; i++) {
        double diff = tempos[i] - media_tempos;
        soma_quadrados += diff * diff;
    }

    double desvio_tempos = sqrt(soma_quadrados / I);
    
    // Exibição de teste
    printf("* Busca Sequencial: \n");
    printf("  Media do tempo: %.6f us\n", media_tempos);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_tempos);
}

int main(int argc, char **argv) {
    // Salvar a seed aleatória para re-gerar os vetores da Q1 na Q2
    unsigned int seed = time(NULL);

    // Questão 1
    questao1(seed, 1000000, 30);

    // Questão 2
    questao2(seed, 1000000, 30);

    // Questão 3

    // .....
    printf("Dados da Q3:\n");
}
