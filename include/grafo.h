#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/// TAD para um grafo não direcionado de tamanho constante.
typedef struct grafo_t grafo_t;

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam);

/// Gera um grafo garantidamente conexo com o tamanho e grau de
/// conectividade pedido.
grafo_t *grafo_criar_conexo(size_t tam, float grau);

/// Libera a memória alocada para o grafo dado.
void grafo_free(grafo_t *grafo);

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor);

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b);

/// Executa busca por largura, ou 'breadth-first search', a partir de um nó 'a'.
/// O resultado é armazenado no vetor passado no argumento 'dist', que deve ter
/// o mesmo tamanho que o numero de nós do grafo.
/// 'dist' contem, para cada posição `i`, a distância do nó `i` até a origem
/// selecionada.
void grafo_bfs(const grafo_t *grafo, size_t a, size_t *dist);

/// Executa busca por profundidade, ou 'depth-first search', a partir de um nó
/// 'a'. O resultado é armazenado no vetors passados nos argumentos 'dist' e
/// 'ordem', que devem ter o mesmo tamanho que o numero de nós do grafo.
///
/// 'dist' contem, para cada posição `i`, a distância do nó `i` até a origem
/// selecionada;
/// 'ordem' contém a ordem de visita dos nós.
void grafo_dfs(const grafo_t *grafo, size_t a, size_t *dist, size_t *ordem);

/// Retorna verdadeiro se o grafo contiver um ciclo de tamanho >= 3.
bool grafo_tem_ciclo(const grafo_t *grafo);

/// Imprime no arquivo dado todos os nós adjacentes ao nó dado.
/// Caso `NULL` seja passado como arquivo, imprimirá na saída padrão.
void grafo_imprimir_no(const grafo_t *grafo, size_t a, FILE *saida);

/// Imprime no arquivo dado a matriz de adjacência do grafo,
/// usado para validar visualmente a conectividade do grafo.
/// Caso `NULL` seja passado como arquivo, imprimirá na saída padrão.
void grafo_imprimir_matriz(const grafo_t *grafo, FILE *saida);

/// Imprime no arquivo dado todas as arestas do grafo, usado para
/// renderizar o grafo em qualquer programa visualisador externo.
/// Caso `NULL` seja passado como arquivo, imprimirá na saída padrão.
void grafo_imprimir_arestas(const grafo_t *grafo, FILE *saida);

/// Retorna a quantidade de nós no grafo.
size_t grafo_tamanho(const grafo_t *grafo);
