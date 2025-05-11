#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vetor.h"
#include "abp.h"

int main() {
    srand(time(NULL));

    int tam = 20;
    vetor_t vet = vetor_criar(tam);
    vetor_gerar_aleatorio(vet, tam);

    printf("Vetor gerado:\n");
    vetor_imprimir(vet, tam, 0, tam);

    abp_t *abp = abp_criar();

    for (int i = 0; i < tam; i++) {
        abp_inserir(abp, vet[i]);
    }

    printf("\nPré-fixado: ");
    abp_imprimir_pre_ordem(abp);

    printf("Em ordem: ");
    abp_imprimir_em_ordem(abp);

    printf("Pós-ordem: ");
    abp_imprimir_pos_ordem(abp);

    vetor_liberar(vet);
    abp_liberar(abp);

    return 0;
}
