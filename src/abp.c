#include <stdio.h>
#include <stdlib.h>

#include "abp.h"

// definição do nó da árvore
struct abp_t {
  int valor;
  struct abp_t* esquerda;
  struct abp_t* direita;
};

// cria um novo nó
abp_t* criar_no(int valor) {
    abp_t* novo = (abp_t*)malloc(sizeof(abp_t));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// insere um valor na árvore
abp_t* abp_inserir(abp_t* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor <= raiz->valor)
        raiz->esquerda = abp_inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = abp_inserir(raiz->direita, valor);
    return raiz;
}

// busca um valor na árvore
abp_t* abp_buscar(abp_t* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor)
        return abp_buscar(raiz->esquerda, valor);
    else
        return abp_buscar(raiz->direita, valor);
}

// remove um valor da arvore
abp_t* abp_remover(abp_t* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = abp_remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = abp_remover(raiz->direita, valor);
    } else {
        // isso é pra caso tenha apenas um filho ou nenhum
        if (raiz->esquerda == NULL) {
            abp_t* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            abp_t* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // No com dois filhos
        abp_t* temp = raiz->direita;
        if (temp->esquerda) {
            abp_t *pai = NULL;

            do {
                pai = temp;
                temp = temp->esquerda;
            } while(temp->esquerda != NULL);

            // Remover diretamente da árvore
            pai->esquerda = NULL;
        } else {
            // A subárvore à direita é folha
            raiz->direita = NULL;
        }

        raiz->valor = temp->valor;
        free(temp);
    }
    return raiz;
}

// Pré fixado

void abp_pre_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        abp_pre_ordem(raiz->esquerda);
        abp_pre_ordem(raiz->direita);
    }
}

// fixado

void abp_em_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        abp_em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        abp_em_ordem(raiz->direita);
    }
}

// pos fixado
void abp_pos_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        abp_pos_ordem(raiz->esquerda);
        abp_pos_ordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// calcula a altura da árvore
int abp_altura(abp_t* raiz) {
    if (!raiz) return 0;

    int e = abp_altura(raiz->esquerda);
    int d = abp_altura(raiz->direita);
    return 1 + (e > d ? e : d);
}

// libera a árvore
void abp_liberar(abp_t *raiz) {
    if (!raiz) return;
    abp_liberar(raiz->esquerda);
    abp_liberar(raiz->direita);
    free(raiz);
}
