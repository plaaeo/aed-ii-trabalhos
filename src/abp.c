#include <stdio.h>
#include <stdlib.h>

// definição do nó da árvore
typedef struct abp_t {
    int valor;
    struct abp_t* esquerda;
    struct abp_t* direita;
} abp_t;

// cria um novo nó
abp_t* criar_no(int valor) {
    abp_t* novo = (abp_t*)malloc(sizeof(abp_t));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// insere um valor na árvore
abp_t* inserir(abp_t* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor <= raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

// busca um valor na árvore
abp_t* buscar(abp_t* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor)
        return buscar(raiz->esquerda, valor);
    else
        return buscar(raiz->direita, valor);
}

// remove um valor da arvore
abp_t* remover(abp_t* raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
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

void pre_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esquerda);
        pre_ordem(raiz->direita);
    }
}

// fixado

void em_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        em_ordem(raiz->direita);
    }
}

// pos fixado
void pos_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esquerda);
        pos_ordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}
