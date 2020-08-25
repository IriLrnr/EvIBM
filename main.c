  #include "include/model.h"

int main(int argc, char* argv[])
{
  int i, j, l, k, number_species, type, deltat, p, genome;
  Population progenitors, offspring;
  Parameters info;
  char nome_arq_s[80] = "";
  char nome_arq_st[80] = "";
  FILE *nspecies;
  FILE *performance;
  time_t t;

  GLOBAL_RNG = gsl_rng_alloc (gsl_rng_taus);
  gsl_rng_set (GLOBAL_RNG, (int) time(NULL));

  info = Set_Parameters();

  l = atoi(argv[3]);
  if (l == 1) {
    sprintf (nome_arq_st, "./data/performance_tests/B/performance_%d.txt", (int) atoi(argv[2]));
    performance = fopen(nome_arq_st, "w");
    fprintf (performance, "real;usr;sys\n");
    fclose (performance);
  }

  info->genome_size = atoi(argv[2]);
  info->reproductive_distance  = (int) floor(0.05*info->genome_size);
  printf("B = %d\n", info->genome_size);

  if (info->genome_size > 1500) {
    if (info->genome_size > 15000) info->number_generations = 200;
    else info->number_generations = 500;
  }
  info->population_size = info->number_individuals;


  time(&t);
  srand (t);
  
  printf("*************BEG**************\n%sB = %d, g = %d, mu = %0.5f\n******************************\n", ctime(&t), info->genome_size, info->reproductive_distance, info->mutation);
  
  sprintf (nome_arq_s, "./data/performance_tests/B/%d/species/numsp_%02d.csv", info->genome_size, l);
  nspecies = fopen (nome_arq_s, "w");
  fprintf (nspecies, "gen;sp;sim\n");

  progenitors = Alloc_Population (info);
  offspring = Alloc_Population (info);  
  Set_Initial_Position (progenitors, info);

  printf("Sim \t Gen \t nsp \t pop\n");
  for (i = 0; i <= info->number_generations; i++) {
    Stablish_Distances (progenitors, info);
    if (i%10 == 0) {
      number_species = 1;//Count_Species (progenitors);
      fprintf (nspecies, "%d;%d;%d\n", i, number_species, l);
    }
    Reproduction  (progenitors, offspring, info);
    if (i % 100 == 0) {
      printf(" %d \t %d \t  %d \t %d\n", l, i, number_species, info->population_size);
    }
    Swap_Generations (&progenitors, &offspring);
  }

  Free_Population (progenitors, info);
  Free_Population (offspring, info);
  fclose (nspecies);

  gsl_rng_free (GLOBAL_RNG);
  free (info);

  return 0;
}