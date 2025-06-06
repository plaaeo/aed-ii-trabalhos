/*
 * q3.c
 * Busca sequencial no arquivo para o atributo chave;
 */

#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "hash.h"
#include "registro.h"
#include "utilitarios.h"

void q3(FILE* arq, hash_t *indice, int buscas[], size_t n_buscas) {
    int r_encontrado[n_buscas];
    double r_tempo_busca[n_buscas];
    double r_tempo_consulta[n_buscas];

    for (size_t i = 0; i < n_buscas; i++) {
        registro_t reg;

        // Medir tempo de busca
        medir_inicio(r_tempo_busca, i);
        r_encontrado[i] = hash_buscar(indice, buscas[i], &reg);
        medir_fim(r_tempo_busca, i);

        // Medir tempo de consulta
        if (r_encontrado[i]) {
            aluno_t aluno;
            medir_inicio(r_tempo_consulta, i);
            
            // Definir posição do cursor para leitura
            fseek(arq, reg.posicao, SEEK_SET);
            fread(&aluno, sizeof(aluno), 1, arq);
            printf("(aluno '%s' encontrado)\n", aluno.nome);

            medir_fim(r_tempo_consulta, i);
        } else {
            r_tempo_consulta[i] = NAN;
        }
    }

    // Imprimir resultados
    printf("| Busca  | Tempo de busca (us) | Tempo de consulta (us) | Encontrado |\n");
    printf("|-------:|:-------------------:|:----------------------:|:----------:|\n");
    for (size_t i = 0; i < n_buscas; i++) {
        const char* encontrado = "Nao";
        if (r_encontrado[i])
            encontrado = "Sim";
        
        printf("| Id. %02lu | %19.2lf | %22.2lf | %10s |\n", i + 1, r_tempo_busca[i], r_tempo_consulta[i], encontrado);
    }
}
