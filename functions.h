/* Libraries */
#include <time.h>
#include <math.h>
#include <gsl_randist.h>
#include <gsl_rng.h>
#include "graph.h"
#include "linkedlist.h"

/* State-keeper of the random number generator*/
gsl_rng *GLOBAL_RNG;

/* Structures used */
typedef struct
{
	int* genome;
	int species;
	double x;
	double y;
	List neighborhood;
} individual;

typedef individual * Individual;

typedef Individual * Population;

typedef struct
{
	int number_individuals;
	int individual_vector_size;
	int population_size;
	int genome_size;
	int reproductive_distance;
	int number_generations;
	int density;
	int min_neighboors;
	int max_increase;
	int max_spot_occupation;
	double lattice_width;
	double lattice_length;
	double radius;
	double mutation;
	double dispersion;
} parameters;

typedef parameters * Parameters;

/* functions from funtions.h */
double random_number();
int rand_upto (int);
double random_numberP ();
int rand_uptoP (int);
unsigned int poisson (double); 
int* Generate_Genome (int);
int Verify_Distance (Population, int, int, Parameters, int);
int Verify_Neighborhood (List);
void neighborhood (Graph, Population, int, Parameters, int);
void expand_neighborhood (Graph, List, Population, int, Parameters, int);
Parameters Set_Parameters ();
Population Alloc_Population (Parameters);
void Set_Initial_Values (Population, Parameters);
void Stablish_Distances (Graph, Population, Parameters);
void Offspring_Position (Population, Population, int, int, Parameters);
void mutation (Population, int, int);
void Create_Offspring (Population, Population, int, int, int, int, Parameters);
int Choose_Mate (Graph, int, Population, Parameters);
void Reproduction (Graph, Population, Population, Parameters);
void Swap_Generations (Population*, Population*);
void DSFvisit (Graph, Vertix, int*, Population, int);
void DepthFirstSearch (Graph, int*, Population);
int Count_Species (Graph, Population);
void Free_Population (Population, Parameters);
int CheckSpecies (Graph, Population, Parameters);
int Count_Singletons (Graph, Population, int, Parameters);

