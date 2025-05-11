#include <stdio.h>
#include "vetor.h"
#include "abp.h"

int main() {
    int tam = 20;
    vetor_t vet = vetor_criar(tam);
    vetor_gerar_aleatorio(vet, tam);

    printf("Vetor gerado:\n");
    vetor_imprimir(vet, tam, 0, tam - 1);

    abp_t *abp = abp_criar();
    for (int i = 0; i < tam; i++) {
        abp_inserir(abp, vet[i]);
    }

    printf("\nPré-ordem:\n");
    abp_imprimir_pre_ordem(abp);

    printf("\nEm ordem:\n");
    abp_imprimir_em_ordem(abp);

    printf("\nPós-ordem:\n");
    abp_imprimir_pos_ordem(abp);

    vetor_liberar(vet);
    abp_liberar(abp);
    return 0;
}
