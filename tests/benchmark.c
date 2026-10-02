#include "grafo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATASET_PATH "data/dataset_1000.txt"
#define REPETICOES 30

static int carregar_dataset(const char *caminho, Grafo *g) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        perror("Erro ao abrir dataset");
        return 0;
    }

    char linha[256];
    char tipo[32];
    char origem[64];
    char destino[64];
    int duracao;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[0] == '#' || linha[0] == '\n' || linha[0] == '\r') {
            continue;
        }

        if (sscanf(linha, "%31s", tipo) != 1) {
            continue;
        }

        if (strcmp(tipo, "TAREFA") == 0) {
            if (sscanf(linha, "%31s %63s %d", tipo, origem, &duracao) == 3) {
                if (!grafo_definir_duracao(g, origem, duracao)) {
                    fclose(arquivo);
                    return 0;
                }
            }
        } else if (strcmp(tipo, "ARESTA") == 0) {
            if (sscanf(linha, "%31s %63s %63s", tipo, origem, destino) == 3) {
                if (!grafo_adicionar_aresta(g, origem, destino)) {
                    fclose(arquivo);
                    return 0;
                }
            }
        }
    }

    fclose(arquivo);
    return 1;
}

static double tempo_ms(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio) * 1000.0) / (double)CLOCKS_PER_SEC;
}

/* BFS usando a lista de adjacencia. */
static size_t bfs_lista(const Grafo *g, size_t inicio) {
    size_t n = g->quantidade_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    size_t *fila = (size_t *)malloc(n * sizeof(size_t));

    if (!visitado || !fila) {
        free(visitado);
        free(fila);
        return 0;
    }

    size_t ini = 0;
    size_t fim = 0;
    size_t visitados = 0;

    visitado[inicio] = 1;
    fila[fim++] = inicio;

    while (ini < fim) {
        size_t u = fila[ini++];
        visitados++;

        for (Adjacente *a = g->vertices[u].lista; a; a = a->proximo) {
            if (!visitado[a->destino]) {
                visitado[a->destino] = 1;
                fila[fim++] = a->destino;
            }
        }
    }

    free(visitado);
    free(fila);
    return visitados;
}

/* DFS usando a lista de adjacencia. */
static void dfs_lista_rec(const Grafo *g, size_t u, int *visitado, size_t *contador) {
    visitado[u] = 1;
    (*contador)++;

    for (Adjacente *a = g->vertices[u].lista; a; a = a->proximo) {
        if (!visitado[a->destino]) {
            dfs_lista_rec(g, a->destino, visitado, contador);
        }
    }
}

static size_t dfs_lista(const Grafo *g, size_t inicio) {
    int *visitado = (int *)calloc(g->quantidade_vertices, sizeof(int));
    if (!visitado) {
        return 0;
    }

    size_t contador = 0;
    dfs_lista_rec(g, inicio, visitado, &contador);

    free(visitado);
    return contador;
}

/* BFS usando a matriz de adjacencia. */
static size_t bfs_matriz(const Grafo *g, size_t inicio) {
    size_t n = g->quantidade_vertices;
    int *visitado = (int *)calloc(n, sizeof(int));
    size_t *fila = (size_t *)malloc(n * sizeof(size_t));

    if (!visitado || !fila) {
        free(visitado);
        free(fila);
        return 0;
    }

    size_t ini = 0;
    size_t fim = 0;
    size_t visitados = 0;

    visitado[inicio] = 1;
    fila[fim++] = inicio;

    while (ini < fim) {
        size_t u = fila[ini++];
        visitados++;

        for (size_t v = 0; v < n; ++v) {
            if (g->matriz[u * n + v] && !visitado[v]) {
                visitado[v] = 1;
                fila[fim++] = v;
            }
        }
    }

    free(visitado);
    free(fila);
    return visitados;
}

/* DFS usando a matriz de adjacencia. */
static void dfs_matriz_rec(const Grafo *g, size_t u, int *visitado, size_t *contador) {
    size_t n = g->quantidade_vertices;

    visitado[u] = 1;
    (*contador)++;

    for (size_t v = 0; v < n; ++v) {
        if (g->matriz[u * n + v] && !visitado[v]) {
            dfs_matriz_rec(g, v, visitado, contador);
        }
    }
}

static size_t dfs_matriz(const Grafo *g, size_t inicio) {
    int *visitado = (int *)calloc(g->quantidade_vertices, sizeof(int));
    if (!visitado) {
        return 0;
    }

    size_t contador = 0;
    dfs_matriz_rec(g, inicio, visitado, &contador);

    free(visitado);
    return contador;
}

static double medir_bfs_lista(const Grafo *g, size_t inicio, size_t *resultado) {
    clock_t inicio_tempo = clock();

    size_t total = 0;
    for (int i = 0; i < REPETICOES; ++i) {
        total += bfs_lista(g, inicio);
    }

    clock_t fim_tempo = clock();

    *resultado = total / REPETICOES;
    return tempo_ms(inicio_tempo, fim_tempo) / REPETICOES;
}

static double medir_dfs_lista(const Grafo *g, size_t inicio, size_t *resultado) {
    clock_t inicio_tempo = clock();

    size_t total = 0;
    for (int i = 0; i < REPETICOES; ++i) {
        total += dfs_lista(g, inicio);
    }

    clock_t fim_tempo = clock();

    *resultado = total / REPETICOES;
    return tempo_ms(inicio_tempo, fim_tempo) / REPETICOES;
}

static double medir_bfs_matriz(const Grafo *g, size_t inicio, size_t *resultado) {
    clock_t inicio_tempo = clock();

    size_t total = 0;
    for (int i = 0; i < REPETICOES; ++i) {
        total += bfs_matriz(g, inicio);
    }

    clock_t fim_tempo = clock();

    *resultado = total / REPETICOES;
    return tempo_ms(inicio_tempo, fim_tempo) / REPETICOES;
}

static double medir_dfs_matriz(const Grafo *g, size_t inicio, size_t *resultado) {
    clock_t inicio_tempo = clock();

    size_t total = 0;
    for (int i = 0; i < REPETICOES; ++i) {
        total += dfs_matriz(g, inicio);
    }

    clock_t fim_tempo = clock();

    *resultado = total / REPETICOES;
    return tempo_ms(inicio_tempo, fim_tempo) / REPETICOES;
}

static size_t memoria_estimada_lista(const Grafo *g) {
    size_t bytes = g->capacidade_vertices * sizeof(Vertice);

    for (size_t i = 0; i < g->quantidade_vertices; ++i) {
        for (Adjacente *a = g->vertices[i].lista; a; a = a->proximo) {
            bytes += sizeof(Adjacente);
        }
    }

    return bytes;
}

static size_t memoria_estimada_matriz(const Grafo *g) {
    return g->quantidade_vertices *
           g->quantidade_vertices *
           sizeof(int);
}

int main(void) {
    Grafo g;

    if (!grafo_inicializar(&g, 1)) {
        fprintf(stderr, "Erro ao inicializar o grafo.\n");
        return EXIT_FAILURE;
    }

    if (!carregar_dataset(DATASET_PATH, &g)) {
        fprintf(stderr, "Erro ao carregar %s\n", DATASET_PATH);
        grafo_liberar(&g);
        return EXIT_FAILURE;
    }

    printf("==============================================\n");
    printf(" BENCHMARK - DATASET 1000\n");
    printf("==============================================\n");
    printf("Arquivo: %s\n", DATASET_PATH);
    printf("Vertices: %zu\n", g.quantidade_vertices);
    printf("Arestas:  %zu\n", g.quantidade_arestas);
    printf("Repeticoes por algoritmo: %d\n\n", REPETICOES);

    if (g.quantidade_vertices != 1000) {
        fprintf(stderr,
                "ERRO: o dataset deveria possuir 1000 vertices, mas possui %zu.\n",
                g.quantidade_vertices);
        grafo_liberar(&g);
        return EXIT_FAILURE;
    }

    size_t inicio = (size_t)grafo_indice_vertice(&g, "T0001");
    if ((int)inicio < 0) {
        fprintf(stderr, "Erro: vertice T0001 nao encontrado.\n");
        grafo_liberar(&g);
        return EXIT_FAILURE;
    }

    size_t resultado_bfs_lista = 0;
    size_t resultado_dfs_lista = 0;
    size_t resultado_bfs_matriz = 0;
    size_t resultado_dfs_matriz = 0;

    double bfs_lista_ms =
        medir_bfs_lista(&g, inicio, &resultado_bfs_lista);

    double dfs_lista_ms =
        medir_dfs_lista(&g, inicio, &resultado_dfs_lista);

    double bfs_matriz_ms =
        medir_bfs_matriz(&g, inicio, &resultado_bfs_matriz);

    double dfs_matriz_ms =
        medir_dfs_matriz(&g, inicio, &resultado_dfs_matriz);

    printf("--- Lista de adjacencia ---\n");
    printf("BFS: %.6f ms (vertices visitados: %zu)\n",
           bfs_lista_ms, resultado_bfs_lista);
    printf("DFS: %.6f ms (vertices visitados: %zu)\n",
           dfs_lista_ms, resultado_dfs_lista);
    printf("Memoria estrutural estimada: %zu bytes (%.2f KB)\n\n",
           memoria_estimada_lista(&g),
           memoria_estimada_lista(&g) / 1024.0);

    printf("--- Matriz de adjacencia ---\n");
    printf("BFS: %.6f ms (vertices visitados: %zu)\n",
           bfs_matriz_ms, resultado_bfs_matriz);
    printf("DFS: %.6f ms (vertices visitados: %zu)\n",
           dfs_matriz_ms, resultado_dfs_matriz);
    printf("Memoria estimada da matriz: %zu bytes (%.2f KB)\n\n",
           memoria_estimada_matriz(&g),
           memoria_estimada_matriz(&g) / 1024.0);

    if (resultado_bfs_lista != resultado_bfs_matriz ||
        resultado_dfs_lista != resultado_dfs_matriz) {
        fprintf(stderr,
                "ERRO: as representacoes produziram resultados diferentes.\n");
        grafo_liberar(&g);
        return EXIT_FAILURE;
    }

    printf("--- Validacao ---\n");
    printf("BFS lista x matriz: OK\n");
    printf("DFS lista x matriz: OK\n");
    printf("Dataset com 1000 vertices: OK\n");

    grafo_liberar(&g);
    return EXIT_SUCCESS;
}
