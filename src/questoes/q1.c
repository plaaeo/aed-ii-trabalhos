#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "abp.h"

int questao1() {
    int tam = 20;  // Tamanho do vetor de exemplo

    // Criar vetor
    int vet[tam];
    
    // Preencher o vetor com valores (apenas exemplo)
    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;  // Valores de 1 a 10
    }

    // Criar a árvore binária de pesquisa (ABP)
    abp_t *abp = NULL;

    // Inserir elementos na árvore
    for (int i = 0; i < tam; i++) {
        abp = abp_inserir(abp, vet[i]);  // Supondo que abp_inserir insira elementos na árvore
    }

    // Imprimir a árvore em diferentes ordens
    printf("Árvore em pré-ordem:\n");
    abp_pre_ordem(abp);
    printf("\n");
    printf("\nÁrvore em ordem:\n");
    abp_em_ordem(abp);
    printf("\n");
    printf("\nÁrvore em pós-ordem:\n");
    abp_pos_ordem(abp);
    printf("\n");

    // Liberar recursos
    abp_liberar(abp);

    return 0;
}
