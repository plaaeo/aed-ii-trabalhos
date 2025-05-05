/**
 * utilitarios.h
 * 
 * Alguns utilitários para cálculos comuns no trabalho.
 * Exemplo de como usar as funções 'medir_inicio' e 'medir_fim':
 *  
 *  double medicoes[30] = {};
 *  for (int i = 0; i < 30; i++) {
 *      medir_inicio(medicoes, i);
 *      fazer_alguma_coisa_que_demora_muito_tempo(muitas_coisas, ..., etc);
 *      medir_fim(medicoes, i);
 *  }
 * 
 * O vetor 'medicoes' vai ter os tempos de execução (em microssegundos) da
 * funcao 'fazer_alguma_coisa_que_demora_muito_tempo' para
 * cada uma das 30 execuções.
 */

#pragma once
#include <time.h>

// A quantidade de clocks em 1 microsegundo
#define CLOCKS_POR_MEDIDA (CLOCKS_PER_SEC / 1000000)

// Inicia uma medição, guardando t_inicio em `medicoes[i]`.
void medir_inicio(double *medicoes, int i);

// Finaliza a medição e armazena (t_fim - t_inicio) em `medicoes[i]`, em microsegundos.
void medir_fim(double *medicoes, int i);

// Retorna o desvio padrão do vetor de medições passado.
double desvio_padrao(double media, double* medicoes, int tam);