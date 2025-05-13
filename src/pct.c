#include <stdio.h>
#include <stdlib.h>

#include "pct.h"

//definição do nó na árvore
struct abp_pct_t {
  Pacote pacote;
  struct abp_pct_t* esquerda;
  struct abp_pct_t* direita;
};

//cria um novo nó
abp_pct_t* pct_criar_no(Pacote pacote) {
    abp_pct_t* novo = (abp_pct_t*)malloc(sizeof(abp_pct_t));
    novo->pacote = pacote;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// insere um valor na árvore
abp_pct_t* pct_abp_inserir(abp_pct_t* raiz, Pacote pacote) {
    if (raiz == NULL) return pct_criar_no(pacote);
    if (pacote.id < raiz->pacote.id)
        raiz->esquerda = pct_abp_inserir(raiz->esquerda, pacote);
    else if (pacote.id > raiz->pacote.id)
        raiz->direita = pct_abp_inserir(raiz->direita, pacote);
    return raiz;
}

// busca um valor na árvore
abp_pct_t* pct_abp_buscar(abp_pct_t* raiz, int ID) {
    if (raiz == NULL || raiz->pacote.id == ID) return raiz;
    if (ID < raiz->pacote.id)
        return pct_abp_buscar(raiz->esquerda, ID);
    else
        return pct_abp_buscar(raiz->direita, ID);
}

// remove um valor da arvore
abp_pct_t* pct_abp_remover(abp_pct_t* raiz, Pacote pacote) {
    if (raiz == NULL) return NULL;

    if (pacote.id < raiz->pacote.id) {
        raiz->esquerda = pct_abp_remover(raiz->esquerda, pacote);
    } else if (pacote.id > raiz->pacote.id) {
        raiz->direita = pct_abp_remover(raiz->direita, pacote);
    } else {
        // isso é pra caso tenha apenas um filho ou nenhum
        if (raiz->esquerda == NULL) {
            abp_pct_t* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            abp_pct_t* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        // No com dois filhos
        abp_pct_t* temp = raiz->direita;
        if (temp->esquerda) {
            abp_pct_t *pai = NULL;

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

        free(temp);
    }
    return raiz;
}

//ordena parcialmente os pacotes pelo id
Pacote pct_ordenar_parcial_id(int tam, Pacote pacotes[tam]){
    int i, j, aux;
    for(i=0; i<(tam/2) - 1; i++){
        for(j=1; j<tam/2; j++){
            if(pacotes[j].id < pacotes[i].id){
                aux = pacotes[i].id;
                pacotes[i].id = pacotes[j].id;
                pacotes[j].id = aux;
            }
        }
    }
}

//ordena todos os pacotes pelo id
Pacote pct_ordenar_id(int tam, Pacote pacotes[tam]){
    int i, j, aux;
    for(i=0; i<tam-1; i++){
        for(j=1; j<tam; j++){
            if(pacotes[j].id < pacotes[i].id){
                aux = pacotes[i].id;
                pacotes[i].id = pacotes[j].id;
                pacotes[j].id = aux;
            }
        }
    }
}
