#include "../avl.h"
#include "../abp.h"
#include "../utilitarios.h"

#include <threads.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define TAM 2000000

int aleatorio() {
    return rand() % TAM;
}

void questao4(unsigned int seed) {
    abp_t* abp = NULL;
    avl_t* avl = NULL;
    double r_abp[10] = {};
    double r_avl[10] = {};
    double b_abp[30] = {};
    double b_avl[30] = {};
    int a_abp[10] = {};
    int a_avl[10] = {};

    printf("* Questao 4\n");
    for (int j = 0; j < 10; j++) {
        // abp_liberar(abp); nao tem ainda :(
        avl_liberar(avl);
        printf(". Executando iteração %d... ", j + 1);
        fflush(stdout);

        // Criação da árvore binária
        srand(seed);
        medir_inicio(r_abp, j);
        for (int i = 0; i < TAM; i++) {
            abp = abp_inserir(abp, aleatorio());
        }
        medir_fim(r_abp, j);
        a_abp[j] = abp_altura(abp);

        printf("[ABP OK] ");
        fflush(stdout);

        // Criação da AVL
        srand(seed);
        medir_inicio(r_avl, j);
        for (int i = 0; i < TAM; i++) {
            avl = avl_inserir(avl, aleatorio());
        }
        medir_fim(r_avl, j);
        a_avl[j] = avl_altura(avl);

        printf("[AVL OK]\n");

        // Definição da próxima seed aleatória
        seed = time(NULL);
    }

    // Busca na árvore binária
    srand(seed);
    for (int i = 0; i < 30; i++) {
        medir_inicio(b_abp, i);
        abp_buscar(abp, aleatorio());
        medir_fim(b_abp, i);
    }

    // Busca na árvore AVL
    srand(seed);
    for (int i = 0; i < 30; i++) {
        medir_inicio(b_avl, i);
        avl_buscar(avl, aleatorio());
        medir_fim(b_avl, i);
    }

    // Imprimir tabelas com os dados
    printf(". Tabela de tempos de criação\n");
    printf("| Criação | ABP           | AVL           | Alt. ABP | Alt. AVL |\n");
    printf("|--------:|:-------------:|:-------------:|:---------|:---------|\n");
    for (int j = 0; j < 10; j++) {
        printf("| It. %2d  | %13.2f | %13.2f | %8d | %8d |\n", j + 1, r_abp[j], r_avl[j], a_abp[j], a_avl[j]);
    }

    double m_abp = media(r_abp, 10);
    double m_avl = media(r_avl, 10);
    double d_abp = desvio_padrao(m_abp, r_abp, 10);
    double d_avl = desvio_padrao(m_avl, r_avl, 10);

    printf("| Media   | %13.4f | %13.4f |    --    |    --    | \n", m_abp, m_avl);
    printf("| Desvio  | %13.4f | %13.4f |    --    |    --    | \n", d_abp, d_avl);

    printf(". Tabela de tempos de busca\n");
    printf("| Busca   | ABP           | AVL           |\n");
    printf("|--------:|:-------------:|:-------------:|\n");
    for (int j = 0; j < 10; j++) {
        printf("| It. %2d  | %13.2f | %13.2f |\n", j + 1, b_abp[j], b_avl[j]);
    }

    double mb_abp = media(b_abp, 30);
    double mb_avl = media(b_avl, 30);
    double db_abp = desvio_padrao(mb_abp, b_abp, 30);
    double db_avl = desvio_padrao(mb_avl, b_avl, 30);

    printf("| Media   | %13.4f | %13.4f |\n", mb_abp, mb_avl);
    printf("| Desvio  | %13.4f | %13.4f |\n", db_abp, db_avl);
};
