#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

#define ESQUERDA 0
#define DIREITA 1

struct avl_t {
    int val;
    int fator;
    avl_t *sub[2];
};

avl_t *avl_criar(int val) {
    avl_t *avl = malloc(sizeof(avl_t));

    if (avl) {
        avl->val = val;
        avl->fator = 0;
        avl->sub[0] = avl->sub[1] = NULL;
    }

    return avl;
};

int *avl_buscar(avl_t *no, int n) {
    if (!no) return NULL;

    if (no->val == n)
        return &no->val;
    else if (n < no->val)
        return avl_buscar(no->sub[ESQUERDA], n);
    else
        return avl_buscar(no->sub[DIREITA], n);
};

avl_t *interno_rot_dir(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->sub[ESQUERDA] = B->sub[DIREITA];
    B->sub[DIREITA] = A;
    A->fator = B->fator = 0;
    return B;
}

avl_t *interno_rot_esq(avl_t *A, avl_t *B) {
    // Trocar subarvores
    A->sub[DIREITA] = B->sub[ESQUERDA];
    B->sub[ESQUERDA] = A;
    A->fator = B->fator = 0;
    return B;
}

avl_t *interno_rotd_dir(avl_t *A, avl_t *B) {
    avl_t *aux = B->sub[ESQUERDA];

    // Rotacionar B com Aux à direita
    B->sub[ESQUERDA] = aux->sub[DIREITA];
    aux->sub[DIREITA] = B;

    // Rotacionar A com Aux à esquerda
    A->sub[DIREITA] = aux->sub[ESQUERDA];
    aux->sub[ESQUERDA] = A;

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
    avl_t *aux = B->sub[DIREITA];

    // Rotacionar B com Aux à esquerda
    B->sub[DIREITA] = aux->sub[ESQUERDA];
    aux->sub[ESQUERDA] = B;

    // Rotacionar A com Aux à direita
    A->sub[ESQUERDA] = aux->sub[DIREITA];
    aux->sub[DIREITA] = A;

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

avl_t *interno_rebalancear(avl_t *no, int d) {
    int dd = no->sub[d]->fator + 1;

    switch (dd + d) {
        // Caso em que houve inserção à esquerda da subárvore esquerda
        case 0: return interno_rot_dir(no, no->sub[d]);

        // Caso em que houve inserção à esquerda da subárvore direita
        case 1: return interno_rotd_dir(no, no->sub[d]);

        // Caso em que houve inserção à direita da subárvore esquerda
        case 2: return interno_rotd_esq(no, no->sub[d]);

        // Caso em que houve inserção à direita da subárvore direita
        case 3: return interno_rot_esq(no, no->sub[d]);
    }

    // Código inalcançável (em casos normais)
    return NULL;
}

avl_t *interno_inserir(avl_t *no, int n) {
    // Define a direção onde o nó buscado está
    int d = (n <= no->val) ? ESQUERDA : DIREITA;

    // O fb. equivalente à essa direção (-1 pra esquerda, 1 pra direita)
    int fb = (d << 1) - 1;

    // Inserir diretamente
    if (!no->sub[d]) {
        no->sub[d] = avl_criar(n);
        no->fator += fb;
        return no;
    }

    int previo = no->sub[d]->fator;
    no->sub[d] = interno_inserir(no->sub[d], n);

    // Verifica se o fator de balanceamento da subárvore
    // aumentou/diminuiu, ou seja, se a subárvore cresceu.
    if (!previo && no->sub[d]->fator) {
        if (no->fator == fb) {
            // O fb. da árvore se tornaria -2/+2
            return interno_rebalancear(no, d);
        } else {
            no->fator += fb;
        }
    }

    return no;
}

avl_t* avl_inserir(avl_t *avl, int n) {
    // Tratar inserção em árvore vazia
    if (!avl) return avl_criar(n);
    else return interno_inserir(avl, n);
};

int avl_altura(avl_t *avl) {
    int i = 0;

    // Percorrer a árvore pelo caminho mais desbalanceado
    while (avl) {
        avl = avl->sub[(avl->fator + 1) >> 1];
        i++;
    }

    return i;
}

void avl_liberar(avl_t *avl) {
    if (!avl) return;

    avl_liberar(avl->sub[ESQUERDA]);
    avl_liberar(avl->sub[DIREITA]);
    free(avl);
}
