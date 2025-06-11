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

#include <hash.h>

extern void q2(FILE* arq, hash_t *indice, int buscas[], size_t n_buscas);
extern void q3(FILE *arquivo, int buscas[], size_t n_buscas);
extern void q5(FILE *arquivo, float buscas[], size_t n_buscas, char operacao);

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
    size_t ALUNOS = 1000000;

    // Número de elementos de busca
    size_t BUSCAS = 30;

    srand(time(NULL));

    FILE *saida = fopen("alunos.db", "w+");

    // Tratar falha de abertura do arquivo
    if (!saida) {
        printf("Não foi possível abrir o arquivo de saída: %s\n", strerror(errno));
        return -1;
    }

    // Indices
    hash_t *indice_hash = hash_criar(ALUNOS / 2);
    int colisoes_hash = 0;

    // Chaves de busca
    int buscas_matricula[BUSCAS];
    float buscas_coeficiente[BUSCAS];

    // Gerar alunos aleatórios
    size_t j = 0;
    for (size_t i = 0; i < ALUNOS; i++) {
        aluno_t aluno = gerar_aluno();

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

        // Preencher vetores de busca
        if (i % (ALUNOS / BUSCAS) == 0) {
            // Gerar um valor possívelmente ausente as vezes
            if (rand() % 4 == 0)
                aluno = gerar_aluno();
            
            buscas_coeficiente[j] = aluno.coeficiente;
            buscas_matricula[j] = aluno.matricula;
            j++;
        }

        // !!! A fazer !!!
        // Inserir cada aluno nos índices (árvores).
        // Lembrando que é pra inserir um dos registros nas árvores, e não o 'struct aluno_t' completo.
        colisoes_hash += hash_inserir(indice_hash, registro_matricula);
    }

    // Desordenar elementos de busca (para a busca sequencial, talvez desnecessário)
    for (size_t i = 0; i < BUSCAS; i++) {
        int chave = rand() % BUSCAS;
        
        // Desordenar matrículas
        int a = buscas_matricula[i];
        buscas_matricula[i] = buscas_matricula[chave];
        buscas_matricula[chave] = a;

        // Desordenar coeficientes
        float b = buscas_coeficiente[i];
        buscas_coeficiente[i] = buscas_coeficiente[chave];
        buscas_coeficiente[chave] = b;
    }

    // Q2. Tabela hash
    q2(saida, indice_hash, buscas_matricula, BUSCAS);
    printf("  Colisões: %d\n", colisoes_hash);

    // Q3. Busca sequencial por igualdade
    q3(saida, buscas_matricula, BUSCAS);
    
    // Q5. Busca sequencial por comparação
    q5(saida, buscas_coeficiente, BUSCAS, '>');


    hash_liberar(indice_hash);
    fclose(saida);
}
