#include "../avl.h"
#include "../abp.h"
#include "../utilitarios.h"

#include <threads.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM 1000000
#define BUSCAS 30
#define ARVORES 10

void questao4() {
    abp_t* abp = NULL;
    avl_t* avl = NULL;
    int a_abp[ARVORES] = {};
    int a_avl[ARVORES] = {};
    double r_abp[ARVORES] = {};
    double r_avl[ARVORES] = {};
    double b_abp[BUSCAS] = {};
    double b_avl[BUSCAS] = {};
    vetor_t dados = malloc(sizeof(int) * TAM);

    printf("\n* Questao 4\n");
    for (int j = 0; j < ARVORES; j++) {
        abp_liberar(abp);
        avl_liberar(avl);
        printf(". Executando iteração %d... ", j + 1);
        fflush(stdout);

        abp = NULL;
        avl = NULL;
        vetor_gerar_aleatorio(dados, TAM, TAM);

        // Criação da árvore binária
        medir_inicio(r_abp, j);
        for (int i = 0; i < TAM; i++) {
            abp = abp_inserir(abp, dados[i]);
        }
        medir_fim(r_abp, j);
        a_abp[j] = abp_altura(abp);

        // Fim da ABP
        printf("[ABP OK] ");
        fflush(stdout);

        // Criação da AVL
        medir_inicio(r_avl, j);
        for (int i = 0; i < TAM; i++) {
            avl = avl_inserir(avl, dados[i]);
        }
        medir_fim(r_avl, j);
        a_avl[j] = avl_altura(avl);

        // Fim da AVL
        printf("[AVL OK]\n");
        fflush(stdout);
    }

    printf(". Executando buscas... ");
    fflush(stdout);

    vetor_t buscas = malloc(sizeof(int) * BUSCAS);
    vetor_gerar_aleatorio(buscas, TAM, BUSCAS);

    // Busca na árvore binária
    for (int i = 0; i < BUSCAS; i++) {
        medir_inicio(b_abp, i);
        abp_buscar(abp, buscas[i]);
        medir_fim(b_abp, i);
    }

    printf("[ABP OK] ");
    fflush(stdout);

    // Busca na árvore AVL
    for (int i = 0; i < BUSCAS; i++) {
        medir_inicio(b_avl, i);
        avl_buscar(avl, buscas[i]);
        medir_fim(b_avl, i);
    }

    printf("[AVL OK]\n\n");
    fflush(stdout);

    // Imprimir tabelas com os dados
    printf("# Tabela de tempos de criação (ms)\n");
    printf("| Criação | ABP           | AVL           | Alt. ABP | Alt. AVL |\n");
    printf("|--------:|:-------------:|:-------------:|:---------|:---------|\n");
    for (int j = 0; j < ARVORES; j++) {
        printf("| It. %2d  | %13.2f | %13.2f | %8d | %8d |\n", j + 1, r_abp[j] / 1000, r_avl[j] / 1000, a_abp[j], a_avl[j]);
    }

    double m_abp = media(r_abp, ARVORES);
    double m_avl = media(r_avl, ARVORES);
    double d_abp = desvio_padrao(m_abp, r_abp, ARVORES);
    double d_avl = desvio_padrao(m_avl, r_avl, ARVORES);

    printf("| Media   | %13.2f | %13.2f |    --    |    --    |\n", m_abp / 1000, m_avl / 1000);
    printf("| Desvio  | %13.4f | %13.4f |    --    |    --    |\n\n", d_abp / 1000, d_avl / 1000);

    printf("# Tabela de tempos de busca (us)\n");
    printf("| Busca   | ABP      | AVL      |\n");
    printf("|--------:|:--------:|:--------:|\n");
    for (int j = 0; j < BUSCAS; j++) {
        printf("| It. %2d  | %8.2f | %8.2f |\n", j + 1, b_abp[j], b_avl[j]);
    }

    double mb_abp = media(b_abp, BUSCAS);
    double mb_avl = media(b_avl, BUSCAS);
    double db_abp = desvio_padrao(mb_abp, b_abp, BUSCAS);
    double db_avl = desvio_padrao(mb_avl, b_avl, BUSCAS);

    printf("| Media   | %8.4f | %8.4f |\n", mb_abp, mb_avl);
    printf("| Desvio  | %8.4f | %8.4f |\n\n", db_abp, db_avl);

    abp_liberar(abp);
    avl_liberar(avl);
    free(dados);
    free(buscas);
};
