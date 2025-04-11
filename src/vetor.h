#pragma once
#include <stddef.h>

/// TAD para um vetor de inteiros.
typedef int vetor_t[];

/// Gera um vetor com valores aleatórios
void vetor_gerar_aleatorio(vetor_t vet, int tam);

/// Gera um vetor com valores ordenados aleatórios
void vetor_gerar_ordenado(vetor_t vet, int tam);

/// -- Ordenação --

/// Ordena o vetor usando o selection sort
void vetor_ordenar_selection(vetor_t vet, int tam);

/// -- Buscas --

/// Faz uma Busca Sequencial pelo vetor
int vetor_busca_sequencial(vetor_t vet, int tam, int valor);

/// Faz uma Busca Binaria pelo vetor
int vetor_busca_binaria(vetor_t vet, int tam, int valor);