/**
 * Algorítmos e Estruturas de Dados II - Turma CB01
 * Trabalho 3 - Indexação e Tabela Hash
 *
 * Aluno: Paulo Victor Fernandes de Melo
 * Aluno: João Luiz Rodrigues da Silva
 * Aluna: Rebecca Aimée Lima de Lima
 * Aluna: Beatriz Jacaúna Martins
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "hash.h"
#include "abp.h"

// Número de alunos aleatórios para gerar
#define ALUNOS 1000000

// Número de elementos de busca
#define BUSCAS 30

extern void q1(abp_t* indice, FILE* arquivo, int buscas[], size_t n_buscas);
extern void q2(FILE* arq, hash_t *indice, int buscas[], size_t n_buscas);
extern void q3(FILE *arquivo, int buscas[], size_t n_buscas);
extern void q4(abp_t* raiz, double valor[], int comparacao[], size_t n_buscas, FILE* arq);
extern void q5(FILE *arquivo, float buscas[], size_t n_buscas, int operacoes[]);

// Gera um aluno com dados quase aleatórios
aluno_t gerar_aluno(int matricula) {
    aluno_t aluno = {};

    // Gerar dados numéricos
    aluno.matricula = matricula;
    aluno.ano_ingresso = 1909 + (rand() % 117);
    aluno.coeficiente = (float)(rand() % 10001) / 1000.0f;

    // Inserir alguns espaços no nome do aluno
    for (size_t i = 1; i < sizeof(aluno.nome) / sizeof(char); i++)
        aluno.nome[i - 1] = rand() % 10 ? 'A' + (rand() % 26) : ' ';

    // Inserir alguns pontos no email
    size_t t_email = sizeof(aluno.email) / sizeof(char);
    for (size_t i = 1; i < t_email; i++)
        aluno.email[i - 1] = rand() % 30 ? 'a' + (rand() % 26) : '.';

    aluno.email[rand() % t_email] = '@';

    // Inserir alguns espaços no nome da cidade
    for (size_t i = 1; i < sizeof(aluno.cidade) / sizeof(char); i++)
        aluno.cidade[i - 1] = rand() % 30 ? 'A' + (rand() % 26) : ' ';

    // Inserir alguns números no nome da cidade
    for (size_t i = 1; i < sizeof(aluno.curso) / sizeof(char); i++)
        aluno.curso[i - 1] = rand() % 30 ? 'A' + (rand() % 26) : '0' + (rand() % 10);

    return aluno;
}

int main() {
    srand(time(NULL));

    FILE *saida = fopen("alunos.db", "w+");

    // Tratar falha de abertura do arquivo
    if (!saida) {
        printf("Não foi possível abrir o arquivo de saída: %s\n", strerror(errno));
        return -1;
    }

    // Gerar matrículas únicas aleatórias
    printf("Gerando matrículas aleatórias...\n");
    int *matriculas = malloc(sizeof(int) * ALUNOS);
    for (int i = 0; i < ALUNOS; i++) {
        int prev = i == 0 ? 10000000 : matriculas[i - 1];
        matriculas[i] = prev + 1 + (rand() % 30);
    }

    int matricula_max = matriculas[ALUNOS - 1];

    // Embaralhar matrículas aleatoriamente
    printf("Embaralhando matrículas...\n");
    for (int i = 0; i < ALUNOS; i++) {
        int j = rand() % ALUNOS;
        int outro = matriculas[j];
        matriculas[j] = matriculas[i];
        matriculas[i] = outro;
    }

    // Indices
    abp_t *indice_abp_mat = NULL;
    abp_t *indice_abp_cr = NULL;
    hash_t *indice_hash = hash_criar(1000003);
    int colisoes_hash = 0;

    // Chaves de busca
    int buscas_matricula[BUSCAS];
    float buscas_coeficiente[BUSCAS];
    int operacoes[BUSCAS];

    // Gerar alunos aleatórios
    printf("Gerando alunos aleatórios...\n");
    for (size_t i = 0; i < ALUNOS; i++) {
        aluno_t aluno = gerar_aluno(matriculas[i]);

        // Imprimir dados (podemos remover dps)
        // printf("---\n");
        // printf("matricula = %d\n", aluno.matricula);
        // printf("nome = %s\n", aluno.nome);
        // printf("email = %s\n", aluno.email);
        // printf("cidade = %s\n", aluno.cidade);
        // printf("ano_ingresso = %d\n", aluno.ano_ingresso);
        // printf("curso = %s\n", aluno.curso);
        // printf("coeficiente = %f\n", aluno.coeficiente);

        // Inserir alunos no arquivo
        long int pos_aluno = ftell(saida);
        fwrite(&aluno, sizeof(aluno_t), 1, saida);

        // Registro com a matrícula como chave
        registro_t registro_matricula = {
            .matricula_ou_cr = aluno.matricula,
            .posicao = pos_aluno
        };

        // Registro com o coeficiente como chave
        registro_t registro_cr = {
            .matricula_ou_cr = aluno.coeficiente,
            .posicao = pos_aluno
        };

        // !!! A fazer !!!
        // Inserir cada aluno nos índices (árvores).
        // Lembrando que é pra inserir um dos registros nas árvores, e não o 'struct aluno_t' completo.
        colisoes_hash += hash_inserir(indice_hash, registro_matricula);
        indice_abp_mat = abp_inserir(indice_abp_mat, registro_matricula);
        indice_abp_cr = abp_inserir(indice_abp_cr, registro_cr);
    }

    // Gerar elementos de busca
    printf("Gerando elementos de busca...\n");
    for (size_t i = 0; i < BUSCAS; i++) {
        int chave = rand() % BUSCAS;

        // 25% de chance de gerar uma matrícula completamente aleatória
        if (rand() % 4) {
            buscas_matricula[i] = matriculas[rand() % ALUNOS];
        } else {
            buscas_matricula[i] = 10000001 + (rand() % (matricula_max - 10000001));
        }

        buscas_coeficiente[i] = (float)(rand() % 10001) / 1000.0f;
        operacoes[i] = rand() % 4;
    }

    rewind(saida);

    // Q1. Busca na ABP por igualdade
    q1(indice_abp_mat, saida, buscas_matricula, BUSCAS);

    // Q2. Tabela hash
    q2(saida, indice_hash, buscas_matricula, BUSCAS);
    printf(" → Colisões: %d\n", colisoes_hash);

    // Q3. Busca sequencial por igualdade
    q3(saida, buscas_matricula, BUSCAS);

    // Q4. Busca na árvore binária por comparação
    q4(indice_abp_cr, buscas_coeficiente, operacoes, BUSCAS, saida);

    // Q5. Busca sequencial por comparação
    q5(saida, buscas_coeficiente, BUSCAS, operacoes);

    hash_liberar(indice_hash);
    abp_liberar(indice_abp_mat);
    free(matriculas);
    fclose(saida);
}
