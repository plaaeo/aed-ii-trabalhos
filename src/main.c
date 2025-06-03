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

#include <hash.h>

typedef struct aluno_t {
    int matricula;
    char nome[100];
    char email[100];
    char cidade[30];
    int ano_ingresso;
    char curso[6];
    float coeficiente;
} aluno_t;

// Gera um aluno com dados quase aleatórios
aluno_t gerar_aluno() {
    aluno_t aluno = {};

    // Gerar dados numéricos
    aluno.matricula = 10000000 + (rand() % 99999999);
    aluno.ano_ingresso = 1909 + (rand() % 118);
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
    // Número de alunos aleatórios para gerar
    size_t ALUNOS = 100;
    srand(time(NULL));

    FILE *saida = fopen("alunos.db", "w");

    // Tratar falha de abertura do arquivo
    if (!saida) {
        int e = ferror(saida);
        printf("Não foi possível abrir o arquivo de saída: %s\n", strerror(e));
        return -1;
    }

    // Gerar alunos aleatórios
    for (size_t i = 0; i < ALUNOS; i++) {
        aluno_t aluno = gerar_aluno();

        // Imprimir dados (podemos remover dps)
        printf("---\n");
        printf("matricula = %d\n", aluno.matricula);
        printf("nome = %s\n", aluno.nome);
        printf("email = %s\n", aluno.email);
        printf("cidade = %s\n", aluno.cidade);
        printf("ano_ingresso = %d\n", aluno.ano_ingresso);
        printf("curso = %s\n", aluno.curso);
        printf("coeficiente = %f\n", aluno.coeficiente);

        // Inserir alunos no arquivo
        // long int pos_aluno = ftell(saida);
        fwrite(&aluno, sizeof(aluno_t), 1, saida);

        // !!! A fazer !!!
        // Inserir cada aluno nos índices (árvore e hash).
        //
        // Lembrando que não é pra inserir o aluno inteiro (ou seja, a struct aluno_t) nos índices,
        // mas uma struct menor que contenha a posição do aluno no arquivo
        //
        // Na sala, alguem comentou que o professor quer que armazene no índice APENAS a posição do aluno no arquivo,
        // para que haja um acesso no arquivo para cada comparação das árvores binárias.
        // Faz sentido, pq senão a busca sequencial fica numa desvantagem gigantesca, mas isso significa que
        // teria q fazer um ajustezão na árvore binária, ent recomendo tirar essa dúvida :3
    }

    fclose(saida);
}
