#include "functions.h"

int main()
{
  int i, j, l, number_species;
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population progenitors, offspring;
  Graph G, H;
  Parameters info;
  char nome_arq_p[80] = "";
  char nome_arq_s[80] = "";
  char linep[65] = "";
  char lines[65] = "";
  FILE *position;
  FILE *nspecies;
  unsigned int sample;

  /* This loop is used when more simulations are needed */

  sprintf (nome_arq_s, "./data/species/numspV0_1.csv");
  nspecies = fopen (nome_arq_s, "w");
  sprintf (lines, "gen;sp;sim\n");
  fputs (lines, nspecies);

  for (l = 0; l < 20; l++) {
    /* Using a fixed seed gives same results at every simulation. */
    srand (time(NULL));
    GLOBAL_RNG = gsl_rng_alloc(gsl_rng_taus);

    if (l == 0) {
      sprintf (nome_arq_p, "./data/position/indlocV0_1.csv");
      position = fopen (nome_arq_p, "w");
      sprintf (linep, "id;x;y;sp;gen\n");
      fputs (linep, position);
    }

    info = Set_Parameters();

    progenitors = Alloc_Population (info);
    offspring = Alloc_Population (info);

    Set_Initial_Values (progenitors, info);

    /* The graph is created with the population's original size*/
    G = CreateGraph (info->individual_vector_size, info->number_individuals);

    /* The actual program is here. In each generation, we make the kth population's graph
     the individuls reproduce, creating a new population, and we count the number of species. */
    for (number_species = 0, i = 0; i <= info->number_generations; i++) {
      Stablish_Distances (G, progenitors, info);
      number_species = Count_Species (G, progenitors);
      if (i > 0) CheckSpecies(G, progenitors, info);
  		Reproduction  (G, progenitors, offspring, info);
      /*This part is just for printing the result for making graphs in R later*/
      if (l == 0 && (i%25 == 0)) {
        sprintf (lines, "%d;%d;%d\n", i, number_species, l);
        fputs (lines, nspecies);
        for (j = 0; j < (G->U); ++j) {
          sprintf(linep, "%d;%f;%f;%d;%d\n", j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, i); 
          fputs (linep, position);
        }
      }
      if (i%10 == 0) {
        printf("GENERATION: %d\n", i);
        printf("pop size: %d\n", G->U);
        printf("NUMBER OF SPECIES = %d\n", number_species);
      }
      Swap_Generations (&progenitors, &offspring);
    }

    /* We end the simulation freeing the used memory */
    DestroyGraph(G);
    Free_Population (progenitors, info);
    Free_Population (offspring, info);
    free (info);
    fclose (position);
    gsl_rng_free (GLOBAL_RNG);
  }

fclose (nspecies);

return 0;
}