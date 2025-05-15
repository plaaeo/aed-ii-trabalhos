#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>

#include "../abp.h"
#include "../utilitarios.h"
#include "../vetor.h"

#define TAMANHO 1000000
#define BUSCAS 30

// Busca um elemento ausente na árvore/vetor a cada 5a busca
#define PERIODO 5

// TODO: pausas para verificar o gerenciador de tarefas
void questao3(unsigned int seed) {
    int ch;

    srand(seed);
    printf("\n* Questao 3\n");

    // Alocação com verificação
    vetor_t vetor = (vetor_t)malloc(TAMANHO * sizeof(int));

    if (!vetor) {
        printf(". Erro na alocação de memória\n");
        return;
    }

    abp_t* arvore = NULL;

    printf(". Gerando vetor ordenado...\n");
    vetor_gerar_ordenado(vetor, TAMANHO);

    printf("  Pressione <ENTER> para gerar a ABP.\n");
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    printf(". Construindo ABP...\n");
    arvore = abp_criar_por_vetor(vetor, TAMANHO);

    printf("  Pressione <ENTER> para continuar a execucao.\n");
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    // Preparar buscas garantindo que alguns valores existam e outros não
    int valores_busca[BUSCAS];
    for (int i = 0; i < BUSCAS; i++) {
        if (i % PERIODO != 0) {
            // Valores que existem no vetor
            valores_busca[i] = vetor[rand() % TAMANHO];
        } else {
            // Valores que não existem
            valores_busca[i] = (2 * TAMANHO) + (rand() % TAMANHO);
        }
    }

    double tempos_abb[BUSCAS] = {};
    double tempos_vet[BUSCAS] = {};

    printf(". Executando buscas...\n");
    for (int i = 0; i < BUSCAS; i++) {
        int valor = valores_busca[i];

        // Busca na ABP
        medir_inicio(tempos_abb, i);
        abp_t* resultado_abb = abp_buscar(arvore, valor);
        medir_fim(tempos_abb, i);

        // Busca no vetor
        medir_inicio(tempos_vet, i);
        int resultado_vetor = vetor_busca_binaria(vetor, TAMANHO, valor);
        medir_fim(tempos_vet, i);

        // Verificação de consistência
        int encontrado_abb = (resultado_abb != NULL);
        int encontrado_vetor = (resultado_vetor != -1);

        if (encontrado_abb != encontrado_vetor) {
            printf(
                ". AVISO: Divergência na busca por %d (ABP: %d, Vetor: %d)\n",
                valor, encontrado_abb, encontrado_vetor);
        }
    }

    printf("\n# Resultados das buscas\n");
    printf("| Buscas   | ABP     | Vetor   |\n");
    printf("|---------:|:-------:|:-------:|\n");
    for (int i = 0; i < BUSCAS; i++) {
        printf("| Busca %2d | %7.2f | %7.2f |\n", i + 1, tempos_abb[i],
               tempos_vet[i]);
    }

    double media_abb = media(tempos_abb, BUSCAS);
    double media_vet = media(tempos_vet, BUSCAS);
    double desvio_abb = desvio_padrao(media_abb, tempos_abb, BUSCAS);
    double desvio_vet = desvio_padrao(media_vet, tempos_vet, BUSCAS);

    printf("| Desvio   | %7.4f | %7.4f |\n", desvio_abb, desvio_vet);
    printf("| Media    | %7.4f | %7.4f |\n", media_abb, media_vet);
    printf(". Altura da ABP: %d\n", abp_altura(arvore));

    abp_liberar(arvore);
    free(vetor);
}
