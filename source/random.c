#include "../include/random.h"

gsl_rng *GLOBAL_RNG;

/* @ rand_1ton */
int rand_1to (int n)
{
  return ((int) (random_number() * n) + 1);
}
/* @ end */

/* @ random_number */
double random_number ()
{
	return (gsl_rng_uniform_pos (GLOBAL_RNG));
}
/* @ end */

/* @ rand_upto */
int rand_upto (int n)
{
	return (gsl_rng_uniform_int (GLOBAL_RNG, n + 1));
} 
/* @ end */
