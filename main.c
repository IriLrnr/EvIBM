#include "include/model.h"

extern gsl_rng *GLOBAL_RNG;

int main(int argc, char* argv[])
{
  int i, l,  number_species;
  int sizes[1000];
  time_t t;
  Population progenitors, offspring;
  Parameters info;
  FILE *nspecies, *distances, *size, *position;

  /* @ main_rand */
  srand(time(&t));
  GLOBAL_RNG = gsl_rng_alloc(gsl_rng_taus);
  gsl_rng_set(GLOBAL_RNG, (int)time(NULL));
  /* @ end */

  info = Set_Parameters(argv);

  l = atoi(argv[3]);

  HEADER(ctime(&t), info->genome_size, info->number_individuals, info->lattice_length, info->radius); /*Code in structures.h*/

  Open_Files (&nspecies, &size, &distances, &position, info, l);

  /* @ main_alloc */
  progenitors = Alloc_Population(info);
  offspring = Alloc_Population(info);  
  Set_Initial_Position(progenitors, info);
  /* @ end */

  /* @ main_loop */
  printf("Sim \t Gen \t nsp\t pop\n");
  for(i = 0; i <= info->number_generations; i++) {
    Stablish_Distances(progenitors, info);
    number_species = Count_Species(progenitors, info, sizes);
    Reproduction  (progenitors, offspring, info);
    Write_Data(&nspecies, &size, &position, sizes, number_species, i, l, progenitors, info);
    Write_Distance_Data (&distances, progenitors, i, l, info);
    Swap_Generations (&progenitors, &offspring);
  }
  /* @ end */
  
  /* @ main_free */
  Free_Population (progenitors, info);
  Free_Population (offspring, info);
  gsl_rng_free (GLOBAL_RNG);
  free (info);

  Close_Files (&nspecies, &size, &distances, &position);
  /* @ end */

  return 0;
}