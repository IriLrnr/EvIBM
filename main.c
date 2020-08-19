  #include "functions.h"

int main()
{
  int i, j, k, l, number_species, type, deltat, p;
  Population progenitors, offspring;
  Graph G;
  Parameters info;
  char nome_arq_s[80] = "";
  char nome_arq_st[80] = "";
  FILE *nspecies;
  time_t t;
  double n, x, lim;

  /* Tests for altered functions with mini population
  info = Set_Mini_Parameters();
  progenitors = Alloc_Population (info);
  offspring = Alloc_Population (info);  
  Set_Initial_Values (progenitors, info);
  G = CreateGraph (info->individual_vector_size, info->number_individuals);

  AlterList (progenitors[1], 7);
  AlterList (progenitors[1], 7)
  */

  GLOBAL_RNG = gsl_rng_alloc (gsl_rng_taus);
  gsl_rng_set (GLOBAL_RNG, (int) time(NULL));

  info = Set_Parameters();

  n = lim = 1;

  n = 150*n;
  lim = 150*lim;
  x = 10;

  for (n; n <= lim; n *= x) {
    info->genome_size = n;
    info->reproductive_distance  = (int) floor(0.05*info->genome_size);
    printf("B = %d\n", info->genome_size);

    if (info->genome_size > 1500) {
      if (info->genome_size > 15000) info->number_generations = 200;
      else info->number_generations = 500;
    }
    info->population_size = info->number_individuals;

    for (l = 0; l < 1; l++) {
      time(&t);
      srand (t);
      
      //printf("*************BEG**************\n%sB = %d, g = %d, mu = %0.5f\n******************************\n", ctime(&t), info->genome_size, info->reproductive_distance, info->mutation);
      
      sprintf (nome_arq_s, "./data/performance_tests/B/%d/species/numsp_%02d.csv", info->genome_size, l);
      nspecies = fopen (nome_arq_s, "w");
      fprintf (nspecies, "gen;sp;sim\n");

      progenitors = Alloc_Population (info);
      offspring = Alloc_Population (info);  
      Set_Initial_Values (progenitors, info);
      G = CreateGraph (info->individual_vector_size, info->number_individuals);

      //printf("Sim \t Gen \t nsp \t pop\n");
      for (i = 0; i <= info->number_generations; i++) {
        Stablish_Distances (G, progenitors, info);
        if (i%10 == 0) {
          number_species = Count_Species (G, progenitors);
          fprintf (nspecies, "%d;%d;%d\n", i, number_species, l);
        }
        Reproduction  (G, progenitors, offspring, info);
       /* if (i % 10 == 0) {
          printf(" %d \t %d \t  %d \t %d\n", l, i, number_species, G->U);
        }
        */
        Swap_Generations (&progenitors, &offspring);
      }

      DestroyGraph(G);
      Free_Population (progenitors, info);
      Free_Population (offspring, info);
      fclose (nspecies);
    }
  }

  gsl_rng_free (GLOBAL_RNG);
  free (info);

  return 0;
}