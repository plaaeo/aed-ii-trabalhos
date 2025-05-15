#include <stdio.h>
#include <stdlib.h>

#include "../pct.h"

#define N 20
#define ORDENADOS 10

void questao2() {
    pacote_t pacotes[N];
    abp_pct_t* raiz = NULL;

    // gerar pacotes
    for (int i = 0; i < N; i++) {
        pacotes[i].id = rand() % 1000000;

        // gerar dado a partir do ID (IDs iguais geram dados iguais)
        pacotes[i].dado = (pacotes[i].id % 26) + 97;
    }

    // ordena parcialmente os pacotes
    for (int i = 0; i < ORDENADOS; i++) {
        for (int j = i + 1; j < ORDENADOS; j++) {
            if (pacotes[j].id < pacotes[i].id) {
                pacote_t aux = pacotes[i];
                pacotes[i] = pacotes[j];
                pacotes[j] = aux;
            }
        }
    }

    // inserir os pacotes criados
    for (int i = 0; i < N; i++) {
        raiz = abp_pct_inserir(raiz, pacotes[i]);
    }

    // imprimir dados parcialmente ordenados na tela
    printf("\n# Pacotes parcialmente ordenados\n");
    printf("| ID         | Dado |\n");
    printf("|-----------:|:-----|\n");
    for (int i = 0; i < N; i++) {
        printf("| %10d | %c    |\n", pacotes[i].id, pacotes[i].dado);
    }

    // salvar dados em um arquivo
    FILE* q2txt = fopen("q2.txt", "w");
    if (q2txt) {
        printf(". Escrevendo resultado da questao 2 em 'q2.txt'\n");
    } else {
        printf("\n# Pacotes ordenados\n");
        q2txt = stdout;
    }

    // imprimir dados ordenados em arquivo
    fprintf(q2txt, "| ID         | Dado |\n");
    fprintf(q2txt, "|-----------:|:-----|\n");
    abp_pct_em_ordem(raiz, q2txt);

    if (q2txt != stdout) fclose(q2txt);
};
