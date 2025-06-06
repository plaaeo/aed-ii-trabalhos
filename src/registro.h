#pragma once

// O aluno completo armazenado no arquivo.
typedef struct aluno_t {
    int matricula;
    char nome[100];
    char email[100];
    char cidade[30];
    int ano_ingresso;
    char curso[6];
    float coeficiente;
} aluno_t;

// O registro a ser usado na ABP. Dependendo do índice,
// a variável 'matricula_ou_cr' pode ser a matrícula do aluno
// (para o índice de busca por igualdade), ou o CR do aluno
// (para o índice de busca por comparação >, <=, etc)
typedef struct registro_t {
    double matricula_ou_cr;

    // Posição do aluno completo no arquivo.
    long int posicao;    
} registro_t;