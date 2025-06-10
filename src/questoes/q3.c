/*
 * q3.c
 * Busca sequencial no arquivo para o atributo chave (matrícula)
 * com saída formatada em tabela
 */

#include <stdio.h>
#include <stdbool.h>
#include "../registro.h"
#include "../utilitarios.h"

// Função para busca sequencial pela matrícula no arquivo
void q3(FILE *arquivo, int buscas[], size_t n_buscas) {
    if (arquivo == NULL || buscas == NULL) {
        fprintf(stderr, "Erro: parâmetros inválidos\n");
        return;
    }

    double tempo_busca[n_buscas];
    bool encontrado[n_buscas];
    aluno_t aluno;

    // Cabeçalho da tabela
    printf("\n  | Busca  | Tempo de busca (us) | Tempo de consulta (us) | Encontrado |\n");
    printf("  |-------:|:-------------------:|:----------------------:|:----------:|\n");

    for (size_t i = 0; i < n_buscas; i++) {
        encontrado[i] = false;
        rewind(arquivo); // Garante que a busca começa do início

        medir_inicio(tempo_busca, i);
        
        // Percorre o arquivo sequencialmente
        while (fread(&aluno, sizeof(aluno_t), 1, arquivo) == 1) {
            if (aluno.matricula == buscas[i]) {
                encontrado[i] = true;
                break; // Encontrou, pode parar a busca
            }
        }
        
        medir_fim(tempo_busca, i);

        // Linha da tabela para esta busca
        const char* status = encontrado[i] ? "Sim" : "Nao";
        printf("  | Id. %02lu | %19.2lf | %22.2lf | %10s |\n", 
               i + 1, tempo_busca[i], tempo_busca[i], status);
    }

    // Cálculo das estatísticas
    double media_tempo = media(tempo_busca, n_buscas);
    double desvio = desvio_padrao(media_tempo, tempo_busca, n_buscas);
    
    printf("\nEstatísticas da busca sequencial por matrícula:\n");
    printf("Média de tempo: %.2f µs\n", media_tempo);
    printf("Desvio padrão: %.2f µs\n", desvio);
    
    int total_encontrados = 0;
    for (size_t i = 0; i < n_buscas; i++) {
        if (encontrado[i]) total_encontrados++;
    }
    printf("Total de matrículas encontradas: %d de %lu\n", total_encontrados, n_buscas);
}