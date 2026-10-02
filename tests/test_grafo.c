#include "grafo.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void testar_representacoes(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "A", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(a >= 0);
    assert(b >= 0);
    assert(c >= 0);
    assert(d >= 0);

    assert(g.matriz[(size_t)a * g.quantidade_vertices + (size_t)b] == 1);
    assert(g.matriz[(size_t)a * g.quantidade_vertices + (size_t)c] == 1);
    assert(g.matriz[(size_t)b * g.quantidade_vertices + (size_t)d] == 1);
    assert(g.matriz[(size_t)c * g.quantidade_vertices + (size_t)d] == 1);

    assert(g.matriz[(size_t)b * g.quantidade_vertices + (size_t)a] == 0);
    assert(g.matriz[(size_t)c * g.quantidade_vertices + (size_t)a] == 0);
    assert(g.matriz[(size_t)d * g.quantidade_vertices + (size_t)a] == 0);

    assert(g.quantidade_vertices == 4);
    assert(g.quantidade_arestas == 4);

    grafo_liberar(&g);
}

static void testar_dag(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));
    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "A", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    size_t *ordem = NULL;
    size_t tamanho = 0;

    assert(grafo_bfs(&g, "A", &ordem, &tamanho));
    assert(tamanho == 4);

    assert(strcmp(g.vertices[ordem[0]].rotulo, "A") == 0);
    assert(strcmp(g.vertices[ordem[1]].rotulo, "C") == 0);
    assert(strcmp(g.vertices[ordem[2]].rotulo, "B") == 0);
    assert(strcmp(g.vertices[ordem[3]].rotulo, "D") == 0);

    free(ordem);

    ordem = NULL;
    tamanho = 0;

    assert(grafo_dfs(&g, "A", &ordem, &tamanho));
    assert(tamanho == 4);

    assert(strcmp(g.vertices[ordem[0]].rotulo, "A") == 0);
    assert(strcmp(g.vertices[ordem[1]].rotulo, "C") == 0);
    assert(strcmp(g.vertices[ordem[2]].rotulo, "D") == 0);
    assert(strcmp(g.vertices[ordem[3]].rotulo, "B") == 0);

    free(ordem);

    ordem = NULL;
    tamanho = 0;

    assert(grafo_ordenacao_topologica_kahn(&g, &ordem, &tamanho));
    assert(tamanho == 4);
    free(ordem);

    ordem = NULL;
    tamanho = 0;

    assert(grafo_ordenacao_topologica_dfs(&g, &ordem, &tamanho));
    assert(tamanho == 4);
    free(ordem);

    assert(!grafo_possui_ciclo(&g));
    assert(!digrafo_fortemente_conexo(&g));

    ordem = NULL;
    tamanho = 0;

    assert(grafo_bfs(&g, "B", &ordem, &tamanho));
    assert(tamanho == 2);
    assert(strcmp(g.vertices[ordem[0]].rotulo, "B") == 0);
    assert(strcmp(g.vertices[ordem[1]].rotulo, "D") == 0);

    free(ordem);

    grafo_liberar(&g);
}

static void testar_ciclo(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));
    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "A"));

    assert(grafo_possui_ciclo(&g));

    size_t *ordem = NULL;
    size_t tamanho = 0;

    assert(!grafo_ordenacao_topologica_kahn(&g, &ordem, &tamanho));
    assert(ordem == NULL);

    assert(!grafo_ordenacao_topologica_dfs(&g, &ordem, &tamanho));

    grafo_liberar(&g);
}

static void testar_conectividade(void) {
    /*
     * Caso 1:
     * Grafo nao direcionado conectado.
     *
     * A -- B -- C -- D
     */
    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    assert(grafo_conexo_nao_direcionado(&g));

    grafo_liberar(&g);

    /*
     * Caso 2:
     * Grafo nao direcionado desconectado.
     *
     * A -- B     C -- D
     */
    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "C", "D"));

    assert(!grafo_conexo_nao_direcionado(&g));

    grafo_liberar(&g);

    /*
     * Caso 3:
     * Digrafo fortemente conexo.
     *
     * A -> B -> C
     * ^         |
     * |---------|
     */
    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "A"));

    assert(digrafo_fortemente_conexo(&g));

    grafo_liberar(&g);

    /*
     * Caso 4:
     * Digrafo nao fortemente conexo.
     *
     * A -> B -> C
     */
    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));

    assert(!digrafo_fortemente_conexo(&g));

    grafo_liberar(&g);
}

static void testar_nao_direcionado(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 0));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "B", "D"));

    assert(grafo_conexo_nao_direcionado(&g));

    int *articulacoes = NULL;
    assert(grafo_vertices_articulacao(&g, &articulacoes));

    int a = grafo_indice_vertice(&g, "A");
    int b = grafo_indice_vertice(&g, "B");
    int c = grafo_indice_vertice(&g, "C");
    int d = grafo_indice_vertice(&g, "D");

    assert(b >= 0 && articulacoes[b] == 1);

    free(articulacoes);

    int *pontes = NULL;
    assert(grafo_pontes(&g, &pontes));

    assert(pontes[(size_t)a * g.quantidade_vertices + (size_t)b]);
    assert(pontes[(size_t)b * g.quantidade_vertices + (size_t)c]);
    assert(pontes[(size_t)b * g.quantidade_vertices + (size_t)d]);

    free(pontes);

    long long faces = 0;
    assert(grafo_verifica_formula_euler(&g, &faces));
    assert(faces == 1);

    int *cores = NULL;
    int qtd_cores = 0;

    assert(grafo_coloracao_gulosa(&g, &cores, &qtd_cores));
    assert(qtd_cores >= 2);

    assert(cores[a] != cores[b]);
    assert(cores[b] != cores[c]);
    assert(cores[b] != cores[d]);

    free(cores);

    grafo_liberar(&g);
}

static void testar_conectividade_forte(void) {
    Grafo g;

    assert(grafo_inicializar(&g, 1));

    assert(grafo_adicionar_aresta(&g, "A", "B"));
    assert(grafo_adicionar_aresta(&g, "B", "C"));
    assert(grafo_adicionar_aresta(&g, "C", "A"));

    assert(digrafo_fortemente_conexo(&g));

    grafo_liberar(&g);
}

int main(void) {
    testar_representacoes();
    testar_dag();
    testar_ciclo();
    testar_conectividade();
    testar_nao_direcionado();
    testar_conectividade_forte();

    printf("Todos os testes da Fase I passaram.\n");

    return 0;
}