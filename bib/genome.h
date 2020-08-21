#include "space.h"

/*
	Generates a random first genome for the simulation.
	It is not being used. First genome is all zero.
*/
int* Generate_Genome (int);

/*
	This function, called by main, compares the genomes and creates a Graph, where vertix are individuals,
	arches means they can reproduce (similar genomes). The weight of the arch is the distance
	between genomes.
*/
void Stablish_Distances (Graph, Population, Parameters);

/*
	This function, called by Create_Offspring, allocates the mutation in the genome
*/
void Mutation (Population, int, Parameters);

/*
	This function, called by Reproduction, determines the characteristics of the offspring, based on the parent's.
	The new offspring will have the position of the focal individual (i). The genome of the offspring has, for
	each loci, 50% chance of coming from either of his parents 
*/
void Create_Offspring (Population, Population, int, int, int, int, Parameters);

void DSFvisit (Graph, Vertix, int*, Population, int);

void DepthFirstSearch (Graph, int*, Population);

/*
	Calls for DephtFirstSearch to count number of species
*/
int Count_Species (Graph, Population);

/*
	Count the size of each species
*/
void Count_Sizes (Graph, Population, int, Parameters, int*);

