/**
 * Algorítmos e Estruturas de Dados II - Turma CB01
 * Trabalho 3 - Indexação e Tabela Hash
 *
 * Aluno: Paulo Victor Fernandes de Melo
 * Aluno: João Luiz Rodrigues da Silva
 * Aluna: Rebecca Aimée Lima de Lima
 * Aluna: Beatriz Jacaúna Martins
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <hash.h>

int main() {
    srand(time(NULL));

    hash_t *hash = hash_criar(13);

    for (int i = 0; i < 30; i++) {
        int d = rand() % 2000;
        int c = hash_inserir(hash, d);

        printf("[%d] Inseri %d, colisão? %d\n", i, d, c);
    }
}
