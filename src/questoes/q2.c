/*
 * q2.c
 *
 * Busca usando hashing para o atributo chave;
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "hash.h"
#include "registro.h"
#include "utilitarios.h"

void q2(FILE* arq, hash_t *indice, int buscas[], size_t n_buscas) {
    int r_encontrado[n_buscas];
    int n_encontrados = 0;
    double r_tempo_busca[n_buscas];
    double r_tempo_consulta[n_buscas];

    for (size_t i = 0; i < n_buscas; i++) {
        registro_t reg;

        // Medir tempo de busca
        medir_inicio(r_tempo_busca, i);
        n_encontrados += (r_encontrado[i] = hash_buscar(indice, buscas[i], &reg));
        medir_fim(r_tempo_busca, i);

        // Medir tempo de consulta
        if (r_encontrado[i]) {
            aluno_t aluno;
            medir_inicio(r_tempo_consulta, i);

            // Definir posição do cursor para leitura
            fseek(arq, reg.posicao, SEEK_SET);

            // Verificar retorno de `fread` (aviso do gcc)
            if (fread(&aluno, sizeof(aluno_t), 1, arq) == 0) {
                printf("Registro do índice não pertence ao arquivo! (%lf)\n", reg.matricula_ou_cr);
            }

            medir_fim(r_tempo_consulta, i);
        } else {
            r_tempo_consulta[i] = NAN;
        }
    }

    // Imprimir resultados
    printf("\n* Questão 2 - Busca por igualdade na tabela hash\n");
    printf("  | Busca  | Tempo de busca (µs) | Tempo de consulta (µs) | Encontrado | Matrícula |\n");
    printf("  |-------:|:-------------------:|:----------------------:|:----------:|:----------|\n");
    for (size_t i = 0; i < n_buscas; i++) {
        const char* encontrado = "Nao";
        if (r_encontrado[i])
            encontrado = "Sim";

        printf("  | Id. %02lu | %19.2lf | %22.2lf | %10s | %9d |\n", i + 1, r_tempo_busca[i], r_tempo_consulta[i], encontrado, buscas[i]);
    }

    // Cálculo das estatísticas
    double media_busca = media(r_tempo_busca, n_buscas);
    double desvio_busca = desvio_padrao(media_busca, r_tempo_busca, n_buscas);
    double media_consulta = media(r_tempo_consulta, n_buscas);
    double desvio_consulta = desvio_padrao(media_consulta, r_tempo_consulta, n_buscas);

    printf("\nEstatísticas da busca na hash por matrícula:\n");
    printf(" → Média de tempo de busca: %.2f µs\n", media_busca);
    printf(" → Desvio padrão da busca: %.2f µs\n", desvio_busca);
    printf(" → Média de tempo de consulta: %.2f µs\n", media_consulta);
    printf(" → Desvio padrão da consulta: %.2f µs\n", desvio_consulta);
    printf(" → Total de matrículas encontradas: %d de %lu\n", n_encontrados, n_buscas);
}
