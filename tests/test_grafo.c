#include "grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * ============================================================
 * TESTES DA FASE I
 * ============================================================
 *
 * Este arquivo reúne os testes das Issues:
 *
 * #1 - Representações do grafo
 * #2 - BFS e DFS
 * #3 - Conectividade
 * #4 - Vértices de articulação e pontes
 * #5 - Fórmula de Euler
 *
 * Os testes utilizam a API real do projeto.
 */


/*
 * ============================================================
 * ISSUE #1
 * Representações do grafo
 * ============================================================
 */
static void testar_representacoes(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    /*
     * Grafo direcionado:
     *
     * A -> B
     * A -> C
     * C -> D
     */
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

    /*
     * Verifica a matriz de adjacência.
     */
    assert(g.matriz[(size_t)a * g.quantidade_vertices + (size_t)b] == 1);
    assert(g.matriz[(size_t)a * g.quantidade_vertices + (size_t)c] == 1);
    assert(g.matriz[(size_t)c * g.quantidade_vertices + (size_t)d] == 1);

    /*
     * Como o grafo é direcionado, as arestas inversas
     * não devem existir.
     */
    assert(g.matriz[(size_t)b * g.quantidade_vertices + (size_t)a] == 0);
    assert(g.matriz[(size_t)c * g.quantidade_vertices + (size_t)a] == 0);
    assert(g.matriz[(size_t)d * g.quantidade_vertices + (size_t)c] == 0);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * ISSUE #2
 * BFS e DFS
 * ============================================================
 */
static void testar_bfs_dfs(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    /*
     *        B
     *       / \
     *      A   D
     *       \ /
     *        C
     *
     * A -> B
     * A -> C
     * B -> D
     * C -> D
     */
    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "A", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    /*
     * BFS a partir de A.
     */
    size_t *ordem_bfs = NULL;
    size_t tamanho_bfs = 0;

    assert(grafo_bfs(
        &g,
        "A",
        &ordem_bfs,
        &tamanho_bfs
    ));

    assert(tamanho_bfs == 4);

    /*
     * O BFS deve visitar os 4 vértices.
     */
    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);
    assert(d >= 0);

    assert(ordem_bfs[0] == (size_t)a);

    free(ordem_bfs);

    /*
     * DFS a partir de A.
     */
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
 * ISSUE #3
 * Conectividade
 * ============================================================
 */
static void testar_conectividade(void) {

    /*
     * --------------------------------------------------------
     * Caso 1:
     * Grafo não direcionado conectado
     * --------------------------------------------------------
     *
     * A -- B -- C -- D
     */
    Grafo conectado;

    assert(grafo_inicializar(&conectado, 0));

    assert(grafo_adicionar_aresta(&conectado, "A", "B"));
    assert(grafo_adicionar_aresta(&conectado, "B", "C"));
    assert(grafo_adicionar_aresta(&conectado, "C", "D"));

    assert(grafo_conexo_nao_direcionado(&conectado));

    grafo_liberar(&conectado);


    /*
     * --------------------------------------------------------
     * Caso 2:
     * Grafo não direcionado desconectado
     * --------------------------------------------------------
     *
     * A -- B
     *
     * C -- D
     */
    Grafo desconectado;

    assert(grafo_inicializar(&desconectado, 0));

    assert(grafo_adicionar_aresta(&desconectado, "A", "B"));
    assert(grafo_adicionar_aresta(&desconectado, "C", "D"));

    assert(!grafo_conexo_nao_direcionado(&desconectado));

    grafo_liberar(&desconectado);
}


/*
 * ============================================================
 * ISSUE #3
 * Conectividade forte em digrafo
 * ============================================================
 */
static void testar_conectividade_forte(void) {

    /*
     * --------------------------------------------------------
     * Caso 1:
     * Digrafo fortemente conexo
     * --------------------------------------------------------
     *
     * A -> B -> C
     * ^         |
     * |_________|
     */
    Grafo forte;

    assert(grafo_inicializar(&forte, 1));

    assert(grafo_adicionar_aresta(&forte, "A", "B"));
    assert(grafo_adicionar_aresta(&forte, "B", "C"));
    assert(grafo_adicionar_aresta(&forte, "C", "A"));

    assert(digrafo_fortemente_conexo(&forte));

    grafo_liberar(&forte);


    /*
     * --------------------------------------------------------
     * Caso 2:
     * Digrafo NÃO fortemente conexo
     * --------------------------------------------------------
     *
     * A -> B -> C
     */
    Grafo nao_forte;

    assert(grafo_inicializar(&nao_forte, 1));

    assert(grafo_adicionar_aresta(&nao_forte, "A", "B"));
    assert(grafo_adicionar_aresta(&nao_forte, "B", "C"));

    assert(!digrafo_fortemente_conexo(&nao_forte));

    grafo_liberar(&nao_forte);
}


/*
 * ============================================================
 * ISSUE #4
 * Vértices de articulação e pontes
 * ============================================================
 */
static void testar_articulacoes_e_pontes(void) {

    /*
     * Grafo:
     *
     *       C
     *       |
     * A --- B --- D
     *
     * B é vértice de articulação.
     *
     * A-B, B-C e B-D são pontes.
     */
    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));

    /*
     * Verifica conectividade.
     */
    assert(grafo_conexo_nao_direcionado(&g));

    /*
     * Verifica vértices de articulação.
     */
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

    /*
     * Verifica pontes.
     */
    int *pontes = NULL;

    assert(grafo_pontes(
        &g,
        &pontes
    ));

    size_t n = g.quantidade_vertices;

    assert(pontes[
        (size_t)a * n + (size_t)b
    ]);

    assert(pontes[
        (size_t)b * n + (size_t)a
    ]);

    assert(pontes[
        (size_t)b * n + (size_t)c
    ]);

    assert(pontes[
        (size_t)c * n + (size_t)b
    ]);

    assert(pontes[
        (size_t)b * n + (size_t)d
    ]);

    assert(pontes[
        (size_t)d * n + (size_t)b
    ]);

    free(pontes);

    grafo_liberar(&g);
}


/*
 * ============================================================
 * ISSUE #4
 * Grafo sem articulação e sem pontes
 * ============================================================
 */
static void testar_grafo_sem_articulacao(void) {

    /*
     * Grafo em ciclo:
     *
     * A ---- B
     * |      |
     * |      |
     * D ---- C
     */
    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));
    assert(grafo_adicionar_aresta(&g, "D", "A"));

    /*
     * O ciclo é conectado.
     */
    assert(grafo_conexo_nao_direcionado(&g));

    /*
     * Nenhum vértice deve ser de articulação.
     */
    int *articulacoes = NULL;

    assert(grafo_vertices_articulacao(
        &g,
        &articulacoes
    ));

    for (size_t i = 0; i < g.quantidade_vertices; ++i) {
        assert(articulacoes[i] == 0);
    }

    free(articulacoes);

    /*
     * Nenhuma aresta deve ser ponte.
     */
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
 * ISSUE #5
 * Fórmula de Euler
 * ============================================================
 *
 * Para um grafo planar conexo:
 *
 *              V - E + F = 2
 *
 * onde:
 *
 * V = número de vértices
 * E = número de arestas
 * F = número de faces
 *
 * A função do projeto calcula:
 *
 *              F = E - V + 2
 *
 * e verifica condições necessárias relacionadas à planaridade.
 *
 * IMPORTANTE:
 *
 * Essa função NÃO é um algoritmo completo de teste de
 * planaridade.
 */


/*
 * ------------------------------------------------------------
 * Caso 1:
 * Árvore
 * ------------------------------------------------------------
 *
 *     A
 *     |
 *     B
 *    / \
 *   C   D
 *
 * V = 4
 * E = 3
 *
 * F = E - V + 2
 * F = 3 - 4 + 2
 * F = 1
 *
 * Portanto:
 *
 * V - E + F = 4 - 3 + 1 = 2
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


/*
 * ------------------------------------------------------------
 * Caso 2:
 * Triângulo
 * ------------------------------------------------------------
 *
 *       A
 *      / \
 *     /   \
 *    B-----C
 *
 * V = 3
 * E = 3
 *
 * F = 3 - 3 + 2
 * F = 2
 *
 * Temos:
 *
 * 1 face interna
 * 1 face externa
 *
 * Portanto:
 *
 * V - E + F = 3 - 3 + 2 = 2
 */
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


/*
 * ------------------------------------------------------------
 * Caso 3:
 * Quadrado
 * ------------------------------------------------------------
 *
 *     A ----- B
 *     |       |
 *     |       |
 *     D ----- C
 *
 * V = 4
 * E = 4
 *
 * F = 4 - 4 + 2
 * F = 2
 *
 * Portanto:
 *
 * V - E + F = 4 - 4 + 2 = 2
 */
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


/*
 * ------------------------------------------------------------
 * Caso 4:
 * Grafo desconectado
 * ------------------------------------------------------------
 *
 * A --- B
 *
 * C --- D
 *
 * A função da Fórmula de Euler do projeto exige que o grafo
 * seja conexo. Portanto, esperamos falha.
 */
static void testar_euler_grafo_desconectado(void) {

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
 * MAIN DOS TESTES
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
    testar_euler_grafo_desconectado();

    printf("Todos os testes da Fase I passaram.\n");

    return 0;
}