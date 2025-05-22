#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

struct avl_t {
    avl_t *esq;
    avl_t *dir;
    avl_valor_t val;
    int altura;
};

avl_t *avl_criar(avl_valor_t val) {
    avl_t *avl = malloc(sizeof(avl_t));

    if (avl) {
        avl->val = val;
        avl->altura = 1;
        avl->esq = avl->dir = NULL;
    }

    return avl;
};

bool avl_buscar(const avl_t *no, avl_chave_t n, avl_valor_t *valor) {
    if (!no) return false;

    if (n == avl_chave(no->val)) {
        if (valor) *valor = no->val;

        return true;
    } else if (n < avl_chave(no->val))
        return avl_buscar(no->esq, n, valor);
    else
        return avl_buscar(no->dir, n, valor);
};

int interno_altura(const avl_t *no) {
    return no ? no->altura : 0;
}

int interno_fator(const avl_t *no) {
    return no ? interno_altura(no->dir) - interno_altura(no->esq) : 0;
}

void interno_ajustar_altura(avl_t *no) {
    int esq = interno_altura(no->esq);
    int dir = interno_altura(no->dir);

    // Definir como 1 + altura da maior subárvore
    no->altura = 1 + (esq > dir ? esq : dir);
}

avl_t *interno_rot_dir(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->esq = B->dir;
    B->dir = A;

    interno_ajustar_altura(A);
    interno_ajustar_altura(B);
    return B;
}

avl_t *interno_rot_esq(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->dir = B->esq;
    B->esq = A;

    interno_ajustar_altura(A);
    interno_ajustar_altura(B);
    return B;
}

avl_t *interno_rotd_esq(avl_t *A, avl_t *B) {
    avl_t *aux = B->esq;

    // Rotacionar B com Aux à direita
    B = interno_rot_dir(B, aux);

    // Rotacionar A com Aux à esquerda
    A = interno_rot_esq(A, aux);
    return aux;
}

avl_t *interno_rotd_dir(avl_t *A, avl_t *B) {
    avl_t *aux = B->dir;

    // Rotacionar B com Aux à esquerda
    B = interno_rot_esq(B, aux);

    // Rotacionar A com Aux à direita
    A = interno_rot_dir(A, aux);
    return aux;
}

avl_t *interno_inserir(avl_t *no, avl_valor_t n) {
    if (!no) {
        return avl_criar(n);
    }

    // Ignora a inserção de elementos repetidos
    if (avl_chave(n) == avl_chave(no->val)) return no;

    // Buscar local de inserção
    int fb_filho = 0;
    if (avl_chave(n) < avl_chave(no->val)) {
        no->esq = interno_inserir(no->esq, n);
        fb_filho = interno_fator(no->esq);
    } else {
        no->dir = interno_inserir(no->dir, n);
        fb_filho = interno_fator(no->dir);
    }

    // Ajustar nova altura após inserção
    interno_ajustar_altura(no);

    // Continuar caso a árvore permaneça balanceada
    int fb = interno_fator(no);
    if (fb >= -1 && fb <= 1) return no;

    int cond = (fb + 2) + (fb_filho + 1);
    switch (cond / 2) {
        // Caso em que houve inserção à esquerda da subárvore esquerda
        case 0:
            return interno_rot_dir(no, no->esq);

        // Caso em que houve inserção à direita da subárvore esquerda
        case 1:
            return interno_rotd_dir(no, no->esq);

        // Caso em que houve inserção à esquerda da subárvore direita
        case 2:
            return interno_rotd_esq(no, no->dir);

        // Caso em que houve inserção à direita da subárvore direita
        case 3:
            return interno_rot_esq(no, no->dir);
    }

    return no;
}

avl_t *avl_inserir(avl_t *avl, avl_valor_t n) {
    return interno_inserir(avl, n);
};

int avl_altura(const avl_t *avl) {
    return avl->altura;
}

void avl_liberar(avl_t *avl) {
    if (!avl) return;

    avl_liberar(avl->esq);
    avl_liberar(avl->dir);
    free(avl);
}
