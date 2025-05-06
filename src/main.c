/**
 * Algorítmos e Estruturas de Dados II - Turma CB01
 * Trabalho 2 - Árvores Binárias de Pesquisa
 *
 * Aluno: Paulo Victor Fernandes de Melo
 * Aluno: João Luiz Rodrigues da Silva
 * Aluna: Rebecca Aimée Lima de Lima
 * Aluna: Beatriz Jacaúna Martins
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "lse.h"
#include "utilitarios.h"
#include "vetor.h"

int main(int argc, char **argv) {
    unsigned int seed = time(NULL);
    srand(seed);

    avl_t *avl = NULL;
    avl_inserir(&avl, 3);
    avl_inserir(&avl, 2);
    avl_inserir(&avl, 1);
    avl_inserir(&avl, 4);
    avl_inserir(&avl, 5);
    avl_inserir(&avl, 6);
    avl_inserir(&avl, 7);
    avl_inserir(&avl, 16);
    avl_inserir(&avl, 15);
    avl_inserir(&avl, 14);

    printf("oii :3\n");
}
