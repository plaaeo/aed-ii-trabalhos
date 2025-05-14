#include <stdio.h>
#include <stdlib.h>

#include "../pct.h"

#define N 20

// TODO: fazer lógica para repetir elementos
// TODO: ajustes nas saídas
void questao2() {
    pacote_t pacotes[N];
    abp_pct_t* raiz = NULL;

    // gerar pacotes
    for (int i = 0; i < N; i++) {
        pacotes[i].id = rand() % 10000;
        srand(pacotes[i].id);
        pacotes[i].dado = (rand() % 26) + 97;
    }

    // ordena parcialmente os pacotes
    for (int i = 0; i < N / 2; i++) {
        for (int j = i + 1; j < N / 2; j++) {
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

    // salvar dados em um arquivo
    FILE* q2csv = fopen("q2.txt", "w");
    if (q2csv) {
        printf("  (escrevendo dados da questao 2 em 'q2.csv')\n");

        // Imprimir dados em formato csv
        fprintf(q2csv, "ID,Dado\n");

        for (int i = 0; i < N; i++) {
            fprintf(q2csv, "%d,%c\n", pacotes[i].id, pacotes[i].dado);
        }
        fclose(q2csv);
    }
};
