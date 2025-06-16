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

// insere um valor na árvore
abp_t* abp_inserir(abp_t* raiz, abp_valor_t valor) {
    if (raiz == NULL) return criar_no(valor);

    if (abp_chave(valor) <= abp_chave(raiz->valor))
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

// Preenche um vetor com todos os valores da árvore que satisfazem a dada comparação com o dado valor.
size_t abp_comparar(abp_t* raiz, double valor, int comparacao, abp_valor_t* vet, size_t tam){
    if (raiz == NULL || tam == 0) return 0;

    bool esq, dir, mid;

    // Elimina a busca nas subárvores caso nenhum dos elementos nesta subárvore
    // satisfaça a comparação.
    switch (comparacao) {
        case 0: {
            esq = mid = raiz->valor.matricula_ou_cr > valor;
            dir = 1;
            break;
        }

        case 1: {
            dir = mid = raiz->valor.matricula_ou_cr < valor;
            esq = 1;
            break;
        }

        case 2: {
            mid = raiz->valor.matricula_ou_cr >= valor;
            esq = dir = 1;
            break;
        }

        case 3: {
            dir = mid = raiz->valor.matricula_ou_cr <= valor;
            esq = 1;
            break;
        }

        default: return 0;
    }

    // Adicionar elemento no vetor caso a comparação tenha sucesso
    size_t add = 0;
    if (mid) {
        vet[add] = raiz->valor;
        add++;
    }

    // Recursivamente preencher vetor
    if (esq) add += abp_comparar(raiz->esquerda, valor, comparacao, &vet[add], tam - add);
    if (dir) add += abp_comparar(raiz->direita, valor, comparacao, &vet[add], tam - add);

    return add;
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

// libera a árvore
void abp_liberar(abp_t* raiz) {
    if (!raiz) return;
    abp_liberar(raiz->esquerda);
    abp_liberar(raiz->direita);
    free(raiz);
}
