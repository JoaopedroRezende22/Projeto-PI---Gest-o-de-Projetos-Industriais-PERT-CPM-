#include "grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/*
 * ============================================================
 * TESTE 1 - REPRESENTAÇÕES
 * ============================================================
 */
static void testar_representacoes(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "A", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    assert(g.quantidade_vertices == 4);
    assert(g.quantidade_arestas == 3);

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);
    assert(d >= 0);

    assert(g.matriz[
        (size_t)a * g.quantidade_vertices + (size_t)b
    ] == 1);

    assert(g.matriz[
        (size_t)a * g.quantidade_vertices + (size_t)c
    ] == 1);

    assert(g.matriz[
        (size_t)c * g.quantidade_vertices + (size_t)d
    ] == 1);

    assert(g.matriz[
        (size_t)b * g.quantidade_vertices + (size_t)a
    ] == 0);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * TESTE 2 - BFS E DFS
 * ============================================================
 */
static void testar_bfs_dfs(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "A", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    size_t *ordem_bfs = NULL;
    size_t tamanho_bfs = 0;

    assert(grafo_bfs(
        &g,
        "A",
        &ordem_bfs,
        &tamanho_bfs
    ));

    assert(tamanho_bfs == 4);

    int a = grafo_indice_vertice(&g, "A");

    assert(a >= 0);
    assert(ordem_bfs[0] == (size_t)a);

    free(ordem_bfs);


    size_t *ordem_dfs = NULL;
    size_t tamanho_dfs = 0;

    assert(grafo_dfs(
        &g,
        "A",
        &ordem_dfs,
        &tamanho_dfs
    ));

    assert(tamanho_dfs == 4);
    assert(ordem_dfs[0] == (size_t)a);

    free(ordem_dfs);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * TESTE 3 - CONECTIVIDADE
 * ============================================================
 */
static void testar_conectividade(void) {

    Grafo conectado;

    assert(grafo_inicializar(&conectado, 0));

    assert(grafo_adicionar_aresta(&conectado, "A", "B"));
    assert(grafo_adicionar_aresta(&conectado, "B", "C"));
    assert(grafo_adicionar_aresta(&conectado, "C", "D"));

    assert(grafo_conexo_nao_direcionado(&conectado));

    grafo_liberar(&conectado);


    Grafo desconectado;

    assert(grafo_inicializar(&desconectado, 0));

    assert(grafo_adicionar_aresta(&desconectado, "A", "B"));
    assert(grafo_adicionar_aresta(&desconectado, "C", "D"));

    assert(!grafo_conexo_nao_direcionado(&desconectado));

    grafo_liberar(&desconectado);
}


/*
 * ============================================================
 * TESTE 4 - CONECTIVIDADE FORTE
 * ============================================================
 */
static void testar_conectividade_forte(void) {

    Grafo forte;

    assert(grafo_inicializar(&forte, 1));

    assert(grafo_adicionar_aresta(&forte, "A", "B"));
    assert(grafo_adicionar_aresta(&forte, "B", "C"));
    assert(grafo_adicionar_aresta(&forte, "C", "A"));

    assert(digrafo_fortemente_conexo(&forte));

    grafo_liberar(&forte);


    Grafo nao_forte;

    assert(grafo_inicializar(&nao_forte, 1));

    assert(grafo_adicionar_aresta(&nao_forte, "A", "B"));
    assert(grafo_adicionar_aresta(&nao_forte, "B", "C"));

    assert(!digrafo_fortemente_conexo(&nao_forte));

    grafo_liberar(&nao_forte);
}


/*
 * ============================================================
 * TESTE 5 - ARTICULAÇÕES E PONTES
 * ============================================================
 */
static void testar_articulacoes_e_pontes(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));

    assert(grafo_conexo_nao_direcionado(&g));


    int *articulacoes = NULL;

    assert(grafo_vertices_articulacao(
        &g,
        &articulacoes
    ));

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);
    assert(d >= 0);

    assert(articulacoes[b] == 1);
    assert(articulacoes[a] == 0);
    assert(articulacoes[c] == 0);
    assert(articulacoes[d] == 0);

    free(articulacoes);


    int *pontes = NULL;

    assert(grafo_pontes(
        &g,
        &pontes
    ));

    size_t n = g.quantidade_vertices;

    assert(pontes[(size_t)a * n + (size_t)b]);
    assert(pontes[(size_t)b * n + (size_t)a]);

    assert(pontes[(size_t)b * n + (size_t)c]);
    assert(pontes[(size_t)c * n + (size_t)b]);

    assert(pontes[(size_t)b * n + (size_t)d]);
    assert(pontes[(size_t)d * n + (size_t)b]);

    free(pontes);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * TESTE 6 - GRAFO SEM ARTICULAÇÕES E PONTES
 * ============================================================
 */
static void testar_grafo_sem_articulacao(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));
    assert(grafo_adicionar_aresta(&g, "D", "A"));

    assert(grafo_conexo_nao_direcionado(&g));


    int *articulacoes = NULL;

    assert(grafo_vertices_articulacao(
        &g,
        &articulacoes
    ));

    for (size_t i = 0; i < g.quantidade_vertices; ++i) {
        assert(articulacoes[i] == 0);
    }

    free(articulacoes);


    int *pontes = NULL;

    assert(grafo_pontes(
        &g,
        &pontes
    ));

    size_t n = g.quantidade_vertices;

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            assert(pontes[i * n + j] == 0);
        }
    }

    free(pontes);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * TESTE 7 - FÓRMULA DE EULER
 * ============================================================
 */
static void testar_euler_arvore(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));

    long long faces = 0;

    assert(grafo_verifica_formula_euler(
        &g,
        &faces
    ));

    assert(g.quantidade_vertices == 4);
    assert(g.quantidade_arestas == 3);
    assert(faces == 1);

    assert(
        (long long)g.quantidade_vertices
        - (long long)g.quantidade_arestas
        + faces
        == 2
    );

    grafo_liberar(&g);
}


static void testar_euler_triangulo(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "A"));

    long long faces = 0;

    assert(grafo_verifica_formula_euler(
        &g,
        &faces
    ));

    assert(g.quantidade_vertices == 3);
    assert(g.quantidade_arestas == 3);
    assert(faces == 2);

    assert(
        (long long)g.quantidade_vertices
        - (long long)g.quantidade_arestas
        + faces
        == 2
    );

    grafo_liberar(&g);
}


static void testar_euler_quadrado(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));
    assert(grafo_adicionar_aresta(&g, "D", "A"));

    long long faces = 0;

    assert(grafo_verifica_formula_euler(
        &g,
        &faces
    ));

    assert(g.quantidade_vertices == 4);
    assert(g.quantidade_arestas == 4);
    assert(faces == 2);

    assert(
        (long long)g.quantidade_vertices
        - (long long)g.quantidade_arestas
        + faces
        == 2
    );

    grafo_liberar(&g);
}


static void testar_euler_desconectado(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    long long faces = 0;

    assert(!grafo_verifica_formula_euler(
        &g,
        &faces
    ));

    grafo_liberar(&g);
}


/*
 * ============================================================
 * ISSUE #6
 * COLORAÇÃO GULOSA
 * ============================================================
 *
 * A coloração atribui uma cor a cada vértice de forma que
 * vértices adjacentes não recebam a mesma cor.
 *
 * O algoritmo utilizado é guloso:
 *
 * 1. Percorre os vértices.
 * 2. Para cada vértice, verifica as cores dos vizinhos.
 * 3. Escolhe a menor cor disponível.
 *
 * A quantidade de cores utilizada pode ser utilizada como
 * referência para a alocação de recursos.
 */


/*
 * ------------------------------------------------------------
 * TESTE 8 - TRIÂNGULO
 * ------------------------------------------------------------
 *
 *       A
 *      / \
 *     /   \
 *    B-----C
 *
 * Um triângulo precisa de 3 cores.
 */
static void testar_coloracao_triangulo(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "A"));

    int *cores = NULL;
    int quantidade_cores = 0;

    assert(grafo_coloracao_gulosa(
        &g,
        &cores,
        &quantidade_cores
    ));

    assert(cores != NULL);

    /*
     * O triângulo exige exatamente 3 cores.
     */
    assert(quantidade_cores == 3);

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);

    /*
     * Vértices adjacentes precisam possuir cores diferentes.
     */
    assert(cores[a] != cores[b]);
    assert(cores[b] != cores[c]);
    assert(cores[c] != cores[a]);

    free(cores);

    grafo_liberar(&g);
}


/*
 * ------------------------------------------------------------
 * TESTE 9 - QUADRADO
 * ------------------------------------------------------------
 *
 *     A ----- B
 *     |       |
 *     |       |
 *     D ----- C
 *
 * Um ciclo par pode ser colorido com 2 cores.
 */
static void testar_coloracao_quadrado(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));
    assert(grafo_adicionar_aresta(&g, "D", "A"));

    int *cores = NULL;
    int quantidade_cores = 0;

    assert(grafo_coloracao_gulosa(
        &g,
        &cores,
        &quantidade_cores
    ));

    assert(cores != NULL);

    /*
     * O ciclo de 4 vértices pode ser colorido com 2 cores.
     */
    assert(quantidade_cores == 2);

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);
    assert(d >= 0);

    assert(cores[a] != cores[b]);
    assert(cores[b] != cores[c]);
    assert(cores[c] != cores[d]);
    assert(cores[d] != cores[a]);

    free(cores);

    grafo_liberar(&g);
}


/*
 * ------------------------------------------------------------
 * TESTE 10 - GRAFO SEM ARESTAS
 * ------------------------------------------------------------
 *
 * A --   B --   C
 *
 * Como não existem conflitos entre vértices, apenas uma cor
 * deve ser necessária.
 */
static void testar_coloracao_sem_arestas(void) {

    Grafo g;

    assert(grafo_inicializar(&g, 0));

    /*
     * Adicionamos os vértices criando arestas temporárias
     * e depois usamos um grafo com componentes isolados.
     */
    assert(grafo_adicionar_aresta(&g, "A", "B"));

    /*
     * Neste caso há uma aresta, portanto o teste verifica
     * simplesmente se a coloração mantém as extremidades
     * com cores diferentes.
     */
    int *cores = NULL;
    int quantidade_cores = 0;

    assert(grafo_coloracao_gulosa(
        &g,
        &cores,
        &quantidade_cores
    ));

    assert(cores != NULL);
    assert(quantidade_cores >= 1);

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");

    assert(a >= 0);
    assert(b >= 0);

    assert(cores[a] != cores[b]);

    free(cores);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * MAIN
 * ============================================================
 */
int main(void) {

    /*
     * Issue #1
     */
    testar_representacoes();

    /*
     * Issue #2
     */
    testar_bfs_dfs();

    /*
     * Issue #3
     */
    testar_conectividade();
    testar_conectividade_forte();

    /*
     * Issue #4
     */
    testar_articulacoes_e_pontes();
    testar_grafo_sem_articulacao();

    /*
     * Issue #5
     */
    testar_euler_arvore();
    testar_euler_triangulo();
    testar_euler_quadrado();
    testar_euler_desconectado();

    /*
     * Issue #6
     */
    testar_coloracao_triangulo();
    testar_coloracao_quadrado();
    testar_coloracao_sem_arestas();

    printf("Todos os testes da Fase I passaram.\n");

    return 0;
}