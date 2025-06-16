/*
 * q4.c
 *
 * Busca do tipo >, >=, < ou <= usando a árvore binária de pesquisa ou 
 AVL para um atributo não-chave.
 */
#include <stdio.h>
#include <stdbool.h>
#include "../registro.h"
#include "../utilitarios.h"
#include "../abp.h"
#include "../lse.h"

//encontra os alunos que satisfazem a comparação

void q4(abp_t* raiz, double valor[], int comparacao[], size_t n_buscas, FILE* arq){ 
    double tempos_busca[n_buscas];
    double tempos_consulta[n_buscas];

    printf("\n* Questão 5 - Busca sequencial por comparação\n");
    printf("  | Busca  | Tempo de busca (µs) | Tempo de Consulta (µs) | Comparação |\n");
    printf("  |-------:|:-------------------:|:----------------------:|:-----------|\n");
    for(size_t i=0; i<n_buscas; i++){
        lse_t* lista = NULL;
        // Medir tempo de busca
        medir_inicio(tempos_busca, i);
        lista = abp_comparar(raiz, valor, comparacao, lista);
        medir_fim(tempos_busca, i);

        // Medir tempo de consulta
        medir_inicio(tempos_consulta, i);
        while(lista != NULL){
            aluno_t aluno;
            registro_t registro = lse_cabeca(lista);
            fseek(arq, registro.posicao, SEEK_SET);

            // Verificar retorno de `fread` (aviso do gcc)
            if (fread(&aluno, sizeof(aluno_t), 1, arq) == 0) {
                printf("Registro do índice não pertence ao arquivo! (%lf)\n", registro.matricula_ou_cr);
            }
            lista = acessar_prox(lista);
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
        printf("  | Id. %02lu | %19.2lf | %22.2lf | %s%-5.02lf     |\n",
               i + 1, tempos_busca[i], tempos_consulta[i], operacao, valor[i]);
    }
    double media_busca = media(tempos_busca, n_buscas);
    double desvio_busca = desvio_padrao(media_busca, tempos_busca, n_buscas);
    double media_consulta = media(tempos_consulta, n_buscas);
    double desvio_consulta = desvio_padrao(media_consulta, tempos_busca, n_buscas);

    printf("\nEstatísticas da busca na ABP por matrícula:\n");
    printf(" → Média do tempo de busca: %.2f µs\n", media_busca);
    printf(" → Desvio do tempo de busca: %.2f µs\n", desvio_busca);
    printf(" → Média do tempo de consulta: %.2f µs\n", media_consulta);
    printf(" → Desvio do tempo de consulta: %.2f µs\n", desvio_consulta);
    
}