/*
 * q1.c
 * Busca por atributo chave (matrícula) usando Árvore Binária de Pesquisa (ABP)
 * Saída formatada + estatísticas
 */

#include <stdio.h>
#include <stdbool.h>
#include "../registro.h"
#include "../utilitarios.h"
#include "../abp.h"

// Função de busca por matrícula usando árvore binária de pesquisa
void q1(abp_t* indice, FILE* arquivo, int buscas[], size_t n_buscas) {
    if (!indice || !arquivo || !buscas) {
        fprintf(stderr, "Erro: argumentos inválidos para busca na ABP.\n");
        return;
    }

    double tempos[n_buscas];
    bool resultados[n_buscas];
    aluno_t aluno;

    printf("\n* Questão 1 - Busca por igualdade na Árvore Binária de Pesquisa (ABP)\n");
    printf("  | Busca  | Tempo de busca (µs) | Encontrado |\n");
    printf("  |-------:|:-------------------:|:----------:|\n");

    for (size_t i = 0; i < n_buscas; i++) {
        resultados[i] = false;
        medir_inicio(tempos, i);

        registro_t registro;
        if (abp_buscar(indice, buscas[i], &registro)) {
            resultados[i] = true;
            fseek(arquivo, registro.posicao, SEEK_SET);
            fread(&aluno, sizeof(aluno_t), 1, arquivo);
        }

        medir_fim(tempos, i);

        printf("  | Id. %02lu | %19.2lf | %10s |\n", 
               i + 1, tempos[i], (resultados[i] > 0) ? "Sim" : "Nao");
    }

    double media_tempo = media(tempos, n_buscas);
    double desvio = desvio_padrao(media_tempo, tempos, n_buscas);

    int encontrados = 0;
    for (size_t i = 0; i < n_buscas; i++)
        if (resultados[i]) encontrados++;

    printf("\nEstatísticas da busca na ABP por matrícula:\n");
    printf(" → Matrículas encontradas: %d de %lu\n", encontrados, n_buscas);
    printf(" → Média de tempo: %.2f µs\n", media_tempo);
    printf(" → Desvio padrão: %.2f µs\n", desvio);
}
