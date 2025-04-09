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
void gerar_aleatorio(int vet[], int tam);
///Ordena o vetor
void ordenar(int vet[], int tam);

///Buscas
///Faz uma Busca Sequencial pelo vetor
int busca_sequencial(int vet[], int tam, int valor);
///Faz uma Busca Binaria pelo vetor
int busca_binaria(int vet[], int tam, int valor);

