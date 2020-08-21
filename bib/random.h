#include "structures.h"

/* 
	State-keeper of the random number generator
*/
gsl_rng *GLOBAL_RNG;

/*
	Returns a random number between 0 and 1
*/
double random_number();

/*
	Returns a random integer from 0 to n
*/
int rand_upto (int);

/*
	returns a random integer from 1 to n
*/
int rand_1to (int);