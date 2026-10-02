# Fase I — Gestão de Projetos Industriais (PERT/CPM)

Projeto de Teoria dos Grafos aplicado ao planejamento de projetos industriais.

## 1. Cenário

O projeto é modelado como um **Grafo Direcionado Acíclico (DAG)**:

- cada vértice representa uma tarefa;
- cada aresta `u -> v` representa uma dependência;
- `u` precisa terminar antes de `v` começar.

Na Fase I, o foco é a representação e a análise estrutural do grafo.

## 2. O que foi implementado nesta versão

- Lista de adjacência implementada manualmente em C;
- Matriz de adjacência implementada manualmente em C;
- BFS;
- DFS;
- conectividade de grafos não direcionados;
- conectividade forte de dígrafos;
- detecção de ciclos;
- ordenação topológica por Kahn;
- ordenação topológica por DFS;
- vértices de articulação (Tarjan, para grafo não direcionado);
- pontes (Tarjan, para grafo não direcionado);
- verificação das condições baseadas na Fórmula de Euler;
- coloração gulosa;
- leitura de dataset textual;
- testes automatizados;
- medição de tempo de execução dos algoritmos demonstrados no programa principal.

> **Importante sobre Euler:** a Fórmula de Euler e as desigualdades derivadas são condições necessárias em determinados casos, mas não constituem, sozinhas, um algoritmo completo de reconhecimento de planaridade. O relatório registra essa limitação para evitar uma conclusão incorreta.

## 3. Linguagem

A implementação dos algoritmos core está em **C11**, sem bibliotecas prontas de grafos.

## 4. Estrutura

```text
include/
  grafo.h
src/
  grafo.c
  main.c
tests/
  test_grafo.c
data/
  projeto_exemplo.txt
diagramas/
  dag_projeto.dot
  dag_projeto.svg
  dag_projeto.png
docs/
  Relatorio_Fase_I.md
  PLANO_GITHUB_FASE_I.md
results/
  program_output.txt
```

## 5. Compilar no VS Code / terminal

### GCC — Windows, Linux ou macOS

Na raiz do projeto:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c src/grafo.c -Iinclude -o programa
```

Windows:

```text
programa.exe
```

Linux/macOS/Git Bash:

```bash
./programa
```

### Compilar os testes

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 tests/test_grafo.c src/grafo.c -Iinclude -o testes
```

Executar:

```bash
./testes
```

No Windows:

```text
testes.exe
```

Saída esperada:

```text
Todos os testes da Fase I passaram.
```

## 6. Dataset

O arquivo `data/projeto_exemplo.txt` é um **dataset demonstrativo** com 10 tarefas. Ele é usado para validar a implementação da Fase I.

Formato:

```text
TAREFA A 2
TAREFA B 4
ARESTA A B
```

O requisito do trabalho que exige dataset real com pelo menos 1.000 vértices ainda precisa ser atendido com uma base real adequada ao domínio. **Não foi utilizado um dataset sintético de 1.000 vértices para fingir que esse requisito foi cumprido.**

## 7. Fase II

Ainda não fazem parte desta entrega:

- Caminho Crítico / Longest Path em DAG;
- PERT/CPM;
- aplicação da coloração à alocação de recursos;
- experimentos completos de escala `N=100`, `500`, `1000`, etc.;
- comparação experimental aprofundada de tempo e memória.

Esses itens devem ser desenvolvidos na Fase II ou na etapa experimental definida pelo professor.
