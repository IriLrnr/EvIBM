#include "graph.h"

int main() {
  Graph G;
  int i, j, subgraphs;
  pointer item;

  G = CreateGraph (15);

  InsertArch(G, 5, 2, 1);
  InsertArch(G, 4, 3, 1);
  InsertArch(G, 7, 4, 1);
  InsertArch(G, 8, 6, 1);


  InsertArch(G, 1, 2, 1);
  InsertArch(G, 1, 9, 1);
  InsertInList (G, 1, 9, 3);

  item = FindValue(3, &G->adj[1][9]->list);


  for (i = 0; i < (G->V); i++) {
    for (j = 0; j < (G->V); j++) {
      printf("%d ", G->adj[i][j]->value);
    }
    printf("\n");
  }
  PrintGraph(G);

  DepthFirstSearch(G, &subgraphs);
  printf("%d\n", subgraphs);

  printf("%d\n", item->info);

  return 0;
}

/*BIBLIOTECA MODIFICADA PRONTA PARA USAR COM LISTA LIGADA TESTE*/
