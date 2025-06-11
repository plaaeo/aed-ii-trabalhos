/*
 * q1.c
 * Busca usando a árvore binária de pesquisa para o atributo chave;
 */
#include <stdio.h>
#include <stdbool.h>
#include "abp.h"
#include "registro.h"
#include "utilitarios.h"

/// Busca um aluno pela matrícula usando a árvore binária de pesquisa.
/// Retorna `true` se encontrado e imprime o aluno. Caso contrário, retorna `false`.
bool buscar_por_matricula_abp(abp_t* indice, int matricula, FILE* arquivo_dados, aluno_t* resultado) {
    registro_t reg;
    bool encontrado = abp_buscar(indice, matricula, &reg);

    if (!encontrado) return false;

    // Posiciona o cursor no arquivo e lê o aluno
    fseek(arquivo_dados, reg.posicao, SEEK_SET);
    fread(resultado, sizeof(aluno_t), 1, arquivo_dados);

    return true;
}

