#include "../include/random.h"

 int rand_1to (int n)
{
  return ((int) (random_number() * n) + 1);
}

double random_number ()
{
	return (gsl_rng_uniform_pos (GLOBAL_RNG));
}

int rand_upto (int n)
{
	return (gsl_rng_uniform_int (GLOBAL_RNG, n + 1));
} 
