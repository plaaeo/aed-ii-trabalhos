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

// Inicia uma medição, guardando t_inicio em `medicoes[i]`.
void medir_inicio(double *medicoes, int i) { medicoes[i] = clock(); }

// Finaliza a medição e armazena (t_fim - t_inicio) em `medicoes[i]`, em microsegundos.
void medir_fim(double *medicoes, int i) {
    medicoes[i] = (double)(clock() - medicoes[i]) / CLOCKS_PER_US;
}

// Retorna o desvio padrão do vetor de medições passado.
double desvio_padrao(double media, double* medicoes, int tam) {
    double soma_quadrados = 0;

    for (int i = 0; i < tam; i++)
        soma_quadrados += pow(medicoes[i] - media, 2);

    return sqrt(soma_quadrados / tam);
}

// Imprime os dados da questão 1
// - `seed` é a semente usada para gerar os vetores aleatórios; 
// - `N` é o tamanho dos vetores aleatórios; 
// - `I` é a quantidade de repetições de cada algorítmo de busca.
void questao1(unsigned int seed, int N, int I) {
    srand(seed);

    double tempos_sequencial[I], tempos_binaria[I];
    double soma_sequencial = 0, soma_binaria = 0;

    // Busca sequencial 30 vezes
    for (int i = 0; i < I; i++) {
        int vet_sequencial[N];
        vetor_gerar_aleatorio(vet_sequencial, N); // Gera vetor aleatorio

        // Medir busca sequencial
        int valor_busca = 1 + (rand() % 1000000); // Gera valor aleatorio

        if (debug_imprimir_vetores) {
            printf("  <Vetor seq. %d> (x = %d) [ %d, %d, ... ]\n", i + 1, valor_busca, vet_sequencial[0], vet_sequencial[1]);
        }

        medir_inicio(tempos_sequencial, i);
        vetor_busca_sequencial(vet_sequencial, N, valor_busca);
        medir_fim(tempos_sequencial, i);

        soma_sequencial += tempos_sequencial[i];
    }

    // Busca binaria 30 vezes
    for (int i = 0; i < I; i++) {
        // Gera vetor aleatório ordenado
        int vet_binario[N];
        vetor_gerar_ordenado(vet_binario, N);

        // Gera valor aleatorio
        int valor_busca = 1 + (rand() % 1000000);

        if (debug_imprimir_vetores) {
            printf("  <Vetor bin. %d> (x = %d) [ %d, %d, ... ]\n", i + 1, valor_busca, vet_binario[0], vet_binario[1]);
        }
        
        // Medir busca binária
        medir_inicio(tempos_binaria, i);
        vetor_busca_binaria(vet_binario, N, valor_busca);
        medir_fim(tempos_binaria, i);

        soma_binaria += tempos_binaria[i];
    }

    // Calcular a media sequencial e binária
    double media_sequencial = soma_sequencial / I;
    double media_binaria = soma_binaria / I;

    // Calcular desvio padrao sequencial e binário
    double desvio_sequencial = desvio_padrao(media_sequencial, tempos_sequencial, I);
    double desvio_binario = desvio_padrao(media_binaria, tempos_binaria, I);

    // Exibição de teste
    printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
    printf("  Media do tempo: %.6f us\n", media_sequencial);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_sequencial);

    printf("* Busca Binaria (%d elementos, %d vezes): \n", N, I);
    printf("  Media do tempo: %.6f us\n", media_binaria);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_binario);
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar as listas aleatórias; 
// - `N` é o tamanho das listas aleatórias; 
// - `I` é a quantidade de repetições da busca sequencial.
void questao2(unsigned int seed, int N, int I) {
    srand(seed);

    double tempos[I];
    double soma_tempos = 0;
    
    for (int i = 0; i < I; i++) {
        // Gerar lista com itens aleatórios
        lse_t *lse = lse_criar_aleatorio(N);

        // Gerar valor aleatorio
        int valor_busca = 1 + (rand() % 1000000); 

        if (debug_imprimir_vetores) {
            printf("  <LSE %d> (x = %d) ", i + 1, valor_busca);
            lse_imprimir(lse, 0, 2);
        }

        // Medir busca sequencial
        medir_inicio(tempos, i);
        lse_busca_sequencial(lse, valor_busca, NULL);
        medir_fim(tempos, i);
        
        soma_tempos += tempos[i];
    }

    // Calcular a media e desvio padrão dos tempos medidos
    double media_tempos = soma_tempos / I;
    double desvio_tempos = desvio_padrao(media_tempos, tempos, I);
    
    // Exibição de teste
    printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
    printf("  Media do tempo: %.6f us\n", media_tempos);
    printf("  Desvio Padrao: %.6f us\n\n", desvio_tempos);
}

void questao3(unsigned int seed) {
    // ...
}

int main(int argc, char **argv) {
    // Salvar a seed aleatória para re-gerar os vetores da Q1 na Q2
    unsigned int seed = time(NULL);

    int N = 1000000;
    int I = 30;
    
    if (argc > 1) sscanf(argv[1], " %d", &N);
    if (argc > 2) sscanf(argv[2], " %d", &I);

    // Questão 1
    printf("Dados da Q1:\n");
    questao1(seed, N, I);

    // Questão 2
    printf("Dados da Q2:\n");
    questao2(seed, N, I);

    // Questão 3
    printf("Dados da Q3:\n");
    questao3(seed);
}
