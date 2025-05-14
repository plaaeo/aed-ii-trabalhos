#pragma once

// definição de pacote
typedef struct pacote_t {
    int id;
    char dado;
} pacote_t;

typedef struct abp_pct_t abp_pct_t;

// insere um valor na árvore
abp_pct_t* abp_pct_inserir(abp_pct_t* raiz, pacote_t pacote);