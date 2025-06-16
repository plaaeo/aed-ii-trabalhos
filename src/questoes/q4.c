/*
 * q4.c
 *
 * Busca do tipo >, >=, < ou <= usando a árvore binária de pesquisa ou AVL para um atributo não-chave.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "registro.h"
#include "utilitarios.h"
#include "abp.h"

// encontra os alunos que satisfazem a comparação
void q4(FILE* arq, abp_t* raiz, double valor[], int comparacao[], size_t n_buscas, size_t n_alunos){
    double tempos_busca[n_buscas];
    double tempos_consulta[n_buscas];
    size_t encontrados[n_buscas];

    registro_t *registros = (registro_t *)malloc(sizeof(registro_t) * n_alunos);

    printf("\n* Questão 4 - Busca na ABP por desigualdade\n");
    printf("  | Busca  | Tempo de busca (µs) | Tempo de Consulta (µs) | Encontrados | Comparação |\n");
    printf("  |-------:|:-------------------:|:----------------------:|:------------|:-----------|\n");
    for(size_t i=0; i<n_buscas; i++){
        // Medir tempo de busca de todos os itens
        medir_inicio(tempos_busca, i);
        encontrados[i] = abp_comparar(raiz, valor[i], comparacao[i], registros, n_alunos);
        medir_fim(tempos_busca, i);

        // Medir tempo de consulta de cada item
        medir_inicio(tempos_consulta, i);
        for (size_t j = 0; j < encontrados[i]; j++) {
            aluno_t aluno;
            fseek(arq, registros[j].posicao, SEEK_SET);

            // Verificar retorno de `fread` (aviso do gcc)
            if (fread(&aluno, sizeof(aluno_t), 1, arq) == 0) {
                printf("Registro do índice não pertence ao arquivo! (%lf)\n", registros[j].matricula_ou_cr);
            }
        }
        medir_fim(tempos_consulta, i);

        // Linha da tabela para esta busca
        const char* operacao;

        switch (comparacao[i]) {
            case 0:  operacao = ">"; break;
            case 1:  operacao = "<"; break;
            case 2:  operacao = "≥"; break;
            case 3:  operacao = "≤"; break;
            default: operacao = "?";
        }

        printf("  | It. %02lu | %19.2lf | %22.2lf | %11ld | %s%-5.02lf     |\n",
               i + 1, tempos_busca[i], tempos_consulta[i], encontrados[i], operacao, valor[i]);
    }

    double media_busca = media(tempos_busca, n_buscas);
    double desvio_busca = desvio_padrao(media_busca, tempos_busca, n_buscas);
    double media_consulta = media(tempos_consulta, n_buscas);
    double desvio_consulta = desvio_padrao(media_consulta, tempos_busca, n_buscas);

    printf("\nEstatísticas da busca na ABP por desigualdade:\n");
    printf(" → Média do tempo de busca: %.2f µs\n", media_busca);
    printf(" → Desvio do tempo de busca: %.2f µs\n", desvio_busca);
    printf(" → Média do tempo de consulta: %.2f µs\n", media_consulta);
    printf(" → Desvio do tempo de consulta: %.2f µs\n", desvio_consulta);

    int total_encontrados = 0;
    for (size_t i = 0; i < n_buscas; i++) {
        total_encontrados += encontrados[i];
    }
    printf(" → Total de registros encontrados: %d\n", total_encontrados);
    printf(" → Média de registros por busca: %.1f\n", ((float)total_encontrados)/((float)n_buscas));

    free(registros);
}
