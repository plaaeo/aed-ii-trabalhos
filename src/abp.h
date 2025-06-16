/**
 * abp.h
 *
 * Define a estrutura e as operações de uma Árvore Binária de Pesquisa (ABP).
 */
#pragma once
#include <stdbool.h>

#include "registro.h"
#include "lse.h"

/* --- Valores e chaves --- */
#ifndef ABP_CUSTOM

/// Define o tipo armazenado na árvore.
typedef registro_t abp_valor_t;

/// Define o tipo da chave usada para busca por itens na árvore.
typedef double abp_chave_t;

/// Retorna um 'abp_chave_t' usado para comparar objetos do tipo 'abp_valor_t'
#define abp_chave(x) ((abp_chave_t)((x).matricula_ou_cr))

/// Imprime um objeto do tipo 'abp_valor_t'
#define abp_valor_imprime(x) printf("%lf", (x).matricula_ou_cr)

#endif
/* --- Definição da ABP --- */

typedef struct abp_t abp_t;

/// Cria uma ABP a partir de um vetor ordenado.
abp_t* abp_criar_por_vetor(abp_valor_t* vetor, int tam);

/// Insere um novo elemento em uma ABP. Retorna a nova raíz
/// da árvore binária. Caso `raiz` seja nulo, uma nova árvore é retornada.
abp_t* abp_inserir(abp_t* raiz, abp_valor_t valor);

/// Busca um elemento na ABP a partir de uma chave. Caso o elemento
/// seja encontrado, a função retorna `true` e atualiza o ponteiro `valor`
bool abp_buscar(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor);

// compara um valor com os coeficientes dos alunos e retorna lista com os registros que satisfazem a comparação
lse_t* abp_comparar(abp_t* raiz, double valor, int comparacao, lse_t* lista);

/// Remove um elemento da ABP. Retorna a nova raíz da árvore binária.
abp_t* abp_remover(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor);

/// Imprime os elementos da ABP em pre-ordem.
void abp_pre_ordem(abp_t* raiz);

/// Imprime os elementos da ABP em ordem.
void abp_em_ordem(abp_t* raiz);

/// Imprime os elementos da ABP em pos-ordem.
void abp_pos_ordem(abp_t* raiz);

/// Retorna a altura da ABP.
int abp_altura(abp_t* raiz);

/// Libera a ABP e todas suas subárvores.
void abp_liberar(abp_t* raiz);
