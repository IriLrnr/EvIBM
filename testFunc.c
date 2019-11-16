#include "functions.h"

int main()
{
  /* Values here are just for tests */
  int number_individuals, reproductive_distance, genome_size, number_generations, number_species, i, j;
  int* first_genome;

  Population individualsk, individualsk1;
  Graph G; /*  Individuals' relations graph  */

  number_individuals    = 20;
  reproductive_distance = 5;
  genome_size           = 50;
  number_generations    = 10;

  individualsk  = (Population) malloc (number_individuals * sizeof (Individual));
  individualsk1 = (Population) malloc (number_individuals * sizeof (Individual));

  /* A random first genome is created */
  first_genome = (int*) malloc (genome_size * sizeof(int));
  Generate_Genome(first_genome, genome_size);

  /*Both pointers allocated in constant time*/
  for (i = 0; i < number_individuals; i++) {
    individualsk[i] = (Individual) malloc (sizeof (individual));
    individualsk1[i] = (Individual) malloc (sizeof (individual));
    individualsk[i]->genome = NULL;
    individualsk1[i]->genome = NULL;
  }

  G = CreateGraph (number_individuals, reproductive_distance);

  InsertInList (G, 1, 2, 100);
  PrintList (G->adj[1][2]->list);
  PrintList (G->adj[2][1]->list);
  InsertInList (G, 1, 2, 4);
  PrintList (G->adj[1][2]->list);
  PrintList (G->adj[2][1]->list);
  printf("1 arch size: %d\n", G->adj[2][1]->value);
  printf("2 arch size: %d\n", G->adj[1][2]->value);
  InsertInList (G, 1, 2, 200);
  PrintList (G->adj[1][2]->list);
  PrintList (G->adj[2][1]->list);
  printf("1 arch size: %d\n", G->adj[2][1]->value);
  printf("2 arch size: %d\n", G->adj[1][2]->value);
  /*for (number_species = 0, i = 0; i < number_generations; i++) {
    printf("GENERATION: %d\n", i);
    Reproduction (G, individualsk, individualsk1, 1, genome_size);
    New_Generation_k (&individualsk, &individualsk1);
    Stablish_Distances (G, individualsk, genome_size, reproductive_distance);
    number_species = Count_Species (G);
    printf("NUMBER OF SPECIES = %d\n", number_species);
  }
  PrintGraph(G); */

  DestroyGraph(G);
  free (first_genome);

  /*novamente faltando dar free em uma geração, não sei por que*/
  for (i = 0; i < number_individuals; i++) {
    DestroyList (&individualsk[i]->genome);
    free (individualsk[i]);
    DestroyList (&individualsk1[i]->genome);
    free (individualsk1[i]);
  }
  free (individualsk);
  free (individualsk1);

  return 0;
}
