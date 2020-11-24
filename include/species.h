#include "space.h"

/*
	Compare genomes of neighbors and construct the lists of neigborhoods.
*/
void Stablish_Distances (Population, Parameters);

/*
	Uses Union-Find heuristics to find number of species
*/
int Count_Species (Population, Parameters, int[]);  


void Find_Species (Population, Parameters);