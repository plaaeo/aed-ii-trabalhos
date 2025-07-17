#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "grafo.h"
#include "questoes.h"
#include "util.h"

/// Imprime a tabela de tempos para cada grafo em um dos algoritmos usados.
void imprimir_tabela(size_t tamanhos[], float graus[], clock_t tempos[],
                     size_t n_tamanhos, size_t n_graus) {
    // Imprimir cabeçalho da tabela
    printf("| Conectividade |");
    for (size_t t = 0; t < n_tamanhos; t++) {
        printf(" Tamanho %4lu |", tamanhos[t]);
    }

    printf("\n|--------------:|");
    for (size_t t = 0; t < n_tamanhos; t++) {
        printf(":-------------|");
    }

    // Imprimir linhas da tabela
    for (size_t g = 0; g < n_graus; g++) {
        printf("\n|       %6.2f%% |", graus[g] * 100);
        for (size_t t = 0; t < n_tamanhos; t++) {
            size_t idx = (t * n_graus) + g;
            printf(" %12.4lf |", (double)(tempos[idx]) / 1000.0);
        }
    }

    printf("\n");
}

int main() {
    srand(time(NULL));

    // Limpar a tela
    printf("\033[2J\033[H");

    printf("=== AED2 - Trabalho 4 - Grafos ===\n\n");
    printf("> Alunos: \n");
    printf(". Paulo Victor Fernandes de Melo\n");
    printf(". João Luiz Rodrigues da Silva\n");
    printf(". Rebecca Aimée Lima de Lima\n");
    printf(". Beatriz Jacaúna Martins\n\n");
    printf(
        "* Para apresentar os grafos, serão impressos listas de pares de "
        "adjacência.\n");
    printf(
        "* Para visualizar os grafos, é recomendado que copie as "
        "listas e use-as em https://csacademy.com/app/graph_editor/\n\n");

    // Abrir arquivo da q2 e q3
    FILE *q2q3 = fopen("q2q3.txt", "w");
    if (q2q3) {
        printf(
            "* Para as questões 2 e 3, pelo tamanho excessivo dos grafos, as "
            "listas de adjacência (exceto as de 100%% de conectividade) serão "
            "salvas em 'q2q3.txt'.\n");
    } else {
        printf(
            "! Os grafos das questões 2 e 3 não serão salvos, pois não foi "
            "possível abrir o arquivo 'q2q3.txt'.\n");
        printf("! Erro: %s\n", strerror(errno));
    }

    aguardar_entrada();

    // Executar questão 1
    questao1();

    // Todos os possíveis tamanhos para os grafos
    size_t tamanhos[] = {16, 64, 512, 1024, 2048, 4096};

    // Todos os possíveis graus de conectividade dos grafos
    float graus[] = {0.10, 0.25, 0.50, 0.75, 1.00};

    // Hack para definir n_tamanhos e n_graus como 'constantes'
    enum {
        n_tamanhos = sizeof(tamanhos) / sizeof(size_t),
        n_graus = sizeof(graus) / sizeof(float)
    };

    // Durações de execução para cada grafo
    clock_t tempos_bfs[n_tamanhos * n_graus] = {};
    clock_t tempos_dfs[n_tamanhos * n_graus] = {};

    for (size_t t = 0; t < n_tamanhos; t++) {
        for (size_t g = 0; g < n_graus; g++) {
            size_t idx = (t * n_graus) + g;

            grafo_t *grafo = grafo_criar_conexo(tamanhos[t], graus[g]);

            // Imprimir todos os grafos (menos os 100% conexos)
            if (graus[g] != 1.00 && q2q3) {
                // Imprimir nome do grafo
                fprintf(
                    q2q3,
                    "- Grafo de tamanho %lu com %.02f%% de conectividade -\n",
                    tamanhos[t], graus[g] * 100);

                grafo_imprimir_arestas(grafo, q2q3);
            }

            // Imprimir grafo para verificação posterior
            printf("=== QUESTÃO 2 e 3 - BFS e DFS ===\n\n");
            printf(
                "--- Grafo de tamanho %lu com %.02f%% de "
                "conectividade ---\n\n",
                tamanhos[t], graus[g] * 100);

            size_t origem = rand() % tamanhos[t];
            printf("> Origem escolhida para DFS/BFS: %lu\n", origem);

            // Executar e medir questões
            tempos_bfs[idx] = questao2(grafo, origem);
            tempos_dfs[idx] = questao3(grafo, origem);

            // Limpar memória
            grafo_free(grafo);
            printf("\n");
            aguardar_entrada();
        }
    }

    fclose(q2q3);

    // Imprimir tabelas da questão 2 e 3
    printf("=== QUESTÃO 2 e 3 - BFS e DFS ===\n\n");
    printf("\n--- Tempos de execução da BFS ---\n");
    imprimir_tabela(tamanhos, graus, tempos_bfs, n_tamanhos, n_graus);
    printf("\n--- Tempos de execução da DFS ---\n");
    imprimir_tabela(tamanhos, graus, tempos_dfs, n_tamanhos, n_graus);
    aguardar_entrada();

    // Executar a questão 4 e 5
    questao4();
    questao5();
}
