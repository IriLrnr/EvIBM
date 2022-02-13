#include "structures.h"

/*
	Here, two genomes are compared. if they are sufficiently simmilar,
	It is a boolean function
*/
int Compare_Genomes (Population, int, int, Parameters);

int Calculate_Genetic_Distance (Population, int, int, Parameters);

/*
	This function, called by Create_Offspring, allocates the mutation in the genome
*/
void Mutation (Population, int, Parameters);

/*
	This function, called by Reproduction, determines the characteristics of the offspring, based on the parent's.
	The new offspring will have the position of the focal individual (i). The genome of the offspring has, for
	each loci, 50% chance of coming from either of his parents 
*/
void Offspring_Genome (Population, Population, int, int, int, Parameters);

void PrintGenome (Population, int, char*);
