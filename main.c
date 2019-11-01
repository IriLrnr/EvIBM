#include "functions.h"

int main()
{
  int number_individuals, reproductive_distance, genome_size, number_generations, i, j, number_species;
  float lattice_lenght, lattice_width, radius;
  int* first_genome;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population individualsk, individualsk1;
  Graph G; /*  Individuals' relations graph  */

  number_individuals    = 1000;
  reproductive_distance = 7;
  genome_size           = 150;
  number_generations    = 2000;
  lattice_lenght        = 100;
  lattice_width         = 100;
  radius                = 5;

  /*Seeding rand() avoids repetition of values*/
  srand(1);

  /* the entry is the number of individuals, the genome size, the radius of reproduction
     and the size of the space. */

  /* scanf("%d %d %d %d %d %f %f", &number_individuals
     &reproductive_distance, &number_generations, &radius, &genome_size, &lattice_width,
     &lattice_lenght); */

  /* The populations k and k+1 are allocated */
  individualsk  = (Population) malloc (number_individuals * sizeof (Individual));
  individualsk1 = (Population) malloc (number_individuals * sizeof (Individual));

  /* A random first genome is created */
  first_genome = (int*) malloc (genome_size * sizeof(int));
  Generate_Genome(first_genome, genome_size);

  /* The genome of each individual is allocated and the first genome is copied to each of
   them */
  for (i = 0; i < number_individuals; i++) {
    individualsk[i] = (Individual) malloc (sizeof (individual));
    individualsk1[i] = (Individual) malloc (sizeof (individual));
    individualsk[i]->genome = (int*) malloc(genome_size * sizeof (int));
    individualsk1[i]->genome = (int*) malloc(genome_size * sizeof (int));
    for (j = 0; j < genome_size; j++) {
      individualsk[i]->genome[j] = first_genome[j];
    }
  }

  /* The first graph is complete (because all the individuals are identical) */
  G = CreateGraph (number_individuals);

  /* The individuals are in the space  */
  for (i = 0; i < number_individuals; i++) {
    individualsk[i]->x = random_number()*lattice_width;
    individualsk[i]->y = random_number()*lattice_lenght;
  }

  /* After all these first definitions, the actual program is here. In each generation,
  /* the individuls will reproduce, and create a new population, and so on */
	for (number_species = 0, i = 0; i < number_generations; i++) {
    printf("GENERATION: %d\n", i);
    Stablish_Distances (G, individualsk, genome_size, reproductive_distance);
		Reproduction (G, individualsk, individualsk1, radius, genome_size);
    New_Generation_k (&individualsk, &individualsk1);
    number_species = Count_Species (G);
    printf("NUMBER OF SPECIES = %d\n", number_species);
	}

  DestroiGraph(G);
  free (first_genome);

  for (i = 0; i < number_individuals; i++) {
    free (individualsk[i]->genome);
    free (individualsk1[i]->genome);
  }

  free (individualsk);
  free (individualsk1);

  return 0;
}
