#include <unistd.h>
#include <stdio.h>
#include "include/model.h"

#define HEADER "*************BEG**************\n%sB = %d, M = %d, L = %.f, S = %.f\n******************************\n"
#define COLS "Sim\tGen\tnsp\tpop"
#define OPTSTRING "h"

typedef struct {
  float side;
  float radius;
  int sim_id;
} config;

extern gsl_rng *GLOBAL_RNG;

/* @ main_rand */
void Setup_Rng(time_t *t) {
  time(t);
  srand(*t);
  GLOBAL_RNG = gsl_rng_alloc(gsl_rng_taus);
  gsl_rng_set(GLOBAL_RNG, (int)(*t));
}
/* @ end */

void help() {
  puts("Usage: main SIDE RADIUS\n"
       "Arguments:\n"
       "    SIDE The side-length of the lattice.\n"
       "  RADIUS Maximum distance between reproducing individuals.");
}

config Parse_Options (int argc, char **argv) {
  char o;
  config conf;

  while ((o = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (o) {
    case 'h':
      help();
      exit(0);
    }
  }

  if (argc - optind < 3) {
    help();
    exit(1);
  }

  conf.side   = atof(argv[optind]);
  conf.sim_id = atoi(argv[optind+1]);
  conf.radius = atof(argv[optind+2]);

  return conf;
}

int main(int argc, char* argv[]) {
  FILE *nspecies, *distances, *size;
  Parameters info;
  Population progenitors, offspring;
  int i, l,  number_species, sizes[1000];
  time_t t;
  config conf;

  Setup_Rng(&t);

  conf = Parse_Options(argc, argv);
  info = Set_Parameters(conf.side, conf.radius);
  l = conf.sim_id;

  printf(HEADER,
	 ctime(&t),
	 info->genome_size,
	 info->number_individuals,
	 info->lattice_length,
	 info->radius
	 );

  Open_Files (&nspecies, &size, &distances, info, l);

  /* @ main_alloc */
  progenitors = Alloc_Population(info);
  offspring = Alloc_Population(info);  
  Set_Initial_Position(progenitors, info);
  /* @ end */

  /* @ main_loop */
  puts(COLS);
  for(i = 0; i <= info->number_generations; i++) {
    Stablish_Distances (progenitors, info);
    number_species = Count_Species (progenitors, info, sizes);
    Reproduction (progenitors, offspring, info);
    Write_Data (&nspecies, &size, &distances, sizes, number_species, i, l, progenitors, info);
    Write_Distance_Data (&distances, progenitors, i, l, info);
    Swap_Generations (&progenitors, &offspring);
  }
  /* @ end */
  
  /* @ main_free */
  Free_Population (progenitors, info);
  Free_Population (offspring, info);
  gsl_rng_free (GLOBAL_RNG);
  free (info);
  Close_Files (&nspecies, &size, &distances);
  /* @ end */

  return 0;
}
