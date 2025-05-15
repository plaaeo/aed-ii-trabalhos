#pragma once
#include <stdio.h>

// definição de pacote
typedef struct pacote_t {
    int id;
    char dado;
} pacote_t;

typedef struct abp_pct_t abp_pct_t;

// insere um valor na árvore
abp_pct_t* abp_pct_inserir(abp_pct_t* raiz, pacote_t pacote);

// salva os pacotes, em ordem, no arquivo de saida
void abp_pct_em_ordem(abp_pct_t* raiz, FILE* saida);

// retorna a altura da árvore
int abp_pct_altura(abp_pct_t* raiz);

// libera a árvore de pacotes
void abp_pct_liberar(abp_pct_t* raiz);
