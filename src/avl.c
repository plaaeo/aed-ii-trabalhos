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
    B->esq = aux->dir;
    aux->dir = B;

    // Rotacionar A com Aux à esquerda
    A->dir = aux->esq;
    aux->esq = A;

    // Suponha que
    // - 'A' (fb. +2) tenha as subárvores [alpha, B]
    // - 'B' (fb. -1) tenha as subárvores [C, beta]
    // - 'C' (fb. ??) tenha as subárvores [gamma, theta] (note que C = aux)
    // Sabemos, então, que
    // - h(C)     = 1 + max { h(gamma), h(theta) }
    // - h(beta)  = h(C) - 1  , por causa do fb. de 'B'
    // - h(alpha) = h(C) - 1  , por causa do fb. de 'A'
    // Logo
    // - h(alpha) = h(beta) = max { h(gamma), h(theta) }
    // Concluimos que
    // - 'A', com as subárvores [alpha, gamma], ficará com o fb.
    //   igual a fb(A) = min { -fb(C), 0 }, pois:
    //   | se fb(C) > 0, h(theta) > h(gamma), mas h(alpha) = h(theta).
    //   | caso contrário, h(alpha) = h(gamma), logo fb(A) = 0.
    //
    // - 'B', com as subárvores [theta, beta], ficará com o fb.
    //   igual = fb(B) = max { -fb(C), 0 }, pois:
    //   | se fb(C) < 0, h(gamma) > h(theta), mas h(beta) = h(gamma).
    //   | caso contrário, h(beta) = h(theta), logo fb(B) = 0.
    //
    // - 'C' terá fb. de zero, pois h(A) = h(alpha) = h(beta) = h(B).
    A->fator = -(aux->fator > 0);
    B->fator = (aux->fator < 0);
    aux->fator = 0;
    return aux;
}

avl_t *interno_rotd_esq(avl_t *A, avl_t *B) {
    avl_t *aux = B->dir;

    // Rotacionar B com Aux à esquerda
    B->dir = aux->esq;
    aux->esq = B;

    // Rotacionar A com Aux à direita
    A->esq = aux->dir;
    aux->dir = A;

    // (Leia a explicação dentro da função `interno_rotd_dir` primeiro!)
    // Neste caso, as suposições iniciais ainda valem, porém:
    // - 'B' terá as subárvores [beta, gamma], logo seu fb. será igual
    //   o cálculo do fb. de 'A' na função `interno_rotd_dir`;
    // - 'A' terá as subárvores [theta, alpha], logo seu fb. será igual
    //   o cálculo do fb. de 'B' na função `interno_rotd_dir`;
    // - 'C' ainda terá fb. zero.
    A->fator = (aux->fator < 0);
    B->fator = -(aux->fator > 0);
    aux->fator = 0;
    return aux;
}

avl_t *interno_inserir(avl_t *no, int n) {
    // Buscar local de inserção de 'n'
    if (n <= no->val) {
        if (!no->esq) {
            no->esq = avl_criar(n);
            no->fator -= 1;
            return no;
        }

        int previo = no->esq->fator;
        no->esq = interno_inserir(no->esq, n);

        // Verifica se o fator de balanceamento da subárvore
        // esq. aumentou/diminuiu, ou seja, se a subárvore cresceu.
        if (no->esq->fator && !previo) {
            if (no->fator >= 0) {
                // A subárvore 'no' foi rebalanceada/desbalanceou para a esq.
                no->fator -= 1;
            }
            // Daqui em diante, o fb de 'no' se tornaria -2, logo,
            // precisamos decidir como rebalancear a árvore.
            else if (no->esq->fator < 0) {
                // A subárvore à esq. (B) tem fb = -1, logo,
                // usaremos uma rotação simples à direita.
                return interno_rot_dir(no, no->esq);
            } else if (no->esq->fator > 0) {
                // A subárvore à esq. (B) tem fb = 1, logo,
                // usaremos uma rotação dupla à esquerda.
                return interno_rotd_esq(no, no->esq);
            }
        }
    } else {
        if (!no->dir) {
            no->dir = avl_criar(n);
            no->fator += 1;
            return no;
        }

        int previo = no->dir->fator;
        no->dir = interno_inserir(no->dir, n);

        // Verifica se o fator de balanceamento da subárvore
        // dir. aumentou/diminuiu, ou seja, se a subárvore cresceu.
        if (no->dir->fator && !previo) {
            if (no->fator <= 0) {
                // A subárvore 'no' foi rebalanceada/desbalanceou para a dir.
                no->fator += 1;
            }
            // Daqui em diante, o fb de 'no' se tornaria 2, logo,
            // precisamos decidir como rebalancear a árvore.
            else if (no->dir->fator < 0) {
                // A subárvore à dir. (B) tem fb = -1, logo,
                // usaremos uma rotação dupla à direita.
                return interno_rotd_dir(no, no->dir);
            } else if (no->dir->fator > 0) {
                // A subárvore à dir. (B) tem fb = 1, logo,
                // usaremos uma rotação simples à esquerda.
                return interno_rot_esq(no, no->dir);
            }
        }
    }

    return no;
}

void avl_inserir(avl_t **avl, int n) {
    if (!avl) return;

    // Tratar inserção em árvore vazia
    if (!*avl) (*avl) = avl_criar(n);
    else *avl = interno_inserir(*avl, n);
    return;
};

avl_t *interno_remover(avl_t *no, int n) {
    // Buscar valor a ser removido
    if (n <= no->val) {
        return interno_remover(no->esq, n);
    } else {
        return interno_remover(no->dir, n);
    }
};

int avl_remover(avl_t **avl, int n);

int avl_altura(avl_t *avl);
