#pragma once
#include <stddef.h>

/// TAD para um vetor de inteiros.
typedef struct vetor_t {
    int* vetor;
    size_t tamanho;
} vetor_t;

/// ...
/// Defina aqui as funções para usar o TAD "vetor_t"

///Gera um vetor com valores aleatórios
void *gerar_aleatorio(int vet[], int tam)
///Ordenar vetor
void ordenar(int vet[], int tam)
