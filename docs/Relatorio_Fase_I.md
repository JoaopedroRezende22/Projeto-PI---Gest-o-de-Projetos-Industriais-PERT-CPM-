# Relatório — Fase I: Gestão de Projetos Industriais (PERT/CPM)

## 1. Introdução

O estudo de caso escolhido é **Gestão de Projetos Industriais (PERT/CPM)**. O problema é modelado como um Grafo Direcionado Acíclico (DAG), no qual os vértices representam tarefas e as arestas representam dependências entre tarefas.

Se existe uma aresta `u -> v`, a tarefa `u` deve ser concluída antes do início de `v`.

A Fase I concentra-se na representação e nas propriedades estruturais do grafo.

## 2. Modelagem

Foi utilizado um cenário demonstrativo com dez tarefas, identificadas de A a J.

Dependências:

```text
A -> B
A -> C
B -> D
C -> D
C -> E
D -> F
E -> F
D -> G
F -> H
G -> H
H -> I
I -> J
```

O grafo é acíclico. Portanto, é possível obter uma ordenação topológica que respeite todas as dependências.

As durações foram armazenadas em dias para preparar a Fase II:

```text
A=2, B=4, C=3, D=5, E=4,
F=3, G=2, H=2, I=4, J=2
```

## 3. Representação por lista de adjacência

A lista de adjacência foi implementada manualmente com estruturas encadeadas em C. Cada vértice possui uma lista dos seus sucessores.

Essa representação é adequada quando o número de arestas é relativamente pequeno em comparação ao número máximo possível de arestas, pois armazena principalmente as relações que realmente existem.

## 4. Representação por matriz de adjacência

A matriz é uma estrutura `V x V`. A posição `(u,v)` vale 1 quando existe a aresta `u -> v` e 0 caso contrário.

A matriz facilita consultas diretas de existência de aresta, porém utiliza memória proporcional a `V²`.

## 5. BFS e DFS

A **BFS** foi implementada com fila. Ela parte de um vértice inicial e visita os vértices por níveis.

A **DFS** foi implementada recursivamente. Ela explora um ramo antes de retornar e continuar os demais.

No programa principal, ambas são executadas a partir da tarefa A.

## 6. Conectividade

Para grafos não direcionados, a conectividade é verificada por BFS: se todos os vértices forem alcançados a partir de um vértice inicial, o grafo é conexo.

Para dígrafos, foi implementada a verificação de **conectividade forte**. O procedimento executa uma busca no grafo original e outra considerando as arestas invertidas. Essa condição garante que todos os vértices sejam alcançáveis nos dois sentidos a partir de um vértice de referência.

O DAG do estudo de caso não é fortemente conexo, o que é esperado para um cronograma com dependências de precedência.

## 7. Ordenação topológica

Foram implementadas duas estratégias:

### 7.1 Kahn

Calcula o grau de entrada dos vértices. Os vértices com grau de entrada zero são processados primeiro. A remoção de uma dependência pode liberar a próxima tarefa.

### 7.2 DFS

Utiliza três estados: não visitado, em processamento e finalizado. Uma aresta para um vértice em processamento indica ciclo.

As duas estratégias produzem uma sequência válida quando o grafo é acíclico. A sequência não precisa ser única, pois tarefas independentes podem aparecer em ordens diferentes.

## 8. Vértices de articulação e pontes

Essas propriedades foram implementadas para grafos não direcionados usando a técnica de Tarjan.

- Um **vértice de articulação** é um vértice cuja remoção pode aumentar o número de componentes conexos.
- Uma **ponte** é uma aresta cuja remoção pode aumentar o número de componentes conexos.

Como o caso de negócio é um DAG direcionado, a análise é feita sobre o **grafo subjacente não direcionado** das dependências quando essas propriedades são solicitadas.

## 9. Fórmula de Euler

Para um grafo planar conexo, a Fórmula de Euler é:

```text
V - E + F = 2
```

portanto:

```text
F = E - V + 2
```

A implementação verifica essa relação e, para grafos simples com `V >= 3`, também considera a condição necessária `E <= 3V - 6`.

É importante destacar que essas verificações **não constituem, isoladamente, um algoritmo completo de planaridade**. O programa, portanto, apresenta o resultado como verificação de condições baseadas em Euler, e não como prova definitiva de que um grafo é planar.

## 10. Coloração gulosa

A coloração gulosa percorre os vértices em uma ordem fixa e atribui a menor cor que não esteja sendo usada por um vizinho já colorido.

No contexto do projeto, a ideia pode posteriormente ser utilizada na Fase II para representar equipes ou recursos. Nesta Fase I, o objetivo é demonstrar a implementação do algoritmo de coloração.

## 11. Testes

Foram criados testes automatizados para:

1. BFS;
2. DFS;
3. ordenação topológica por Kahn;
4. ordenação topológica por DFS;
5. detecção de ciclos;
6. conectividade forte de um ciclo direcionado;
7. conectividade de grafo não direcionado;
8. vértice de articulação;
9. pontes;
10. condição baseada na Fórmula de Euler;
11. coloração gulosa.

A execução local produz:

```text
Todos os testes da Fase I passaram.
```

## 12. Resultados demonstrativos

Para o cenário de dez tarefas, o programa apresenta as duas representações, executa BFS e DFS, verifica a existência de ciclos, calcula ordenações topológicas, analisa o grafo subjacente não direcionado e executa a coloração gulosa.

Também são registrados tempos de execução em milissegundos para os algoritmos demonstrados. Esses tempos servem como saída funcional inicial; a análise experimental de crescimento assintótico deve utilizar datasets maiores e vários tamanhos de entrada.

## 13. Limitações e próximos passos

O dataset incluído é apenas um cenário demonstrativo com 10 vértices. Ele não é apresentado como atendimento ao requisito de dataset real com pelo menos 1.000 vértices.

Como próximos passos estão a seleção e integração de uma base real adequada ao domínio, os testes de estresse com diferentes valores de `V`, a comparação de memória entre matriz e lista e o desenvolvimento da Fase II: Caminho Crítico, PERT/CPM e aplicação da coloração à alocação de recursos.
