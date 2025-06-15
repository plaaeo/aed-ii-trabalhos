/*
 * q1.c
 * Busca por atributo chave (matrícula) usando Árvore Binária de Pesquisa (ABP)
 * Saída formatada + estatísticas
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "../abp.h"
#include "../registro.h"
#include "../utilitarios.h"

// Função de busca por matrícula usando árvore binária de pesquisa
void q1(abp_t* indice, FILE* arquivo, int buscas[], size_t n_buscas) {
    double tempos_busca[n_buscas];
    double tempos_consulta[n_buscas];
    bool resultados[n_buscas];
    aluno_t aluno;

    printf("\n* Questão 1 - Busca por igualdade na Árvore Binária de Pesquisa (ABP)\n");
    printf("  | Busca  | Tempo de busca (µs) | Tempo de consulta (µs) | Encontrado | Matrícula |\n");
    printf("  |-------:|:-------------------:|:----------------------:|:----------:|:----------|\n");

    for (size_t i = 0; i < n_buscas; i++) {
        registro_t registro;

        // Medir tempo de busca
        medir_inicio(tempos_busca, i);
        resultados[i] = abp_buscar(indice, buscas[i], &registro);
        medir_fim(tempos_busca, i);

        if (resultados[i]) {
            // Medir tempo de consulta
            medir_inicio(tempos_consulta, i);
            fseek(arquivo, registro.posicao, SEEK_SET);
            fread(&aluno, sizeof(aluno_t), 1, arquivo);
            medir_fim(tempos_consulta, i);
        } else {
            tempos_consulta[i] = NAN;
        }

        printf("  | Id. %02lu | %19.2lf | %22.2lf | %10s | %9d |\n", i + 1,
               tempos_busca[i], tempos_consulta[i],
               (resultados[i] > 0) ? "Sim" : "Nao", buscas[i]);
    }

    double media_busca = media(tempos_busca, n_buscas);
    double desvio_busca = desvio_padrao(media_busca, tempos_busca, n_buscas);
    double media_consulta = media(tempos_consulta, n_buscas);
    double desvio_consulta =
        desvio_padrao(media_consulta, tempos_busca, n_buscas);

    int encontrados = 0;
    for (size_t i = 0; i < n_buscas; i++)
        if (resultados[i]) encontrados++;

    printf("\nEstatísticas da busca na ABP por matrícula:\n");
    printf(" → Matrículas encontradas: %d de %lu\n", encontrados, n_buscas);
    printf(" → Média do tempo de busca: %.2f µs\n", media_busca);
    printf(" → Desvio do tempo de busca: %.2f µs\n", desvio_busca);
    printf(" → Média do tempo de consulta: %.2f µs\n", media_consulta);
    printf(" → Desvio do tempo de consulta: %.2f µs\n", desvio_consulta);
}
