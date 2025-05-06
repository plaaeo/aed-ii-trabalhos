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

avl_t *interno_rot_dir(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->esq = B->dir;
    B->dir = A;
    A->fator = B->fator = 0;
    return B;
}

avl_t *interno_rot_esq(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->dir = B->esq;
    B->esq = A;
    A->fator = B->fator = 0;
    return B;
}

avl_t *interno_rotd_dir(avl_t *A, avl_t *B) {
    avl_t *aux = B->esq;

    // Rotacionar B com Aux à direita
    interno_rot_dir(B, aux);

    // Rotacionar A com Aux à esquerda
    return interno_rot_esq(A, aux);

    // TODO: ajustar os fatores de balanceamento
}

avl_t *interno_rotd_esq(avl_t *A, avl_t *B) {
    avl_t *aux = B->dir;

    // Rotacionar B com Aux à esquerda
    interno_rot_esq(B, aux);

    // Rotacionar A com Aux à direita
    return interno_rot_dir(A, aux);

    // TODO: ajustar os fatores de balanceamento
}

avl_t *interno_inserir(avl_t *no, int n) {
    if (n <= no->val) {
        // O valor a ser inserido está na subarvore à esquerda.
        if (!no->esq) {
            no->esq = avl_criar(n);
            no->fator -= 1;
            return no;
        }

        int previo = no->esq->fator;
        no->esq = interno_inserir(no->esq, n);

        // O fator de balanceamento da subárvore esq. aumentou/diminuiu,
        // ou seja, a subárvore cresceu.
        if (no->esq->fator && previo != no->esq->fator) {
            if (no->fator == 0) {
                // Não é realizada rotação neste nó, logo, seu fator muda,
                // pois a altura da subárvore mudou!
                no->fator -= 1;
            } else if (no->esq->fator < 0) {
                // 'no' é a subárvore mais próxima do valor inserido
                // com fator < 0.
                return interno_rot_dir(no, no->esq);
            } else if (no->esq->fator > 0) {
                // 'no' é a subárvore mais próxima do valor inserido
                // com fator > 0.
                return interno_rotd_esq(no, no->esq);
            }
        }
    } else {
        // O valor a ser inserido está na subarvore à direita.
        if (!no->dir) {
            no->dir = avl_criar(n);
            no->fator += 1;
            return no;
        }

        int previo = no->dir->fator;
        no->dir = interno_inserir(no->dir, n);

        // O fator de balanceamento da subárvore dir. aumentou/diminuiu,
        // ou seja, a subárvore cresceu.
        if (no->dir->fator && previo != no->dir->fator) {
            if (no->fator == 0) {
                // Não é realizada rotação neste nó, logo, seu fator muda,
                // pois a altura da subárvore mudou!
                no->fator += 1;
            } else if (no->dir->fator < 0) {
                // 'no' é a subárvore mais próxima do valor inserido
                // com fator < 0.
                return interno_rotd_dir(no, no->dir);
            } else if (no->dir->fator > 0) {
                // 'no' é a subárvore mais próxima do valor inserido
                // com fator > 0.
                return interno_rot_esq(no, no->dir);
            }
        }
    }

    return no;
}

void avl_inserir(avl_t **avl, int n) {
    if (!avl) return;

    // Árvore vazia
    if (!*avl) {
        (*avl) = avl_criar(n);
        return;
    }

    *avl = interno_inserir(*avl, n);
    return;
};

int avl_remover(avl_t **avl, int n);

int avl_altura(avl_t *avl);
