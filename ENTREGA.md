# Entrega — Fase I

## Objetivo desta versão

Esta versão reorganiza a implementação anterior e corrige a principal divergência em relação ao enunciado: os algoritmos core foram migrados de C++ para **C11**.

## Requisitos da aula atendidos

- [x] Representação por lista de adjacência
- [x] Representação por matriz de adjacência
- [x] BFS
- [x] DFS
- [x] Conectividade de grafo não direcionado
- [x] Conectividade forte de dígrafo
- [x] Vértices de articulação
- [x] Pontes
- [x] Verificação das condições baseadas na Fórmula de Euler
- [x] Coloração gulosa
- [x] Testes automatizados
- [x] Projeto principal modelado como DAG
- [x] Ordenação topológica por Kahn
- [x] Ordenação topológica por DFS

## Requisitos que continuam pendentes

- [ ] Dataset real com pelo menos 1.000 vértices
- [ ] Experimentos de estresse com vários tamanhos de entrada
- [ ] Comparação experimental completa de memória entre lista e matriz
- [ ] Artigo científico final de 4 a 6 páginas no padrão SBC

## Por que o dataset de exemplo não é apresentado como dataset real?

O arquivo incluído contém apenas 10 tarefas e foi mantido como cenário controlado para validar os algoritmos. Isso é útil para testes funcionais, mas não satisfaz o requisito de base real com pelo menos 1.000 vértices.

## Fase II

As Issues antigas relacionadas a Caminho Crítico, PERT/CPM e aplicação da coloração podem ser mantidas no GitHub, mas devem ser tratadas como trabalho posterior.
