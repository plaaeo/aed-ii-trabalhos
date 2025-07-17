#include "grafo.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t dim = grafo->tam * grafo->tam;
    size_t i = (a * grafo->tam) + b;

    // Medida de debug, apenas para garantir o uso correto de `grafo->adj`
    assert(i < dim);

    return i;
}

/// Cria um grafo vazio com o tamanho determinado.
grafo_t *grafo_criar(size_t tam) {
    grafo_t *grafo = (grafo_t *)malloc(sizeof(grafo_t));
    grafo->adj = calloc(tam * tam, sizeof(uint8_t));
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
        size_t *conexoes = malloc(tam * sizeof(size_t));

        // Gerar vetor de conexões básico, sem repetições
        for (size_t i = 0; i < tam; i++) {
            conexoes[i] = (i + 1) % tam;
        }

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
        free(conexoes);
    }

    // Máximo possível de arestas
    size_t max_arestas = (tam - 1) * tam / 2;

    // Quantidade de arestas que se deve gerar
    size_t alvo = grau * max_arestas;

    // Já temos um grafo com a quantidade adequada de arestas
    if (alvo <= arestas) return grafo;

    // Índice da próxima aresta livre
    size_t n = rand() % ((max_arestas - arestas) / (alvo - arestas));

    for (size_t i = 0; i < tam; i++) {
        for (size_t j = i + 1; j < tam; j++) {
            // Iterar apenas arestas livres
            if (grafo_tem_aresta(grafo, i, j)) continue;

            // Chegamos na aresta selecionada
            if (n-- == 0) {
                // Retornar caso tenhamos atingido o limite
                if (++arestas >= alvo) return grafo;

                grafo_definir_aresta(grafo, i, j, true);
                n = rand() % ((max_arestas - arestas) / (alvo - arestas));
            }
        }
    }

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

    grafo->adj[indice(grafo, a, b)] = valor ? 1 : 0;
    grafo->adj[indice(grafo, b, a)] = valor ? 1 : 0;
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

size_t *dfs(const grafo_t *grafo, size_t a, size_t *visita, size_t *ordem,
            size_t distancia) {
    *ordem = a;
    visita[a] = distancia;

    for (size_t vizinho = 0; vizinho < grafo->tam; vizinho++) {
        if (visita[vizinho] == SIZE_MAX &&
            grafo_tem_aresta(grafo, a, vizinho)) {
            ordem = dfs(grafo, vizinho, visita, ordem + 1, distancia + 1);
        }
    }

    return ordem;
}

/// Executa busca por profundindade, ou 'depth-first search', a partir de um nó
/// 'a'.
void grafo_dfs(const grafo_t *grafo, size_t a, size_t *dist, size_t *ordem) {
    // Inicializa todos os nós como não visitados
    for (size_t i = 0; i < grafo->tam; i++) {
        dist[i] = SIZE_MAX;
    }

    dfs(grafo, a, dist, ordem, 0);
};

typedef struct dfs_contexto_t {
    size_t indice;
    size_t *ordem;
    uint8_t *visitas;
    struct dfs_contexto_t *prox;
} dfs_ctx_t;

/// Copia o contexto dado.
dfs_ctx_t *dfs_ctx_fork(const grafo_t *grafo, dfs_ctx_t *orig) {
    dfs_ctx_t *copia = malloc(sizeof(dfs_ctx_t));
    copia->ordem = malloc(grafo->tam * sizeof(size_t));
    copia->visitas = malloc(grafo->tam * sizeof(uint8_t));

    // Inserir como próximo da origem
    copia->prox = orig->prox;
    orig->prox = copia;

    // Copiar dados do contexto original
    copia->indice = orig->indice;
    memcpy(copia->ordem, orig->ordem, orig->indice * sizeof(size_t));
    memcpy(copia->visitas, orig->visitas, grafo->tam * sizeof(uint8_t));

    // Definir todos os outros elementos da ordem como SIZE_MAX
    memset(&copia->ordem[copia->indice], -1,
           (grafo->tam - orig->indice) * sizeof(size_t));
    return copia;
}

/// Modificação da DFS para gerar todos os caminhos possíveis.
void dfs_caminhos(const grafo_t *grafo, size_t atual, dfs_ctx_t *ctx) {
    ctx->ordem[ctx->indice++] = atual;
    ctx->visitas[atual] = 1;

    // Contar todos os vizinhos
    size_t n_vizinhos = 0;
    for (size_t vizinho = 0; vizinho < grafo->tam; vizinho++) {
        // Ignorar nós visitados/desconectados
        if (ctx->visitas[vizinho] == 1 ||
            !grafo_tem_aresta(grafo, atual, vizinho)) {
            continue;
        }

        n_vizinhos++;
    }

    for (size_t vizinho = 0; vizinho < grafo->tam; vizinho++) {
        // Ignorar nós visitados/desconectados
        if (ctx->visitas[vizinho] == 1 ||
            !grafo_tem_aresta(grafo, atual, vizinho)) {
            continue;
        }

        // Clonar contexto caso não seja o último vizinho
        if (--n_vizinhos > 0) {
            dfs_ctx_t *copia = dfs_ctx_fork(grafo, ctx);
            dfs_caminhos(grafo, vizinho, copia);
        } else {
            dfs_caminhos(grafo, vizinho, ctx);
        }
    }
}

/// Utiliza busca por profundidade para calcular todos os caminhos possíveis no
/// grafo.
size_t **grafo_calcular_caminhos(const grafo_t *grafo, size_t origem,
                                 size_t *quantos) {
    dfs_ctx_t *inicial = malloc(sizeof(dfs_ctx_t));
    inicial->indice = 0;
    inicial->ordem = malloc(grafo->tam * sizeof(size_t));
    inicial->visitas = calloc(grafo->tam, sizeof(uint8_t));
    inicial->prox = NULL;

    // Definir todos os elementos da ordem como SIZE_MAX
    memset(inicial->ordem, -1, grafo->tam * sizeof(size_t));

    // Calcular caminhos
    dfs_caminhos(grafo, origem, inicial);

    // Contar quantos caminhos existem
    size_t n_caminhos = 0;
    for (dfs_ctx_t *i = inicial; i != NULL; i = i->prox) {
        n_caminhos++;
    }

    // Gerar matriz
    size_t j = 0;
    size_t **matriz = calloc(n_caminhos, sizeof(size_t *));
    for (dfs_ctx_t *i = inicial; i != NULL;) {
        matriz[j++] = i->ordem;

        // Liberar memória do dfs_ctx_t
        dfs_ctx_t *old_i = i;
        i = i->prox;
        free(old_i->visitas);
        free(old_i);
    }

    *quantos = n_caminhos;
    return matriz;
};

/// Função auxiliar de DFS para detecção de ciclos
bool dfs_ciclo(const grafo_t *grafo, size_t atual, size_t pai, bool *visitado) {
    visitado[atual] = true;

    for (size_t vizinho = 0; vizinho < grafo->tam; vizinho++) {
        if (grafo_tem_aresta(grafo, atual, vizinho)) {
            if (!visitado[vizinho]) {
                if (dfs_ciclo(grafo, vizinho, atual, visitado)) {
                    return true;
                }
            } else if (vizinho != pai) {
                return true;  // Encontrou um ciclo (tamanho ≥ 3)
            }
        }
    }

    return false;
}

/// Retorna verdadeiro se o grafo contiver um ciclo de tamanho >= 3.
bool grafo_tem_ciclo(const grafo_t *grafo) {
    size_t n = grafo_tamanho(grafo);
    bool *visitado = calloc(n, sizeof(bool));
    if (!visitado) return false;

    for (size_t i = 0; i < n; i++) {
        if (!visitado[i]) {
            if (dfs_ciclo(grafo, i, (size_t)-1, visitado)) {
                free(visitado);
                return true;
            }
        }
    }

    free(visitado);
    return false;
}

/// Imprime todos os nós adjacentes ao nó dado.
void grafo_imprimir_no(const grafo_t *grafo, size_t a, FILE *saida) {
    if (a >= grafo->tam) return;

    // Garantir saída padrão caso saída seja NULL
    if (saida == NULL) {
        saida = stdout;
    }

    for (size_t b = 0; b < grafo->tam; b++) {
        bool adj = grafo_tem_aresta(grafo, a, b);

        // Imprime o par 'a' e 'b'
        if (adj) fprintf(saida, "%lu %lu\n", a, b);
    }
}

/// Imprime a matriz de adjacência do grafo, usado para verificar
/// visualmente a conectividade do grafo.
void grafo_imprimir_matriz(const grafo_t *grafo, FILE *saida) {
    // Garantir saída padrão caso saída seja NULL
    if (saida == NULL) {
        saida = stdout;
    }

    for (size_t i = 0; i < grafo->tam; i++) {
        for (size_t j = 0; j < grafo->tam; j++) {
            bool adj = grafo_tem_aresta(grafo, i, j);
            fprintf(saida, "%1hhu ", adj);
        }

        fprintf(saida, "\n");
    }
};

/// Imprime todas as arestas do grafo, usado para renderizar o grafo em
/// qualquer programa visualisador externo.
void grafo_imprimir_arestas(const grafo_t *grafo, FILE *saida) {
    // Garantir saída padrão caso saída seja NULL
    if (saida == NULL) {
        saida = stdout;
    }

    // Similar ao `grafo_imprimir_no`, porém sem redundâncias.
    for (size_t a = 0; a < grafo->tam; a++) {
        for (size_t b = a; b < grafo->tam; b++) {
            bool adj = grafo_tem_aresta(grafo, a, b);

            // Imprime o par 'a' e 'b'
            if (adj) {
                fprintf(saida, "%lu %lu\n", a, b);
            }
        }
    }
};

/// Retorna a quantidade de nós no grafo.
size_t grafo_tamanho(const grafo_t *grafo) {
    return grafo->tam;
}
