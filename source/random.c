#include "../include/random.h"

/* @ rand_1ton */
int rand_1to (int n)
{
  return ((int) (random_number() * n) + 1);
}
/* @ */

/* @ random_number */
double random_number ()
{
	return (gsl_rng_uniform_pos (GLOBAL_RNG));
}
/* @ */

/* @ rand_upto */
int rand_upto (int n)
{
	return (gsl_rng_uniform_int (GLOBAL_RNG, n + 1));
} 
/* @ */
