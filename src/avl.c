#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

struct avl_t {
    int val;
    int fator;
    avl_t *esq;
    avl_t *dir;
};

avl_t *avl_criar(int val) {
    avl_t *avl = malloc(sizeof(avl_t));

    if (avl) {
        avl->val = val;
        avl->fator = 0;
        avl->esq = avl->dir = NULL;
    }

    return avl;
};

int *avl_buscar(avl_t **avl, int n) {
    if (!avl) return NULL;

    avl_t *no = *avl;

    if (no->val == n)
        return &no->val;
    else if (n < no->val)
        return avl_buscar(&no->esq, n);
    else
        return avl_buscar(&no->dir, n);
};

void interno_rot_dir(avl_t **raiz, avl_t *B) {
    avl_t *A = *raiz;
    avl_t *tmp = B->dir;
    B->dir = A;
    A->esq = tmp;
    *raiz = B;
    A->fator = B->fator = 0;
}

void interno_rot_esq(avl_t **raiz, avl_t *B) {
    avl_t *A = *raiz;
    avl_t *tmp = B->esq;
    B->esq = A;
    A->dir = tmp;
    *raiz = B;
    A->fator = B->fator = 0;
}

int interno_inserir(avl_t **avl, int n) {
    avl_t **sub = NULL;
    avl_t *no = *avl;

    if (n <= no->val) {
        sub = &no->esq;
        no->fator -= 1;
    } else {
        sub = &no->dir;
        no->fator += 1;
    }

    printf("fator(%d) = %d\n", no->val, no->fator);

    if (!*sub) {
        (*sub) = avl_criar(n);
        return 0;
    } else {
        interno_inserir(sub, n);

        if (no->fator == -2)
            interno_rot_dir(avl, *sub);
        else if (no->fator == 2)
            interno_rot_esq(avl, *sub);
    }
}

void avl_inserir(avl_t **avl, int n) {
    if (!avl) return;

    // Árvore vazia
    if (!*avl) {
        (*avl) = avl_criar(n);
        return;
    }

    interno_inserir(avl, n);
    return;
};

int avl_remover(avl_t **avl, int n);

int avl_altura(avl_t *avl);
