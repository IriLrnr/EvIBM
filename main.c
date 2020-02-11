#include "functions.h"

int main()
{
  int i, j, l, number_species;
  int* first_genome;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population individualsk, individualsk1;
  Graph G; /*  Individuals' relations graph */
  Parameters info;
  char nome_arq[15] = "";
  char line[65] = "";
  char x[20] = "";
  char y[20] = "";
  char sp[20] = "";
  FILE *output;

  /* This loop is used when more simulations are needed */
  for (l = 0; l < 1; l++) {

  /* The parameters are almost fixed. The only one that changes is the population_size. */
  info = (Parameters) malloc (sizeof (parameters));

  info->number_individuals     = 1000;
  info->population_size        = 1000;
  /* The population can grow and sink. Here we estimate the grown aoround 20% */
  info->individual_vector_size = (int)(info->number_individuals * 1.2);
  info->reproductive_distance  = 7;
  info->genome_size            = 150;
  info->number_generations     = 1000;
  info->lattice_lenght         = 100;
  info->lattice_width          = 100;
  info->radius                 = 5;

  /* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
  individuals that mark the density limit (60% of the original density) */
  info->neighbors = (int)(0.6*info->radius*info->radius*3.14159*info->number_individuals) / (info->lattice_lenght * info->lattice_width);

  /* Using a fixed seed gives same results at every simulation. */
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

  /* The graph is created with the population's original size*/
  G = CreateGraph (info->individual_vector_size, info->number_individuals);

  /* The individuals are in the space */
  for (i = 0; i < G->V; i++) {
    individualsk[i]->x = random_number()*info->lattice_width;
    individualsk[i]->y = random_number()*info->lattice_lenght;
    individualsk[i]->neighborhood = CreateHeadedList ();
    individualsk1[i]->neighborhood = CreateHeadedList (); 
  }

  /* After all these first definitions, the actual program is here. In each generation, we make the kth population's graph
   the individuls reproduce, creating a new population, and we count the number of species. */
	for (number_species = 0, i = 0; i < info->number_generations; i++) {
    printf("GENERATION: %d\n", i);
    Stablish_Distances (G, individualsk, info);
    Reproduction (G, individualsk, individualsk1, info);
    number_species = Count_Species (G, individualsk);
    /*This part is just for printing the result for making graphs in R later*/
    if (i < 10) {
      sprintf(nome_arq, "%d", i);
      strcat (nome_arq, "gen.txt");
      output = fopen (nome_arq,"w");
      for (j = 0; j < info->population_size; ++j) {
       sprintf(line, "%d;", i);
       sprintf (x, "%f;", individualsk[j]->x);
       sprintf(y, "%f;", individualsk[j]->y);
       sprintf(sp, "%d\n", individualsk[j]->species);
       strcat(line, x);
       strcat(line, y);
       strcat(line, sp);  
       fputs (line, output);
      }
      fclose (output);
    }
    New_Generation_k (&individualsk, &individualsk1);
    printf("NUMBER OF SPECIES = %d\n", number_species);
  }
  /* We end the simulation freeing the used memory */

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

/*----------------------------------------
Situação atual:

- Forma muita espécie muito rápido, dai estabiliza muito, indicando colapso da posição dos individuos para poucos pontos.

------------------------------------------*/