#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lse.h"
#include "vetor.h"

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

/// Dados retornados de `questao1(...)`
typedef struct res_q1_t {
    double *seq_dt, *bin_dt;
    double bin_avg, bin_std;
    double seq_avg, seq_std;
} res_q1_t;

/// Dados retornados de `questao2(...)`
typedef struct res_q2_t {
    double *seq_dt;
    double seq_avg, seq_std;
} res_q2_t;

/// Dados retornados de `questao2(...)`
typedef struct res_q3_t {
    double *bub_dt, *ins_dt,
           *sel_dt, *qui_dt, *mer_dt;
    double bub_avg, bub_std;
    double ins_avg, ins_std;
    double sel_avg, sel_std;
    double qui_avg, qui_std;
    double mer_avg, mer_std;
} res_q3_t;

// Imprime os dados da questão 1
// - `seed` é a semente usada para gerar os vetores aleatórios; 
// - `N` é o tamanho dos vetores aleatórios; 
// - `I` é a quantidade de repetições de cada algorítmo de busca.
res_q1_t questao1(unsigned int seed, int N, int I) {
    srand(seed);

    double *tempos_sequencial = malloc(I * sizeof(double)),
           *tempos_binaria = malloc(I * sizeof(double));
    double soma_sequencial = 0, soma_binaria = 0;

    // Busca sequencial 30 vezes
    for (int i = 0; i < I; i++) {
        int vet_sequencial[N];
        vetor_gerar_aleatorio(vet_sequencial, N); // Gera vetor aleatorio

        // Medir busca sequencial
        int valor_busca = 1 + (rand() % N); // Gera valor aleatorio

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

    return (res_q1_t) {
        .seq_dt = tempos_sequencial,
        .bin_dt = tempos_binaria,
        .seq_avg = media_sequencial,
        .seq_std = desvio_sequencial,
        .bin_avg = media_binaria,
        .bin_std = desvio_binario,
    };
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar as listas aleatórias; 
// - `N` é o tamanho das listas aleatórias; 
// - `I` é a quantidade de repetições da busca sequencial.
res_q2_t questao2(unsigned int seed, int N, int I) {
    srand(seed);

    double *tempos = malloc(I * sizeof(double));
    double soma_tempos = 0;
    
    for (int i = 0; i < I; i++) {
        // Gerar lista com itens aleatórios
        lse_t *lse = lse_criar_aleatorio(N);

        // Gerar valor aleatorio
        int valor_busca = 1 + (rand() % N); 

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
    
    return (res_q2_t) {
        .seq_dt = tempos,
        .seq_avg = media_tempos,
        .seq_std = desvio_tempos,
    };
}

// Imprime os dados da questão 2
// - `seed` é a semente usada para gerar os vetores aleatórios; 
// - `N` é o tamanho dos vetores aleatórios; 
// - `I` é a quantidade de repetições dos algorítmos de ordenação.
res_q3_t questao3(unsigned int seed, int N, int I) {
    srand(seed);

    int original[N], copia[N];
    double *tempo_b = malloc(I * sizeof(double)),
           *tempo_i = malloc(I * sizeof(double)),
           *tempo_s = malloc(I * sizeof(double)),
           *tempo_q = malloc(I * sizeof(double)),
           *tempo_m = malloc(I * sizeof(double));
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
           media_i = soma_i / (double) I,
           media_s = soma_s / (double) I,
           media_q = soma_q / (double) I,
           media_m = soma_m / (double) I;
    
    // Calcular os desvios padrão
    double desvio_b = desvio_padrao(media_b, tempo_b, I),
           desvio_i = desvio_padrao(media_i, tempo_i, I),
           desvio_s = desvio_padrao(media_s, tempo_s, I),
           desvio_q = desvio_padrao(media_q, tempo_q, I),
           desvio_m = desvio_padrao(media_m, tempo_m, I);

    return (res_q3_t) {
        .bub_dt = tempo_b,
        .ins_dt = tempo_i,
        .sel_dt = tempo_s,
        .qui_dt = tempo_q,
        .mer_dt = tempo_m,
        .bub_avg = media_b,
        .bub_std = desvio_b,
        .ins_avg = media_i,
        .ins_std = desvio_i,
        .sel_avg = media_s,
        .sel_std = desvio_s,
        .qui_avg = media_q,
        .qui_std = desvio_q,
        .mer_avg = media_m,
        .mer_std = desvio_m,
    };
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
    if (busca) fprintf(busca, "Tamanho,Busca seq. em vetor,Busca bin. em vetor,Busca seq. em lista\n");
    if (ordenacao) fprintf(ordenacao, "Tamanho,Bubble Sort,Insertion Sort,Selection Sort,Quicksort,Merge Sort\n");

    for (int i = 0; i < 10; i++) {
        // Executar testes de busca (caso o arquivo esteja aberto)
        if (busca) {
            int tam = (i + 1) * 100000;
            
            printf("* Executando buscas com %d elementos...\n", tam);
            res_q1_t r1 = questao1(seed, tam, 1);
            res_q2_t r2 = questao2(seed, tam, 1);
            fprintf(busca, "%d,%lf,%lf,%lf\n", tam, r1.seq_avg, r1.bin_avg, r2.seq_avg);

            // Liberar vetores de tempo
            free(r1.seq_dt);
            free(r1.bin_dt);
            free(r2.seq_dt);
        }

        // Executar testes de ordenação (caso o arquivo esteja aberto)
        if (ordenacao) {
            int tam = (i + 1) * 10000;
            
            printf("* Executando ordenacao com %d elementos...\n", tam);
            res_q3_t r3 = questao3(seed, tam, 1);
            fprintf(ordenacao, "%d,%lf,%lf,%lf,%lf,%lf\n", tam, r3.bub_avg, r3.ins_avg, r3.sel_avg, r3.qui_avg, r3.mer_avg);
            
            // Liberar vetores de tempo
            free(r3.bub_dt);
            free(r3.ins_dt);
            free(r3.sel_dt);
            free(r3.qui_dt);
            free(r3.mer_dt);
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
        int N = 1000000, I = 30;
        res_q1_t res = questao1(seed, N, I);
        
        printf("Dados da Q1:\n");
        printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.seq_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.seq_std);
        printf("* Busca Binaria (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.bin_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.bin_std);

        // Salvar dados em um arquivo
        FILE *q1csv = fopen("q1.csv", "w");
        if (q1csv) {
            printf("  (escrevendo dados da questao 1 em 'q1.csv')\n");
            
            // Imprimir dados em formato csv
            fprintf(q1csv, "-,Busca seq. em vetor,Busca bin. em vetor\n");
            for (int i = 0; i < I; i++)
                fprintf(q1csv, "It. %d,%lf,%lf\n", i + 1, res.seq_dt[i], res.bin_dt[i]);

            fprintf(q1csv, "Media,%lf,%lf\n", res.seq_avg, res.bin_avg);
            fprintf(q1csv, "Desvio padrao,%lf,%lf\n", res.seq_std, res.bin_std);
            fclose(q1csv);
        }

        free(res.seq_dt);
        free(res.bin_dt);
    }

    // Questão 2
    if (questao == 0 || questao == 2) {
        int N = 1000000, I = 30;
        res_q2_t res = questao2(seed, N, I);

        printf("Dados da Q2:\n");
        printf("* Busca Sequencial (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.seq_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.seq_std);

        // Salvar dados em um arquivo
        FILE *q2csv = fopen("q2.csv", "w");
        if (q2csv) {
            printf("  (escrevendo dados da questao 2 em 'q2.csv')\n");
            
            // Imprimir dados em formato csv
            fprintf(q2csv, "-,Busca seq. em lista encadeada\n");
            for (int i = 0; i < I; i++)
                fprintf(q2csv, "It. %d,%lf\n", i + 1, res.seq_dt[i]);

            fprintf(q2csv, "Media,%lf\n", res.seq_avg);
            fprintf(q2csv, "Desvio padrao,%lf\n", res.seq_std);
            fclose(q2csv);
        }

        free(res.seq_dt);
    }

    // Questão 3
    if (questao == 0 || questao == 3) {
        int N = 100000, I = 10;
        res_q3_t res = questao3(seed, N, I);
       
        printf("Dados da Q3:\n");
        printf("* Bubble Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.bub_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.bub_std);
        printf("* Insertion Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.ins_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.ins_std);
        printf("* Selection Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.sel_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.sel_std);
        printf("* Quicksort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.qui_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.qui_std);
        printf("* Merge Sort (%d elementos, %d vezes): \n", N, I);
        printf("  Media do tempo: %.6f us\n", res.mer_avg);
        printf("  Desvio Padrao: %.6f us\n\n", res.mer_std);

        // Salvar dados em um arquivo
        FILE *q3csv = fopen("q3.csv", "w");
        if (q3csv) {
            printf("  (escrevendo dados da questao 3 em 'q3.csv')\n");
            
            // Imprimir dados em formato csv
            fprintf(q3csv, "-,Bubble,Insertion,Selection,Quick,Merge\n");
            for (int i = 0; i < I; i++)
                fprintf(q3csv, "It. %d,%lf,%lf,%lf,%lf,%lf\n", i + 1, res.bub_dt[i], res.ins_dt[i], res.sel_dt[i], res.qui_dt[i], res.mer_dt[i]);

            fprintf(q3csv, "Media,%lf,%lf,%lf,%lf,%lf\n", res.bub_avg, res.ins_avg, res.sel_avg, res.qui_avg, res.mer_avg);
            fprintf(q3csv, "Desvio padrao,%lf,%lf,%lf,%lf,%lf\n", res.bub_std, res.ins_std, res.sel_std, res.qui_std, res.mer_std);
            fclose(q3csv);
        }

        free(res.bub_dt);
        free(res.ins_dt);
        free(res.sel_dt);
        free(res.qui_dt);
        free(res.mer_dt);
    }

    // Questão 4/5
    if (questao == 0 || questao == 4 || questao == 5) {
        printf("Salvando dados da Q4/5:\n");
        questao5(seed, "busca.csv", "ordenacao.csv");
    }
}
