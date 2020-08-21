#include "random.h"

/*
	Set the initial values for every progenitor's y and x coordinates
*/
void Set_Initial_Position (Population, Parameters);

/*
	 Dhecks if an individual is within the range of another individual
*/
int Verify_Distance (Population, int, int, Parameters, int);


/*
	 Checks the number of neighbors of an individual
*/
int Verify_Neighborhood (List);

/*
	This function creates a linked list which represents
	the compatible neighborhood of an indiviudal
*/
void Compatible_Neighborhood (Graph, Population, int, Parameters, int);

/*
	This function creates a linked list which represents
	the spatial neighborhood of an indiviudal, except for 
*/
void Spatial_Neighborhood (Graph, Population, int, Parameters, int);

/*
	Through this function both lists of neighbors can be created 
	at the same time
*/
void Neighborhood (Graph, Population, int, Parameters, int);


/*
	Through this function a list os compatible neighbors can grow 
	one unit in radius at a time 
*/
void Expand_Compatible_Neighborhood (Graph, List, Population, int, Parameters, int);

/*
	Through this function both lists of neighbors can grow 
	one unit in radius at a time
*/
void Expand_Neighborhood (Graph, Population, int, Parameters, int);

/*
	Through this function both lists of neighbors can shink 
	one unit in radius at a time
*/
void Shrink_Neighborhood (Graph, Population, int, Parameters, int);

/*
	Sorts a neighbor from neighbors lists combined
*/
int Sort_Neighbor (Population, int);

/*
	 Counts number of individuals in a spot
*/
int Site_Occupation (Graph, Population, int, Parameters);

/*
	This function, called by Reproduction, defines the offspring position, that is, 
	if it is going to move, how much,and in which direction. 
	It can move in it's focal parent range, with 1% chance
*/
void Offspring_Position (Population, Population, int, int, Parameters);

/*
	 Chooses a compatible neighbor for reproducing
*/
int Choose_Mate (Graph, int, Population, Parameters);

/*
	 Chooses an individual to replace when a focal 
	 dies before reproducing
*/
int Choose_Other (Graph, int, Population, Parameters, int, int[]);