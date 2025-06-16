/**
 * abp.h
 *
 * Define a estrutura e as operações de uma Árvore Binária de Pesquisa (ABP).
 */
#pragma once
#include <stdbool.h>
#include <stddef.h>

#include "registro.h"

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

/// Insere um novo elemento em uma ABP. Retorna a nova raíz
/// da árvore binária. Caso `raiz` seja nulo, uma nova árvore é retornada.
abp_t* abp_inserir(abp_t* raiz, abp_valor_t valor);

/// Busca um elemento na ABP a partir de uma chave. Caso o elemento
/// seja encontrado, a função retorna `true` e atualiza o ponteiro `valor`
bool abp_buscar(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor);

/// Preenche um vetor com todos os valores da árvore que satisfazem a dada comparação com o dado valor.
/// Retorna a quantidade de elementos encontrados.
/// Possíveis comparações:
///     0 -> a > b
///     1 -> a < b
///     2 -> a >= b
///     3 -> a <= b
size_t abp_comparar(abp_t* raiz, double valor, int comparacao, abp_valor_t* vetor, size_t tam);

/// Remove um elemento da ABP. Retorna a nova raíz da árvore binária.
abp_t* abp_remover(abp_t* raiz, abp_chave_t chave, abp_valor_t* valor);

/// Libera a ABP e todas suas subárvores.
void abp_liberar(abp_t* raiz);
