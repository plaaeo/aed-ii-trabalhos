#include <stdlib.h>

#include "vetor.h"

// Gera um vetor com valores aleatórios
void vetor_gerar_aleatorio(vetor_t vet, int tam) {
    for (int i = 0; i < tam; i++) {
        vet[i] = 1 + (rand() % 1000000); // Valores aleatórios entre 1 e 1 milhão
    }
}

// Gera um vetor com valores aleatórios ordenados
void vetor_gerar_ordenado(vetor_t vet, int tam) {
    int acc = 0;
    for (int i = 0; i < tam; i++) {
        vet[i] = acc + (rand() % 3); // Valores aleatórios entre 0 e 2

        // Garante que o próximo valor sempre será >= o anterior
        if (vet[i] > acc)
            acc = vet[i];
    }
}

// Ordena o vetor
void vetor_ordenar_selection(vetor_t vet, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (vet[i] > vet[j]) {
                int aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

// Buscas
int vetor_busca_sequencial(vetor_t vet, int tam, int valor) {
    for (int i = 0; i < tam; i++) {
        if (vet[i] == valor) {
            return i; // Posição do valor
        }
    }
    return -1; // Caso não encontrar
}

int vetor_busca_binaria(vetor_t vet, int tam, int valor) {
    int x = 0, y = tam - 1;
    while (x <= y) {
        int meio = (x + y) / 2;
        if (vet[meio] == valor) {
            return meio; // Posição do valor
        } else if (vet[meio] < valor) {
            x = meio + 1;
        } else {
            y = meio - 1;
        }
    }
    return -1; // Caso não encontrar
}
