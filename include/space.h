#include "genome.h"
/*
	Set simulation parameters
*/
Parameters Set_Parameters ();

/*
	Parameters for testing
*/
Parameters Set_Mini_Parameters ();

/*
	Set the initial values for every progenitor's y and x coordinates
*/
void Set_Initial_Position (Population, Parameters);

/*
	 Dhecks if an individual is within the range of another individual
*/
int Verify_Distance (Population, int, int, Parameters, int);

/*
	Through this function both lists of neighbors can verified 
	at the same time
*/
int Find_Neighborhood (Population, int, Parameters, int);

/*
	Through this function both lists of neighbors can be verifies 
*/
int Find_Compatible_Neighborhood (Population, int, Parameters, int);

/*
	Sorts a neighbor from neighbors lists combined
*/
int Sort_Neighbor (Population, int, Parameters, int);

void Stablish_Distances (Population, Parameters);

void Expand_Neighborhood (Population, int, Parameters, int);

/*
	This function, called by Reproduction, defines the offspring position, that is, 
	if it is going to move, how much,and in which direction. 
	It can move in it's focal parent range, with 1% chance
*/
void Offspring_Position (Population, Population, int, int, Parameters);

/*
	 Chooses a compatible neighbor for reproducing
*/
int Choose_Mate (Population, int, Parameters);

/*
	 Chooses an individual to replace when a focal 
	 dies before reproducing
*/
int Choose_Other (Population, int, Parameters, int);



