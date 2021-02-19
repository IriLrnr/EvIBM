/* Libraries */
#include "data.h"

/*
	Set simulation parameters
*/
Parameters Set_Parameters (float,float);

/*
	Creates genome and position of offspring
*/
void Create_Offspring (Population, Population, int, int, int, int, Parameters);

/*
	The actual model The rest is auxiliary
*/
void Reproduction (Population, Population, Parameters);
