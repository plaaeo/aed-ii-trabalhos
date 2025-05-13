#pragma once

//definição de Pacote
typedef struct Pacotes{
    int id;
    char dado;
}Pacote;

typedef struct abp_pct_t abp_pct_t;

//cria um no
abp_pct_t* pct_criar_no(Pacote pacote);

// insere um valor na árvore
abp_pct_t* pct_abp_inserir(abp_pct_t* raiz, Pacote pacote);

// busca um valor na árvore
abp_pct_t* pct_abp_buscar(abp_pct_t* raiz, int ID);

// remove um valor da arvore
abp_pct_t* pct_abp_remover(abp_pct_t* raiz, Pacote pacote);

//ordena parcialmente os pacotes pelo id
Pacote pct_ordenar_parcial_id(int tam, Pacote pacotes[tam]);

//ordena todos os pacotes por id
Pacote pct_ordenar_id(int tam, Pacote pacotes[tam]);
