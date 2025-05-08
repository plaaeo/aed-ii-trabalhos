#include "../avl.h"
#include "../abp.h"
#include "../utilitarios.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int aleatorio() {
    return rand() % 1000000;
}

void questao4(unsigned int seed) {
    double r_abp[10] = {};
    double r_avl[10] = {};
    int a_abp[10] = {};
    int a_avl[10] = {};

    for (int j = 0; j < 10; j++) {
        // Criação da árvore binária
        abp_t *abp = NULL;

        srand(seed);
        medir_inicio(r_abp, j);
        for (int i = 0; i < 1000000; i++) {
            abp = abp_inserir(abp, aleatorio());
        }
        medir_fim(r_abp, j);
        a_abp[j] = abp_altura(abp);

        // Criação da AVL
        avl_t *avl = NULL;

        srand(seed);
        medir_inicio(r_avl, j);
        for (int i = 0; i < 1000000; i++) {
            avl = avl_inserir(avl, aleatorio());
        }
        medir_fim(r_avl, j);
        a_avl[j] = avl_altura(avl);

        // Definição da próxima seed aleatória
        seed = time(NULL);
    }

    // Imprimir tabelas com os dados
    printf("| Criação | ABP           | AVL           | Alt. ABP | Alt. AVL |\n");
    printf("|--------:|:-------------:|:-------------:|:---------|:---------|\n");
    for (int j = 0; j < 10; j++) {
        printf("| It. %2d  | %13.2f | %13.2f | %8d | %8d |\n", j + 1, r_abp[j], r_avl[j], a_abp[j], a_avl[j]);
    }

    double m_abp = media(r_abp, 10);
    double m_avl = media(r_avl, 10);
    double d_abp = desvio_padrao(m_abp, r_abp, 10);
    double d_avl = desvio_padrao(m_avl, r_avl, 10);

    printf("| Media  | %13.4f | %13.4f |    --    |    --    | \n", m_abp, m_avl);
    printf("| Desvio | %13.4f | %13.4f |    --    |    --    | \n", d_abp, d_avl);
};
