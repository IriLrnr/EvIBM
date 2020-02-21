#include "functions.h"

int main()
{
  int i, j, l, number_species;
  int* first_genome;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population progenitors, offspring;
  Graph G; /*  Individuals' relations graph */
  Parameters info;

  /* This loop is used when more simulations are needed */
  for (l = 0; l < 1; l++) {

    info = Set_Parameters();

    /* Using a fixed seed gives same results at every simulation. */
    srand (1);

    /* The populations k and k+1 are allocated */
    progenitors  = (Population) malloc (info->individual_vector_size * sizeof (Individual));
    offspring = (Population) malloc (info->individual_vector_size * sizeof (Individual));

    /* A random first genome is created */
    first_genome = (int*) malloc (info->genome_size * sizeof(int));
    Generate_Genome(first_genome, info->genome_size);

    /* The genome of each individual is allocated and the first genome is copied to each of
     them */
    for (i = 0; i < info->individual_vector_size; i++) {
      progenitors[i] = (Individual) malloc (sizeof (individual));
      offspring[i] = (Individual) malloc (sizeof (individual));
      progenitors[i]->genome = (int*) malloc(info->genome_size * sizeof (int));
      offspring[i]->genome = (int*) malloc(info->genome_size * sizeof (int));
      progenitors[i]->neighborhood = CreateHeadedList ();
      offspring[i]->neighborhood = CreateHeadedList (); 
      for (j = 0; j < info->genome_size; j++) {
        progenitors[i]->genome[j] = first_genome[j];
      }
    }

    /* The individuals are in the space */
    for (i = 0; i < info->number_individuals; i++) {
      progenitors[i]->x = random_number() * info->lattice_width;
      progenitors[i]->y = random_number() * info->lattice_lenght;
    }


    /* The graph is created with the population's original size*/
    G = CreateGraph (info->individual_vector_size, info->number_individuals);

    /* After all these first definitions, the actual program is here. In each generation, we make the kth population's graph
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
    free (first_genome);
    free (info);

    for (i = 0; i < info->number_individuals; i++) {
      free (progenitors[i]->genome);
      free (offspring[i]->genome);
    }

    free (progenitors);
    free (offspring);
  }

return 0;
}

/*----------------------------------------
Situação atual:

- Forma muita espécie muito rápido, dai estabiliza muito, indicando colapso da posição dos individuos para poucos pontos.

------------------------------------------*/