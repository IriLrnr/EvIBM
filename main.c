#include "functions.h"

int main()
{
  int i, j, l, number_species;
  int* first_genome;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population individualsk, individualsk1;
  Graph G; /*  Individuals' relations graph  */
  Parameters info;

  for (l = 0; l < 1; l++) {

  info = (Parameters) malloc (sizeof (parameters));

  info->number_individuals     = 1000;
  info->population_size        = 1000;
  info->individual_vector_size = (int)(info->number_individuals * 1.5);
  info->reproductive_distance  = 7;
  info->genome_size            = 150;
  info->number_generations     = 1000;
  info->lattice_lenght         = 100;
  info->lattice_width          = 100;
  info->radius                 = 5;

  /* How many neighbors make 60% of the initial average density */
  info->neighbors = (int)(0.6*info->radius*info->radius*3.14159*info->number_individuals) / (info->lattice_lenght * info->lattice_width);

    /*Seeding rand() avoids repetition of values*/
    srand (1);

    /* The populations k and k+1 are allocated */
    individualsk  = (Population) malloc (info->individual_vector_size * sizeof (Individual));
    individualsk1 = (Population) malloc (info->individual_vector_size * sizeof (Individual));

    /* A random first genome is created */
    first_genome = (int*) malloc (info->genome_size * sizeof(int));
    Generate_Genome(first_genome, info->genome_size);

    /* The genome of each individual is allocated and the first genome is copied to each of
     them */
    for (i = 0; i < info->individual_vector_size; i++) {
      individualsk[i] = (Individual) malloc (sizeof (individual));
      individualsk1[i] = (Individual) malloc (sizeof (individual));
      individualsk[i]->genome = (int*) malloc(info->genome_size * sizeof (int));
      individualsk1[i]->genome = (int*) malloc(info->genome_size * sizeof (int));
      for (j = 0; j < info->genome_size; j++) {
        individualsk[i]->genome[j] = first_genome[j];
      }
    }

    /* The first graph is complete (because all the individuals are identical) */
    G = CreateGraph (info->individual_vector_size, info->number_individuals);
    /* I need to be able to add and remove vertices from the graph  BECAUSE IT NEEDS TO BE ABLE TO GROW AND SHRINK*/


    /* The individuals are in the space */
    for (i = 0; i < G->V; i++) {
      individualsk[i]->x = random_number()*info->lattice_width;
      individualsk[i]->y = random_number()*info->lattice_lenght;
    }


    /* After all these first definitions, the actual program is here. In each generation,
    /* the individuls will reproduce, and create a new population, and so on */
  	for (number_species = 0, i = 0; i < info->number_generations; i++) {
      printf("GENERATION: %d\n", i);
      Stablish_Distances (G, individualsk, info);
  		Reproduction (G, individualsk, individualsk1, info);
      New_Generation_k (&individualsk, &individualsk1);
      number_species = Count_Species (G);
      printf("NUMBER OF SPECIES = %d\n", number_species);
  	}
    /*printf("SIMULATION %d\nNUMBER OF SPECIES = %d\n", l, number_species);*/

    DestroiGraph(G);
    free (first_genome);
    free (info);

    for (i = 0; i < info->number_individuals; i++) {
      free (individualsk[i]->genome);
      free (individualsk1[i]->genome);
    }

    free (individualsk);
    free (individualsk1);
  }

  return 0;
}
