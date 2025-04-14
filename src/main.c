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
void questao1(FILE *saida, unsigned int seed, int N, int I) {
    srand(seed);

    double tempos_sequencial[I], tempos_binaria[I];
    double soma_sequencial = 0, soma_binaria = 0;

    // Busca sequencial 30 vezes
    for (int i = 0; i < I; i++) {
        int vet_sequencial[N];
        vetor_gerar_aleatorio(vet_sequencial, N); // Gera vetor aleatorio

        // Medir busca sequencial
        int valor_busca = 1 + (rand() % N); // Gera valor aleatorio

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
        int valor_busca = 1 + (rand() % N);

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
    double media_sequencial = soma_sequencial / (double) I;
    double media_binaria = soma_binaria / (double) I;

    // Calcular desvio padrao sequencial e binário
    double desvio_sequencial = desvio_padrao(media_sequencial, tempos_sequencial, I);
    double desvio_binario = desvio_padrao(media_binaria, tempos_binaria, I);

    if (saida) {
        // Imprimir no arquivo de saída caso presente
        fprintf(saida, "Sequencial (Vetor),%d,%.6f\n", N, media_sequencial);
        fprintf(saida, "Binaria (Vetor),%d,%.6f\n", N, media_binaria);
    } else {
        // Exibição de teste
        printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_sequencial);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_sequencial);

        printf("* Busca Binaria (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_binaria);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_binario);
    }
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar as listas aleatórias; 
// - `N` é o tamanho das listas aleatórias; 
// - `I` é a quantidade de repetições da busca sequencial.
void questao2(FILE *saida, unsigned int seed, int N, int I) {
    srand(seed);

    double tempos[I];
    double soma_tempos = 0;
    
    for (int i = 0; i < I; i++) {
        // Gerar lista com itens aleatórios
        lse_t *lse = lse_criar_aleatorio(N);

        // Gerar valor aleatorio
        int valor_busca = 1 + (rand() % N); 

        if (debug_imprimir_vetores) {
            printf("  <LSE %d> (x = %d) ", i + 1, valor_busca);
            lse_imprimir(lse, 0, 2);
        }

        // Medir busca sequencial
        medir_inicio(tempos, i);
        lse_busca_sequencial(lse, valor_busca, NULL);
        medir_fim(tempos, i);

        soma_tempos += tempos[i];
        lse_liberar(lse);
    }

    // Calcular a media e desvio padrão dos tempos medidos
    double media_tempos = soma_tempos / (double) I;
    double desvio_tempos = desvio_padrao(media_tempos, tempos, I);
    
    if (saida) {
        // Imprimir no arquivo de saída caso presente
        fprintf(saida, "Sequencial (LSE),%d,%.6f\n", N, media_tempos);
    } else {
        // Exibição de teste
        printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_tempos);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_tempos);
    }
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar os vetores aleatórios; 
// - `N` é o tamanho dos vetores aleatórios; 
// - `I` é a quantidade de repetições dos algorítmos de ordenação.
void questao3(FILE *saida, unsigned int seed, int N, int I) {
    srand(seed);

    int original[N], copia[N];
    double tempo_b[I], tempo_i[I], tempo_s[I], tempo_q[I], tempo_m[I];
    double soma_b = 0, soma_i = 0, soma_s = 0, soma_q = 0, soma_m = 0;

    // Executa 10 rodadas
    for (int r = 0; r < I; r++) {
        vetor_gerar_aleatorio(original, N);

        // Medir o bubble sort
        vetor_copiar(original, copia, N);
        medir_inicio(tempo_b, r);
        vetor_ordenar_bubble(copia, N);
        medir_fim(tempo_b, r);

        // Medir o insertion sort
        vetor_copiar(original, copia, N);
        medir_inicio(tempo_i, r);
        vetor_ordenar_insertion(copia, N);
        medir_fim(tempo_i, r);

        // Medir o selection sort
        vetor_copiar(original, copia, N);
        medir_inicio(tempo_s, r);
        vetor_ordenar_selection(copia, N);
        medir_fim(tempo_s, r);

        // Medir o quicksort
        vetor_copiar(original, copia, N);
        medir_inicio(tempo_q, r);
        vetor_ordenar_quick(copia, 0, N);
        medir_fim(tempo_q, r);

        // Medir o merge sort
        vetor_copiar(original, copia, N);
        medir_inicio(tempo_m, r);
        vetor_ordenar_merge(copia, 0, N);
        medir_fim(tempo_m, r);

        // Somar valores para o cálculo da média e desvio padrão
        soma_b += tempo_b[r];
        soma_i += tempo_i[r];
        soma_s += tempo_s[r];
        soma_q += tempo_q[r];
        soma_m += tempo_m[r];
    }

    // Calcular as médias
    double media_b = soma_b / (double) I,
           media_i = soma_b / (double) I,
           media_s = soma_s / (double) I,
           media_q = soma_q / (double) I,
           media_m = soma_m / (double) I;
    
    // Calcular os desvios padrão
    double desvio_b = desvio_padrao(media_b, tempo_b, N),
           desvio_i = desvio_padrao(media_b, tempo_b, N),
           desvio_s = desvio_padrao(media_s, tempo_s, N),
           desvio_q = desvio_padrao(media_q, tempo_q, N),
           desvio_m = desvio_padrao(media_m, tempo_m, N);
    
    if (saida) {
        // Imprimir no arquivo de saída caso presente
        fprintf(saida, "Bubble,%d,%.6f\n", N, media_b);
        fprintf(saida, "Insertion,%d,%.6f\n", N, media_i);
        fprintf(saida, "Selection,%d,%.6f\n", N, media_s);
        fprintf(saida, "Quicksort,%d,%.6f\n", N, media_q);
        fprintf(saida, "Merge,%d,%.6f\n", N, media_m);
    } else {
        // Imprimir dados temporais
        printf("* Bubble Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_b);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_b);
        printf("* Insertion Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_i);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_i);
        printf("* Selection Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_s);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_s);
        printf("* Quicksort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_q);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_q);
        printf("* Merge Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", media_m);
        printf("  Desvio Padrao: %.6f us\n\n", desvio_m);
    }
}

// Imprime os dados da questão 5.
void questao5(unsigned int seed, const char* nome_busca, const char* nome_ordenacao) {
    FILE *busca = fopen(nome_busca, "w");
    FILE *ordenacao = fopen(nome_ordenacao, "w");
    
    // Alertar falhas na abertura do arquivo de busca
    if (busca) printf("  (escrevendo dados de busca em '%s')\n", nome_busca);
    else printf("  (nao foi possivel abrir o arquivo '%s')\n", nome_busca);

    // Alertar falhas na abertura do arquivo de ordenação
    if (ordenacao) printf("  (escrevendo dados de ordenacao em '%s')\n", nome_ordenacao);
    else printf("  (nao foi possivel abrir o arquivo '%s')", nome_ordenacao);

    // Imprimir cabeçalho dos CSVs
    if (busca) fprintf(busca, "Nome,Tamanho,Tempo (us)\n");
    if (ordenacao) fprintf(ordenacao, "Nome,Tamanho,Tempo (us)\n");

    for (int i = 0; i < 10; i++) {
        // Executar testes de busca (caso o arquivo esteja aberto)
        if (busca) {
            int tam = (i + 1) * 100000;
            
            printf("* Executando buscas com %d elementos...\n", tam);
            questao2(busca, seed, tam, 1);
            questao1(busca, seed, tam, 1);
            printf("  Finalizado\n");
        }

        // Executar testes de ordenação (caso o arquivo esteja aberto)
        if (ordenacao) {
            int tam = (i + 1) * 10000;
            
            printf("* Executando ordenacao com %d elementos...\n", tam);
            questao3(ordenacao, seed, tam, 1);
            printf("  Finalizado\n");
        }
    }

    // Fechar arquivos da questão 4/5
    fclose(busca);
    fclose(ordenacao);
}

int main(int argc, char **argv) {
    // Salvar a seed aleatória para re-gerar os vetores da Q1 na Q2
    unsigned int seed = time(NULL);

    int questao = 0;
    
    // Selecionar questão pela linha de comando
    if (argc > 1) sscanf(argv[1], " %d", &questao);
    if (questao < 0 || questao > 5) questao = 0;

    // Questão 1
    if (questao == 0 || questao == 1) {
        printf("Dados da Q1:\n");
        questao1(NULL, seed, 1000000, 30);
    }

    // Questão 2
    if (questao == 0 || questao == 2) {
        printf("Dados da Q2:\n");
        questao2(NULL, seed, 1000000, 30);
    }

    // Questão 3
    if (questao == 0 || questao == 3) {
        printf("Dados da Q3:\n");
        questao3(NULL, seed, 100000, 10);
    }

    // Questão 4/5
    if (questao == 0 || questao == 4 || questao == 5) {
        printf("Salvando dados da Q4/5:\n");
        questao5(seed, "busca.csv", "ordenacao.csv");
    }
}
