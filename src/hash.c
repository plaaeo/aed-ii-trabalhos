#include "hash.h"
#include <stddef.h>
#include <stdlib.h>

// Uma lista encadeada simples usada para tratar colisões
// na tabela hash.
typedef struct bucket_t {
    hash_valor_t dado;
    struct bucket_t *prox;
} bucket_t;

// Insere um dado no início e retorna a nova lista.
bucket_t *bucket_inserir(bucket_t *raiz, hash_valor_t dado) {
    bucket_t* novo = malloc(sizeof(bucket_t));
    novo->prox = raiz;
    novo->dado = dado;
    return novo;
}

// Busca a chave na lista e retorna o elemento.
hash_valor_t *bucket_buscar(bucket_t *raiz, hash_chave_t chave) {
    while (raiz) {
        if (hash_chave(raiz->dado) == chave)
            return &raiz->dado;
        raiz = raiz->prox;
    }
    return NULL;
}

// Libera todos os nós da lista.
void bucket_liberar(bucket_t *raiz) {
    while (raiz) {
        bucket_t *i = raiz;
        raiz = raiz->prox;
        free(i);
    }
}

struct hash_t {
    bucket_t **tabela;
    int tamanho;
};

// A função que distribui as chaves na tabela.
int hash_funcao(hash_t* hash, hash_chave_t chave) {
    return chave % hash->tamanho;
}

// Cria uma tabela hash com o tamanho dado.
hash_t *hash_criar(int tam) {
    hash_t *hash = malloc(sizeof(hash_t));
    hash->tabela = calloc(tam, sizeof(bucket_t*));
    hash->tamanho = tam;
    return hash;
}

// Insere o valor dado na tabela hash.
// Retorna 'true' se ocorrer uma colisão.
bool hash_inserir(hash_t *hash, hash_valor_t valor) {
    if (!hash) return false;

    int dist = hash_funcao(hash, hash_chave(valor));
    
    // Detecta colisão caso a lista não esteja vazia.
    bool colisao = hash->tabela[dist] != NULL;
    
    hash->tabela[dist] = bucket_inserir(hash->tabela[dist], valor);

    return colisao;
}

// Busca um elemento na tabela hash por chave.
// Caso o elemento exista na tabela, a função retorna 'true'
// e atualiza o ponteiro 'hash_valor_t'.
bool hash_buscar(hash_t *hash, hash_chave_t chave, hash_valor_t *valor) {
    if (!hash) return false;
    
    int dist = hash_funcao(hash, chave);
    
    // Realizar busca na lista pela chave específica
    hash_valor_t *res = bucket_buscar(hash->tabela[dist], chave);
    
    if (!res)
        return false;

    *valor = *res;
    return true;
}

// Libera a tabela hash e seus elementos.
void hash_liberar(hash_t *hash) {
    if (!hash) return;
    
    for (int i = 0; i < hash->tamanho; i++)
        bucket_liberar(hash->tabela[i]);

    free(hash->tabela);
    free(hash);
}