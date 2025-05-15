#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../vetor.h"
#include "../abp.h"

// Tamanho do vetor de exemplo
#define TAM 20

int questao1() {
    vetor_t vet = malloc(sizeof(int) * TAM);

    srand(time(NULL));

    printf("* Questao 1\n");

    // Preencher o vetor com valores (apenas exemplo)
    vetor_gerar_aleatorio(vet, TAM);

    // Criar a árvore binária de pesquisa (ABP)
    abp_t *abp = NULL;

    // Inserir elementos na árvore
    for (int i = 0; i < TAM; i++) {
        // Supondo que abp_inserir insira elementos na árvore
        abp = abp_inserir(abp, vet[i]);
    }

    // Imprimir a árvore em diferentes ordens
    printf(". Árvore em pré-ordem:\n  ");
    abp_pre_ordem(abp);
    printf("\n. Árvore em ordem:\n  ");
    abp_em_ordem(abp);
    printf("\n. Árvore em pós-ordem:\n  ");
    abp_pos_ordem(abp);
    printf("\n");

    // Liberar recursos
    abp_liberar(abp);
    free(vet);

    return 0;
}
