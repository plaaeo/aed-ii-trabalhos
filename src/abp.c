#include "abp.h"

#include <stdio.h>
#include <stdlib.h>

// definição do nó da árvore
struct abp_t {
    abp_valor_t valor;
    struct abp_t* esquerda;
    struct abp_t* direita;
};

// cria um novo nó
abp_t* criar_no(abp_valor_t valor) {
    abp_t* novo = (abp_t*)malloc(sizeof(abp_t));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// cria uma abp usando um vetor ordenado
abp_t* interno_criar_por_vetor(abp_valor_t* vetor, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int idx = inicio + (fim - inicio) / 2;

    abp_t* no = criar_no(vetor[idx]);
    no->esquerda = interno_criar_por_vetor(vetor, inicio, idx - 1);
    no->direita = interno_criar_por_vetor(vetor, idx + 1, fim);
    return no;
}

// cria uma abp usando um vetor ordenado
abp_t* abp_criar_por_vetor(abp_valor_t* vetor, int tam) {
    return interno_criar_por_vetor(vetor, 0, tam);
};


// insere um valor na árvore
abp_t* abp_inserir(abp_t* raiz, abp_valor_t valor) {
    if (raiz == NULL) return criar_no(valor);

    if (abp_chave(valor) < abp_chave(raiz->valor))
        raiz->esquerda = abp_inserir(raiz->esquerda, valor);
    else if (abp_chave(valor) > abp_chave(raiz->valor))
        raiz->direita = abp_inserir(raiz->direita, valor);
    return raiz;
}

// busca um valor na árvore
bool abp_buscar(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor) {
    if (raiz == NULL) return false;
    if (chave == abp_chave(raiz->valor)) {
        if (valor) *valor = raiz->valor;

        return true;
    } else if (chave < abp_chave(raiz->valor))
        return abp_buscar(raiz->esquerda, chave, valor);
    else
        return abp_buscar(raiz->direita, chave, valor);
}

// remove um valor da arvore
abp_t* abp_remover(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor) {
    if (raiz == NULL) return NULL;

    if (chave < abp_chave(raiz->valor)) {
        raiz->esquerda = abp_remover(raiz->esquerda, chave, valor);
    } else if (chave > abp_chave(raiz->valor)) {
        raiz->direita = abp_remover(raiz->direita, chave, valor);
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
            abp_t* pai = NULL;

            do {
                pai = temp;
                temp = temp->esquerda;
            } while (temp->esquerda != NULL);

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
        abp_valor_imprime(raiz->valor);
        printf(" ");
        abp_pre_ordem(raiz->esquerda);
        abp_pre_ordem(raiz->direita);
    }
}

// fixado

void abp_em_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        abp_em_ordem(raiz->esquerda);
        abp_valor_imprime(raiz->valor);
        printf(" ");
        abp_em_ordem(raiz->direita);
    }
}

// pos fixado
void abp_pos_ordem(abp_t* raiz) {
    if (raiz != NULL) {
        abp_pos_ordem(raiz->esquerda);
        abp_pos_ordem(raiz->direita);
        abp_valor_imprime(raiz->valor);
        printf(" ");
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
void abp_liberar(abp_t* raiz) {
    if (!raiz) return;
    abp_liberar(raiz->esquerda);
    abp_liberar(raiz->direita);
    free(raiz);
}
