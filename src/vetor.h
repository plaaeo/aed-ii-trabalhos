#pragma once
#include <stddef.h>

/// TAD para um vetor de inteiros.
typedef int vetor_t[];

/// Gera um vetor com valores aleatórios
void vetor_gerar_aleatorio(vetor_t vet, int tam);

/// Gera um vetor com valores ordenados aleatórios
void vetor_gerar_ordenado(vetor_t vet, int tam);

/// Copia os dados do vetor `origem` pro vetor `destino`
void vetor_copiar(vetor_t origem, vetor_t destino, int tam);

/// Imprime os valores do vetor na saída padrão.
void vetor_imprimir(vetor_t vet, int tam, int inicio, int fim);

/// -- Ordenação --

/// Ordena o vetor usando o selection sort
void vetor_ordenar_selection(vetor_t vet, int tam);

/// Ordena o vetor usando o bubble sort
void vetor_ordenar_bubble(vetor_t vet, int tam);

/// Ordena o vetor usando o insertion sort
void vetor_ordenar_insertion(vetor_t vet, int tam);

/// Ordena o vetor usando o quick sort
void vetor_ordenar_quick(vetor_t vet, int inicio, int fim);

/// Ordena o vetor usando o merge sort
void vetor_ordenar_merge(vetor_t vet, int inicio, int fim);

/// -- Buscas --

/// Faz uma Busca Sequencial pelo vetor
int vetor_busca_sequencial(vetor_t vet, int tam, int valor);

/// Faz uma Busca Binaria pelo vetor
int vetor_busca_binaria(vetor_t vet, int tam, int valor);