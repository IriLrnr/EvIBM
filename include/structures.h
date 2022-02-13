#include <time.h>
#include <math.h>
#include "linkedlist.h"
#include "random.h"
#include <string.h>

#define HEADER(time, B, M, L, S) printf("*************BEG**************\n%sB = %d, M = %d, L = %.f, S = %.f\n******************************\n", time, B, M, L, S)

/* @ individual */
typedef struct
{
	List genome;
	int species;
	int species_size;
	int radius_increase;
	double x;
	double y;
	int local_density;
	int* neighbors_address;
	List compatible_neighbors;
	List spatial_neighbors;
} individual;

typedef individual * Individual;
/* @ end */

/* @ population */
typedef Individual * Population;
/* @ end */

/* @ parameters */
typedef struct
{
	int number_individuals;
	int population_size;
	int child_population_size;
	int genome_size;
	int reproductive_distance;
	int number_generations;
	int min_neighboors;
	int max_increase;
	double density;
	double lattice_width;
	double lattice_length;
	double radius;
	double mutation;
	double dispersion;
} parameters;

typedef parameters * Parameters;
/* @ end */

Population Alloc_Population (Parameters);

void Free_Population (Population, Parameters);

void Swap_Generations (Population*, Population*);

int min (int, int);

int max (int, int);

int Find (Population, int);

void Union (Population, int, int);
