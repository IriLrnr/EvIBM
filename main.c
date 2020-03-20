#include "functions.h"

int main()
{
  int i, j, l, number_species;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population progenitors, offspring;
  Graph G;
  Parameters info;
  char nome_arq_p[80] = "";
  char nome_arq_s[80] = "";
  char nome_arq_f[80] = "";
  char linep[65] = "";
  char lines[65] = "";
  char linef[65] = "";
  FILE *position;
  FILE *nspecies;
  FILE *fluctuation;
  unsigned int sample;

  GLOBAL_RNG = gsl_rng_alloc(gsl_rng_taus);

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
    sprintf (nome_arq_p, "../ProjetoFinalJB/data/position/indlocV2_2_r.csv");
    sprintf (nome_arq_s, "../ProjetoFinalJB/data/species/numspV2_2_r.csv");
    sprintf (nome_arq_f, "../ProjetoFinalJB/data/fluctuation/floatpopV2_2_r.csv");
    position = fopen (nome_arq_p, "w");
    nspecies = fopen (nome_arq_s, "w");
    fluctuation = fopen (nome_arq_f, "w");
    sprintf (linep, "id;x;y;sp;gen\n");
    sprintf (lines, "gen;sp\n");
    sprintf (linef, "gen;size\n");
    fputs (linep, position);
    fputs (lines, nspecies);
    fputs (linef, fluctuation);

  	for (number_species = 0, i = 0; i < info->number_generations; i++) {
      printf("GENERATION: %d\n", i);
      Stablish_Distances (G, progenitors, info);
  		Reproduction (G, progenitors, offspring, info);
      number_species = Count_Species (G, progenitors);
      /*This part is just for printing the result for making graphs in R later*/
      sprintf (lines, "%d;%d\n", i, number_species);
      sprintf (linef, "%d;%d\n", i, info->population_size);
      fputs (lines, nspecies);
      fputs (linef, fluctuation);
      if (i < info->number_generations) {
        for (j = 0; j < info->population_size; ++j) {
         sprintf(linep, "%d;%f;%f;%d;%d\n", j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, i); 
         fputs (linep, position);
        }
      }
      Swap_Generations (&progenitors, &offspring);
      printf("NUMBER OF SPECIES = %d\n", number_species);
  	}
    fclose (position);
    fclose (nspecies);
    fclose (fluctuation);

    /* We end the simulation freeing the used memory */
    DestroyGraph(G);
    Free_Population (progenitors, info);
    Free_Population (offspring, info);
    free (info);
    gsl_rng_free (GLOBAL_RNG);
  }

return 0;
}