#include "pct.h"

#include <stdio.h>
#include <stdlib.h>

// definição do nó na árvore
struct abp_pct_t {
    pacote_t pacote;
    struct abp_pct_t* esquerda;
    struct abp_pct_t* direita;
};

// cria um novo nó
abp_pct_t* pct_criar_no(pacote_t pacote) {
    abp_pct_t* novo = (abp_pct_t*)malloc(sizeof(abp_pct_t));
    novo->pacote = pacote;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// insere um valor na árvore
abp_pct_t* abp_pct_inserir(abp_pct_t* raiz, pacote_t pacote) {
    if (raiz == NULL) return pct_criar_no(pacote);
    if (pacote.id < raiz->pacote.id)
        raiz->esquerda = abp_pct_inserir(raiz->esquerda, pacote);
    else if (pacote.id > raiz->pacote.id)
        raiz->direita = abp_pct_inserir(raiz->direita, pacote);
    return raiz;
}

// salva os pacotes, em ordem, no arquivo de saida
void abp_pct_em_ordem(abp_pct_t* raiz, FILE* saida) {
    if (!raiz) return;

    abp_pct_em_ordem(raiz->esquerda, saida);
    fprintf(saida, "| %10d | %c    |\n", raiz->pacote.id, raiz->pacote.dado);
    abp_pct_em_ordem(raiz->direita, saida);
}

// calcula a altura da árvore
int abp_pct_altura(abp_pct_t* raiz) {
    if (!raiz) return 0;

    int e = abp_pct_altura(raiz->esquerda);
    int d = abp_pct_altura(raiz->direita);
    return 1 + (e > d ? e : d);
}

// libera a árvore de pacotes
void abp_pct_liberar(abp_pct_t *raiz) {
    if (!raiz) return;
    abp_pct_liberar(raiz->esquerda);
    abp_pct_liberar(raiz->direita);
    free(raiz);
}
