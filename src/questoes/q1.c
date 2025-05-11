#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"
#include "abp.h"

int main() {
    int tam = 10;  // Tamanho do vetor de exemplo

    // Criar vetor
    vetor_t vet = vetor_criar(tam);
    
    // Preencher o vetor com valores (apenas exemplo)
    for (int i = 0; i < tam; i++) {
        vet[i] = i + 1;  // Valores de 1 a 10
    }

    // Criar a árvore binária de pesquisa (ABP)
    abp_t *abp = abp_criar();

    // Inserir elementos na árvore
    for (int i = 0; i < tam; i++) {
        abp_inserir(abp, vet[i]);  // Supondo que abp_inserir insira elementos na árvore
    }

    // Imprimir a árvore em diferentes ordens
    printf("Árvore em pré-ordem:\n");
    abp_imprimir_pre_ordem(abp);

    printf("\nÁrvore em ordem:\n");
    abp_imprimir_em_ordem(abp);

    printf("\nÁrvore em pós-ordem:\n");
    abp_imprimir_pos_ordem(abp);

    // Liberar recursos
    abp_liberar(abp);
    vetor_liberar(vet);

    return 0;
}
