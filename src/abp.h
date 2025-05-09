#pragma once

typedef struct abp_t abp_t;

// insere um valor na árvore
abp_t* abp_inserir(abp_t* raiz, int valor);

// busca um valor na árvore
abp_t* abp_buscar(abp_t* raiz, int valor);

// remove um valor da arvore
abp_t* abp_remover(abp_t* raiz, int valor);

// Pré fixado
void abp_pre_ordem(abp_t* raiz);

// fixado
void abp_em_ordem(abp_t* raiz);

// pos fixado
void abp_pos_ordem(abp_t* raiz);

// calcula a altura da árvore
int abp_altura(abp_t* raiz);

// libera a árvore
void abp_liberar(abp_t *raiz);
