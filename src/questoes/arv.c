#include <stdio.h>
#include <stdlib.h>

// definição do nó da árvore    
typedef struct No{
    int valor;
    struct No* esquerda;
    struct No* direita;
}No;

//cria um novo nó
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// insere um valor na árvore
No* inserir(No* raiz, int valor){
    if (raiz == NULL)
        return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if(valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
        return raiz;
}

// busca um valor na árvore
No* buscar(No* raiz, int valor){
    if (raiz == NULL || raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscar(raiz->esquerda, valor);
    else
        return buscar(raiz->direita, valor);

}

//Encontra o menor valor da ávore (fdssssssss)
No* minimo(No* raiz) {
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

//remove um valor da arvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL)
        return NULL;

    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    }else if(valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    }else {
        //isso é pra caso tenha apenas um filho ou nenhum
        if (raiz->esquerda == NULL){
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        }else if (raiz->direita == NULL){
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        //No com dois filhos
        No* temp = minimo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;

}

//Pré fixado

void pre_ordem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esquerda);
        pre_ordem(raiz->direita);
    }
}

//fixado

void em_ordem(No* raiz) {
    if (raiz != NULL) {
        em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        em_ordem(raiz->direita);
    }
}

//pos fixado
void pos_ordem(No* raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esquerda);
        pos_ordem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}