#include <time.h>
#include <math.h>
#include "linkedlist.h"
#include "random.h"

/* Structures used */
typedef struct
{
	List genome;
	int species;
	int species_size;
	int radius_increase;
	double x;
	double y;
	int* neighbors_address;
	List compatible_neighbors;
	List spatial_neighbors;
} individual;

typedef individual * Individual;

typedef Individual * Population;

typedef struct
{
	int number_individuals;
	int individual_vector_size;
	int population_size;
	int child_population_size;
	int genome_size;
	int reproductive_distance;
	int number_generations;
	int density;
	int min_neighboors;
	int max_increase;
	int max_spot_density;
	double lattice_width;
	double lattice_length;
	double radius;
	double mutation;
	double dispersion;
} parameters;

typedef parameters * Parameters;

Population Alloc_Population (Parameters);

void Free_Population (Population, Parameters);

void Swap_Generations (Population*, Population*);

int min (int, int);

int max (int, int);

int Find (Population, int);

void Union (Population, int, int);
