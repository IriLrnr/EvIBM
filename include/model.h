/* Libraries */
#include "species.h"

/*
	Set simulation parameters
*/
Parameters Set_Parameters ();

/*
	Parameters for testing
*/
Parameters Set_Mini_Parameters ();



void Create_Offspring (Population, Population, int, int, int, int, Parameters);

/*
	The actual model The rest is auxiliary
*/
void Reproduction (Population, Population, Parameters);
