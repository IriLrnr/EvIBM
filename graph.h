#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Vertix int

typedef struct {
  int V;
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

Graph CreateGraph (int V)
{
  Graph G;
  G = (Graph) malloc (sizeof (graph));
  G->V = V;
  G->A = 0;
  G->adj = AlocateMatrix (V, V, 0);
  return G;
}

void InsertArch (Graph G, Vertix u, Vertix v, int k)
{
  if (u != v && u < G->V && v < G->V && G->adj[u][v] == 0 && G->adj[v][u] == 0) {
    G->adj[u][v] = k;
    G->adj[v][u] = k;
    (G->A)++;
  }
}

void RemoveArch (Graph G, Vertix u, Vertix v)
{
  if (u != v && u < G->V && v < G->V && G->adj[u][v] != 0 && G->adj[v][u] != 0) {
    G->adj[u][v] = 0;
    G->adj[v][u] = 0;
    (G->A)--;
  }
}

void PrintGraph (Graph G)
{
  Vertix u, v;

  for (u = 0; u < G->V; u++) {
    printf("%d: ", u);
    for (v = 0; v < G->V; v++)
      if (G->adj[u][v] > 0)
        printf("%d ", v);
    printf("\n");
  }
}

void DestroiGraph (Graph G)
{
 int i;

  for (i = 0; i< G->V; i++ )
    free (G->adj[i]);
  free (G->adj);

  free(G);
}

Graph CreateCompleteGraph (int V, int k)
{
  Vertix u, v;
  Graph G = CreateGraph(V);

  for (u = 0; u < G->V; u++)
    for (v = 0; v < G->V; v++){
      InsertArch (G, u, v, k);
    }
  return G;
}

void DSFvisit (Graph G, Vertix v, int* parent)
{
  int i;

  for (i = 0; i < (G->V); i++) {
    if (G->adj[v][i] != 0 && parent[i] == -1) {
      parent[i] = v;
      DSFvisit (G, i, parent);
    }
  }
}

void DepthFirstSearch (Graph G, int *counter_adress)
{
  int i;
  int* parent;

  parent = (int*) malloc ((G->V) * sizeof (int));
  for (i = 0; i < (G->V); i++) {
    parent[i] = -1;
  }

  (*counter_adress) = 0;

  for (i = 0; i < (G->V); i++) {
    if (parent[i] == -1) {
      parent[i] = -2;
      DSFvisit (G, i, parent);
      (*counter_adress)++;
    }
  }
  free (parent);
}
