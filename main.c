  #include "include/model.h"

int main (int argc, char* argv[])
{
  int i, j, l, k, number_species, type, deltat, p, genome;
  int sizes[1000];
  char nome_arq_s[80] = "", nome_arq_st[80] = "", nome_arq_ss[80] = "";
  time_t t;
  Population progenitors, offspring;
  Parameters info;
  FILE *nspecies, *performance, *size;

  srand (time(&t));
  GLOBAL_RNG = gsl_rng_alloc (gsl_rng_taus);
  gsl_rng_set (GLOBAL_RNG, (int) time(NULL));

  info = Set_Parameters();

  l = atoi(argv[3]);
  if (l == 1) {
    sprintf (nome_arq_st, "./data/sizes_tests/%.f/performance_%d.txt", info->radius, (int) atoi(argv[2]));
    performance = fopen(nome_arq_st, "w");
    fprintf (performance, "real;usr;sys\n");
    fclose (performance);
  }

  info->density                = 0.1;
  info->lattice_length         = atof(argv[2]);
  info->lattice_width          = info->lattice_length;
  info->number_individuals     = (int) info->lattice_length*info->lattice_width*info->density;
  info->population_size        = info->number_individuals;
  info->child_population_size  = info->number_individuals;
  info->individual_vector_size = (int)(info->number_individuals * 1.15);
  info->radius                 = atof(argv[4]);

  printf("*************BEG**************\n%sB = %d, N = %d, L = %.f, R = %.f\n******************************\n", ctime(&t), info->genome_size, info->number_individuals, info->lattice_length, info->radius);
  
  sprintf (nome_arq_s, "./data/sizes_tests/%.f/%.f/species/numsp_%02d.csv", info->radius, info->lattice_length, l);
  nspecies = fopen (nome_arq_s, "w");
  fprintf (nspecies, "gen;sp;pop;sim\n");

  sprintf (nome_arq_ss, "./data/sizes_tests/%.f/%.f/sizes/sizes_%02d.csv", info->radius, info->lattice_length, l);
  size = fopen (nome_arq_ss, "w");
  fprintf (size, "sim;gen;sp;size;pop\n");

  progenitors = Alloc_Population (info);
  offspring = Alloc_Population (info);  
  Set_Initial_Position (progenitors, info);

  printf("Sim \t Gen \t nsp\t pop\n");
  for (i = 0; i <= info->number_generations; i++) {
    Stablish_Distances (progenitors, info);
    if (i%1 == 0) {
      number_species = Count_Species (progenitors, info, sizes);
      fprintf (nspecies, "%d;%d;%d;%d\n", i, number_species, info->population_size, l);
    }
    Reproduction  (progenitors, offspring, info);
    if (i % 25 == 0) {
      //if (info->genome < 15000) FindSpecies (progenitors, info);
      printf(" %d \t %d \t  %d \t %d\n", l, i, number_species, info->population_size);
    }
    if (i % 20 == 0) {
      for (j = 0; j < number_species; ++j) {
        fprintf (size, "%d;%d;%d;%d;%d\n", l, i, j, sizes[j], info->population_size);
      }
    }
    Swap_Generations (&progenitors, &offspring);
  }
  Free_Population (progenitors, info);
  Free_Population (offspring, info);
  fclose (nspecies);
  fclose (size);

  gsl_rng_free (GLOBAL_RNG);
  free (info);

  return 0;
}