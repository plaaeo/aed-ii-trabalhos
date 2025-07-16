#include "grafo.h"

#include <stdint.h>
#include <stdio.h>

#include "fila.h"

/// TAD para um grafo não direcionado de tamanho constante.
struct grafo_t {
    /// Matriz de adjacência para cada nó do grafo.
    uint8_t *adj;

    /// A quantidade de nós do grafo.
    size_t tam;
};

/// Calcula o índice da aresta a->b na matriz de adjacência do grafo.
size_t indice(const grafo_t *grafo, size_t a, size_t b) {
    return a * grafo->tam + b;
}

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam) {
    grafo_t *grafo = (grafo_t *)malloc(sizeof(grafo_t));
    grafo->adj = malloc(tam * tam * sizeof(uint8_t));
    grafo->tam = tam;
    return grafo;
}

/// Gera um grafo garantidamente conexo com o tamanho e grau de
/// conectividade pedido.
grafo_t *grafo_criar_conexo(size_t tam, float grau) {
    grafo_t *grafo = grafo_criar(tam);

    size_t arestas = 0;

    // - Garantir que o grafo é conexo -
    {
        // Vetor de conexões a serem feitas no grafo.
        // Cada nó em 'conexoes[i]' se conecta ao nó 'conexoes[i + 1]'
        size_t conexoes[tam];

        // Gerar vetor de conexões básico, sem repetições
        for (size_t i = 0; i < tam; i++) conexoes[i] = (i + 1) % tam;

        // Embaralhar vetor
        for (size_t i = 0; i < tam; i++) {
            size_t j = rand() % tam;
            size_t a = conexoes[i];
            conexoes[i] = conexoes[j];
            conexoes[j] = a;
        }

        // Conectar todos os nós
        for (size_t i = 1; i < tam; i++) {
            // Poderiamos sempre selecionar um nó anterior aleatório,
            // mas o grafo ficaria aleatório demais, e se sempre selecionarmos
            // o nó anterior para conexão, o grafo viraria uma linha.
            if (rand() % 3) {
                grafo_definir_aresta(grafo, conexoes[i], conexoes[rand() % i],
                                     true);
            } else {
                grafo_definir_aresta(grafo, conexoes[i], conexoes[i - 1], true);
            }
        }

        arestas = grafo->tam - 1;
    }

    // Quantidade de arestas que se deve gerar
    size_t alvo = grau * (tam - 1) * tam / 2;
    for (; arestas < alvo; arestas++) {
        // Gerar um par novo até que não seja definido e não seja da diagonal
        size_t i, j;
        do {
            i = rand() % tam;
            j = rand() % tam;
        } while (i == j || grafo->adj[indice(grafo, i, j)]);

        // Definir uma aresta aleatória
        grafo_definir_aresta(grafo, i, j, true);
    }

    for (size_t i = 0; i < tam; i++) {
        for (size_t j = 0; j < tam; j++) {
            printf("%1hhu ", grafo->adj[indice(grafo, i, j)]);
        }
        printf("\n");
    }
    printf("\n");

    return grafo;
}

/// Libera a memória alocada para o grafo dado.
void grafo_free(grafo_t *grafo) {
    if (!grafo) return;

    free(grafo->adj);
    free(grafo);
}

/// Define se há ou não aresta entre os nós a e b no grafo.
void grafo_definir_aresta(grafo_t *grafo, size_t a, size_t b, bool valor) {
    if (a >= grafo->tam || b >= grafo->tam) return;

    grafo->adj[indice(grafo, a, b)] = valor;
    grafo->adj[indice(grafo, b, a)] = valor;
}

/// Verifica se há aresta entre os nós a e b no grafo.
bool grafo_tem_aresta(const grafo_t *grafo, size_t a, size_t b) {
    if (a >= grafo->tam || b >= grafo->tam) return false;

    return grafo->adj[indice(grafo, a, b)];
}

/// Executa busca por largura, ou 'breadth-first search', a partir de um nó 'a'.
void grafo_bfs(const grafo_t *grafo, size_t a, size_t *dist) {
    // Criar fila
    fila_t *fila = fila_criar(grafo->tam);
    if (!fila) return;

    // Inicializa distâncias
    for (size_t i = 0; i < grafo->tam; i++) {
        dist[i] = SIZE_MAX;
    }

    // Inicializar BFS
    dist[a] = 0;
    fila_inserir(fila, a);

    size_t atual;
    while (fila_remover(fila, &atual)) {
        for (size_t vizinho = 0; vizinho < grafo->tam; vizinho++) {
            if (grafo_tem_aresta(grafo, atual, vizinho)) {
                if (dist[vizinho] == SIZE_MAX) {
                    dist[vizinho] = dist[atual] + 1;
                    if (!fila_inserir(fila, vizinho)) {
                        fila_liberar(fila);
                        return;
                    }
                }
            }
        }
    }

    fila_liberar(fila);
};

void dfs(const grafo_t *grafo, size_t a, size_t *visita, size_t ordem) {
    visita[a] = ordem;

    for (size_t vizinho = 0; vizinho < grafo_tamanho(grafo); vizinho++) {
        if (grafo_tem_aresta(grafo, a, vizinho) &&
            visita[vizinho] == SIZE_MAX) {
            dfs(grafo, vizinho, visita, ordem + 1);
        }
    }
}

/// Executa busca por profundindade, ou 'depth-first search', a partir de um nó
/// 'a'.
void grafo_dfs(const grafo_t *grafo, size_t a, size_t *dist) {
    // Inicializa todos os nós como não visitados
    for (size_t i = 0; i < grafo->tam; i++) {
        dist[i] = SIZE_MAX;
    }

    return dfs(grafo, a, dist, 0);
};

/// Imprime todos os nós adjacentes ao nó dado.
void grafo_imprimir_no(const grafo_t *grafo, size_t a) {
    if (a >= grafo->tam) return;

    for (size_t b = 0; b < grafo->tam; b++) {
        bool adj = grafo->adj[indice(grafo, a, b)];

        // Imprime o par 'a' e 'b'
        if (adj) printf("%lu %lu\n", a, b);
    }
}

/// Retorna a quantidade de nós no grafo.
size_t grafo_tamanho(const grafo_t *grafo) {
    return grafo->tam;
}
