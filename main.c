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

  for (l = 0; l < 20; l++) {
    /* Using a fixed seed gives same results at every simulation. */
    srand (time(NULL));
    GLOBAL_RNG = gsl_rng_alloc(gsl_rng_taus);

    sprintf (nome_arq_s, "./data/species/numspV0_1_%02d.csv", l);
    nspecies = fopen (nome_arq_s, "w");
    fprintf (nspecies, "gen;sp;sim\n");

    if (l == 0) {
      sprintf (nome_arq_p, "./data/position/indlocV0_1.csv");
      position = fopen (nome_arq_p, "w");
      fprintf (position, "id;x;y;sp;gen\n");
    }

    info = Set_Parameters();

    progenitors = Alloc_Population (info);
    offspring = Alloc_Population (info);

    Set_Initial_Values (progenitors, info);

    G = CreateGraph (info->individual_vector_size, info->number_individuals);

    printf("SIMULATION %d\n", l);
    for (i = 0; i <= info->number_generations; i++) {
      Stablish_Distances (G, progenitors, info);
      number_species = Count_Species (G, progenitors);
      if (i > 0) CheckSpecies(G, progenitors, info);
  		Reproduction  (G, progenitors, offspring, info);
      if (1) {
        fprintf (nspecies, "%d;%d;%d\n", i, number_species, l);
        if (l == 0) {
          for (j = 0; j < (G->U); j++) {
            fprintf(position, "%d;%f;%f;%d;%d\n", j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, i); 
          }
        }
      }
      if (i%1000 == 0) {
        printf("GENERATION: %d\n", i);
        printf("pop size: %d\n", G->U);
        printf("NUMBER OF SPECIES = %d\n", number_species);
      }
      Swap_Generations (&progenitors, &offspring);
    }

    DestroyGraph(G);
    Free_Population (progenitors, info);
    Free_Population (offspring, info);
    free (info);
    if (l == 0) fclose (position);
    fclose (nspecies);
    gsl_rng_free (GLOBAL_RNG);
  }

return 0;
}