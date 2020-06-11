  #include "functions.h"

int main()
{
  int i, j, l, number_species;
  int sizes[40];
  /* A vector for keeping all the individuals of the kth generation, and other for the
  /* (k+1)th generation */
  Population progenitors, offspring;
  Graph G, H;
  Parameters info;
  char nome_arq_s[80] = "";
  FILE *position;
  FILE *nspecies;
  FILE *size;
  unsigned int sample;
  time_t t;

  /* This loop is used when more simulations are needed */
  for (l = 1; l < 20; l++) {
    /* Using a fixed seed gives same results at every simulation. */
    time(&t);
    srand (t);
    //srand(1);
    GLOBAL_RNG = gsl_rng_alloc (gsl_rng_taus);

    printf("********************\n%s\n*********************\n", ctime(&t));

    sprintf (nome_arq_s, "./data/species/v1/numsp_vF_%02d.csv", l);
    nspecies = fopen (nome_arq_s, "w");
    fprintf (nspecies, "gen;sp;sim\n");

    if (l == 0) {
      position = fopen ("./data/position/indloc_vF.csv", "w");
      size = fopen ("./data/species/sizes_vF.csv", "w");
      fprintf (position, "id;x;y;sp;gen\n");
      fprintf (size, "sim;gen;sp;size;pop;\n");
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
      Reproduction  (G, progenitors, offspring, info);
      if (1) {
        fprintf (nspecies, "%d;%d;%d\n", i, number_species, l);
        if (l == 0) {
          for (j = 0; j < (G->U); j++) {
            fprintf(position, "%d;%f;%f;%d;%d\n", j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, i); 
          }
          Count_Sizes (G, progenitors, number_species, info, sizes);
          for (j = 0; j < number_species; ++j) {
            fprintf (size, "%d;%d;%d;%d;%d\n", l, i, j, sizes[j], G->U);
          }
        }
      }
      if (i % 10 == 0) {
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
    if (l == 0) {
      fclose (position);
      fclose (size);
    }
    fclose (nspecies);
    gsl_rng_free (GLOBAL_RNG);
  }

  return 0;
}