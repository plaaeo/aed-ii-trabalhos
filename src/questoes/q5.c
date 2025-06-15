/*
 * q5.c
 *
 * Busca sequencial no arquivo para consultas do tipo >, <, >=, <= em coeficiente
 * com saída formatada em tabela
 */

#include <stdio.h>
#include <stdbool.h>
#include "registro.h"
#include "utilitarios.h"

// Função auxiliar para verificar se um aluno satisfaz a condição
static bool satisfaz_condicao(float coeficiente, float valor, int operacao) {
    switch (operacao) {
        case 0:  return coeficiente > valor;
        case 1:  return coeficiente < valor;
        case 2:  return coeficiente >= valor;
        case 3:  return coeficiente <= valor;
        default: return false;
    }
}

// Função para busca sequencial por coeficiente com saída em tabela
void q5(FILE *arquivo, float buscas[], size_t n_buscas, int operacoes[]) {
    double tempo_busca[n_buscas];
    int encontrados[n_buscas];
    aluno_t aluno;

    // Cabeçalho da tabela
    printf("\n* Questão 5 - Busca sequencial por comparação\n");
    printf("  | Busca  | Tempo de busca (µs) | Encontrados | Comparação |\n");
    printf("  |-------:|:-------------------:|:-----------:|:-----------|\n");

    for (size_t i = 0; i < n_buscas; i++) {
        encontrados[i] = 0;
        rewind(arquivo);

        medir_inicio(tempo_busca, i);

        // Percorre todo o arquivo
        while (fread(&aluno, sizeof(aluno_t), 1, arquivo) == 1) {
            if (satisfaz_condicao(aluno.coeficiente, buscas[i], operacoes[i])) {
                encontrados[i]++;
            }
        }

        medir_fim(tempo_busca, i);

        // Linha da tabela para esta busca
        const char* operacao;

        switch (operacoes[i]) {
            case 0:  operacao = ">"; break;
            case 1:  operacao = "<"; break;
            case 2:  operacao = "≥"; break;
            case 3:  operacao = "≤"; break;
            default: operacao = "?";
        }

        printf("  | Id. %02lu | %19.2lf | %11d | %s%-5.02lf     |\n",
               i + 1, tempo_busca[i], encontrados[i], operacao, buscas[i]);
    }

    // Estatísticas finais
    double media_tempo = media(tempo_busca, n_buscas);
    double desvio = desvio_padrao(media_tempo, tempo_busca, n_buscas);

    printf("\nEstatísticas da busca sequencial por coeficiente:\n");
    printf(" → Média de tempo: %.2f µs\n", media_tempo);
    printf(" → Desvio padrão: %.2f µs\n", desvio);

    int total_encontrados = 0;
    for (size_t i = 0; i < n_buscas; i++) {
        total_encontrados += encontrados[i];
    }
    printf(" → Total de registros encontrados: %d\n", total_encontrados);
    printf(" → Média de registros por busca: %.1f\n", ((float)total_encontrados)/((float)n_buscas));
}
