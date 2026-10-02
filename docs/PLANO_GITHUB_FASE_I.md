# Plano de GitHub — Fase I

O professor informou que a avaliação considera Issues, Pull Requests e evolução do projeto. Por isso, a recomendação é não fazer um único commit gigante.

## Ordem sugerida

### Issue 1 — Migrar implementação para C

Branch:

```text
feature/migracao-c
```

Commits sugeridos:

```text
refactor: migra estrutura de grafos de cpp para c
refactor: substitui containers por estruturas em c
```

### Issue 2 — Lista e matriz de adjacência

Branch:

```text
feature/representacoes-grafo
```

Commits:

```text
feat: implementa lista de adjacencia
feat: implementa matriz de adjacencia
```

### Issue 3 — BFS e DFS

Branch:

```text
feature/buscas-grafo
```

Commits:

```text
feat: implementa bfs
feat: implementa dfs
```

### Issue 4 — Conectividade

Branch:

```text
feature/conectividade
```

Commits:

```text
feat: implementa conectividade de grafo nao direcionado
feat: implementa conectividade forte de digrafo
```

### Issue 5 — Articulação e pontes

Branch:

```text
feature/articulacao-pontes
```

Commits:

```text
feat: implementa vertices de articulacao
feat: implementa pontes
```

### Issue 6 — Euler

Branch:

```text
feature/formula-euler
```

Commit:

```text
feat: implementa verificacao das condicoes de euler
```

### Issue 7 — Coloração gulosa

Branch:

```text
feature/coloracao-gulosa
```

Commit:

```text
feat: implementa coloracao gulosa
```

### Issue 8 — Testes e documentação

Branch:

```text
feature/testes-documentacao-fase1
```

Commits:

```text
test: adiciona testes da fase 1
docs: atualiza documentacao da fase 1
```

## Fluxo de cada tarefa

```text
Issue
  ↓
criar branch
  ↓
implementar
  ↓
compilar
  ↓
rodar testes
  ↓
commit
  ↓
push
  ↓
Pull Request
  ↓
revisar
  ↓
merge
  ↓
fechar Issue
```

## Comandos básicos

```bash
git status
git checkout -b feature/nome-da-tarefa
git add .
git commit -m "feat: descricao curta"
git push -u origin feature/nome-da-tarefa
```

Depois, abrir a Pull Request no GitHub e associá-la à Issue correspondente.

## Atenção

Não marcar como concluído um requisito que ainda não foi realmente demonstrado. Em particular, o dataset atual tem 10 vértices e é apenas demonstrativo; o dataset real com pelo menos 1.000 vértices deve ser adicionado quando for selecionado.
