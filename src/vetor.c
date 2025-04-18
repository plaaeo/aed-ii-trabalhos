#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "vetor.h"

// Gera um vetor com valores aleatórios
void vetor_gerar_aleatorio(vetor_t vet, int tam) {
    for (int i = 0; i < tam; i++) {
        vet[i] = 1 + (rand() % tam); // Valores aleatórios entre 1 e `tam`
    }
}

// Gera um vetor com valores aleatórios ordenados
void vetor_gerar_ordenado(vetor_t vet, int tam) {
    vetor_gerar_aleatorio(vet, tam);
    vetor_ordenar_merge(vet, 0, tam);
}

/// Copia os dados do vetor `origem` pro vetor `destino`
void vetor_copiar(vetor_t origem, vetor_t destino, int tam) {
    memcpy(destino, origem, tam * sizeof(int));
}

/// Imprime os valores do vetor na saída padrão.
void vetor_imprimir(vetor_t vet, int tam, int inicio, int fim) {
    printf("[ ");

    if (inicio != 0)
        printf("..., ");

    fim = tam < fim ? tam : fim;
    for (int i = inicio; i < fim; i++) {
        printf("%d", vet[i]);

        // Printar vírgula caso ainda hajam mais elementos para imprimir
        if ((i + 1) < fim)
            printf(", ");
    }

    if (fim != tam)
        printf(", ...");

    printf(" ]\n");
};

// -- Ordenação

// Ordena o vetor usando selection sort
void vetor_ordenar_selection(vetor_t vet, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int min = i;
        for (int j = i + 1; j < tam; j++) {
            if (vet[j] < vet[min]) {
                min = j;
            }
        }
        int aux = vet[i];
        vet[i] = vet[min];
        vet[min] = aux;
    }
}

/// Ordena o vetor usando o bubble sort
void vetor_ordenar_bubble(vetor_t vet, int tam) {
    bool trocado = true;
    while(trocado) {
        trocado = false;

        for (int i = 0; i < tam - 1; i++) {
            if (vet[i] > vet[i + 1]) {
                int aux = vet[i + 1];
                vet[i + 1] = vet[i];
                vet[i] = aux;
                trocado = true;
            }
        }
    }
};

/// Ordena o vetor usando o insertion sort
void vetor_ordenar_insertion(vetor_t vet, int tam) {
    for (int i = 1; i < tam; i++) {
        int chave = vet[i];
        int j = i - 1;
        while (j >= 0 && vet[j] > chave) {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = chave;
    }
};

/// Ordena o vetor usando o quick sort
void vetor_ordenar_quick(vetor_t vet, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = vet[fim];
        int i = inicio - 1;
        for (int j = inicio; j < fim; j++) {
            if (vet[j] <= pivo) {
                i++;
                int aux = vet[i];
                vet[i] = vet[j];
                vet[j] = aux;
            }
        }
        int aux = vet[i + 1];
        vet[i + 1] = vet[fim];
        vet[fim] = aux;
        vetor_ordenar_quick(vet, inicio, i);
        vetor_ordenar_quick(vet, i + 2, fim);
    }
};

// Funções auxiliares para o Merge Sort
void merge(vetor_t vet, int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = vet[inicio + i];
    for (int j = 0; j < n2; j++)
        R[j] = vet[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            vet[k++] = L[i++];
        else
            vet[k++] = R[j++];
    }

    while (i < n1)
        vet[k++] = L[i++];
    while (j < n2)
        vet[k++] = R[j++];

    free(L);
    free(R);
}


/// Ordena o vetor usando o merge sort
void vetor_ordenar_merge(vetor_t vet, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        vetor_ordenar_merge(vet, inicio, meio);
        vetor_ordenar_merge(vet, meio + 1, fim);
        merge(vet, inicio, meio, fim);
    }
};

// -- Buscas -- 
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
