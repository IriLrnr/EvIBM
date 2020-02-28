#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Vertix int

typedef struct {
  int V;
  int U;
  int A;
  int **adj;
} graph;

typedef graph * Graph;

int** AlocateMatrix (int m, int n, int value)
{
  int **A, i, j;
  A = (int**) malloc (m * sizeof (int*));
  for (i = 0; i < m; i++) {
    A[i] = (int*) malloc (n * sizeof (int));
    for (j = 0; j < n; j++)
      A[i][j] = value;
  }
  return A;
}

Graph CreateGraph (int V, int U)
{
  Graph G;
  G = (Graph) malloc (sizeof (graph));
  G->U = U;
  G->V = V;
  G->A = 0;
  G->adj = AlocateMatrix (V, V, 0);
  return G;
}

void ChangeGraphSize (Graph G, int add_or_remove)
{
  G->U = G->U + add_or_remove;
}

void InsertArc (Graph G, Vertix u, Vertix v, int k)
{
  if (u != v && u < G->U && v < G->U && G->adj[u][v] == 0 && G->adj[v][u] == 0) {
    G->adj[u][v] = k;
    G->adj[v][u] = k;
    (G->A)++;
  }
}

void RemoveArc (Graph G, Vertix u, Vertix v)
{
  if (u != v && u < G->U && v < G->U && G->adj[u][v] != 0 && G->adj[v][u] != 0) {
    G->adj[u][v] = 0;
    G->adj[v][u] = 0;
    (G->A)--;
  }
}

void PrintGraph (Graph G)
{
  Vertix u, v;

  for (u = 0; u < G->U; u++) {
    printf("%d: ", u);
    for (v = 0; v < G->U; v++)
      if (G->adj[u][v] > 0)
        printf("%d ", v);
    printf("\n");
  }
}

void DestroyGraph (Graph G)
{
 int i;

  for (i = 0; i < G->V; i++)
    free (G->adj[i]);
  free (G->adj);

  free(G);
}

