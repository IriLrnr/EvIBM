#include "functions.h"

int main()
{
  int i, j, l, number_species;
  int* first_genome;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population progenitors, offspring;
  Graph G;
  Parameters info;

  /* This loop is used when more simulations are needed */
  for (l = 0; l < 1; l++) {
  /* Using a fixed seed gives same results at every simulation. */
    srand (1);

    info = Set_Parameters();

    progenitors = Alloc_Population (info);
    offspring = Alloc_Population (info);

    Set_Initial_Values (progenitors, info);

    /* The graph is created with the population's original size*/
    G = CreateGraph (info->individual_vector_size, info->number_individuals);

    /* The actual program is here. In each generation, we make the kth population's graph
     the individuls reproduce, creating a new population, and we count the number of species. */
  	for (number_species = 0, i = 0; i < info->number_generations; i++) {
      printf("GENERATION: %d\n", i);
      Stablish_Distances (G, progenitors, info);
  		Reproduction (G, progenitors, offspring, info);
      number_species = Count_Species (G, progenitors);
      New_Generation_k (&progenitors, &offspring);
      printf("NUMBER OF SPECIES = %d\n", number_species);
  	}

    /* We end the simulation freeing the used memory */

    DestroiGraph(G);
    Free_Population (progenitors, info);
    Free_Population (offspring, info);
    free (info);
  }

return 0;
}
