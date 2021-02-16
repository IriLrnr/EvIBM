#include "../include/model.h"

/* @ Set_Parameters */
Parameters Set_Parameters () 
{
	Parameters info;
	double rho, epslon = 0.74;

	info = (Parameters) malloc (sizeof (parameters));

	info->number_individuals     = 1000;
	info->population_size        = info->number_individuals;
	info->child_population_size  = info->number_individuals;
	/* The population can grow and sink. Here we estimate the grown aoround 20% */
	info->genome_size            = 1500;
	info->reproductive_distance  = (int) floor(0.05*info->genome_size);
	info->number_generations     = 1000;
	info->lattice_length         = 100;
	info->lattice_width          = 100;
	info->radius                 = 5;
	info->mutation               = 0.00025;
	info->dispersion             = 0.01;
	info->min_neighboors         = 3;
	info->max_increase           = 2;
	
	/* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
	individuals that mark the density limit (60% of the original density) */
	//rho = 0.83*((double) info->number_individuals)/((double) (info->lattice_length * info->lattice_width));
	//info->density = (int) ceil(3.1416*rho*info->radius*info->radius * 0.6 - epslon);

	info->density = ((double) info->number_individuals)/((double) (info->lattice_length * info->lattice_width));

	return info;
}
/* @ end */

/* @ Create_Offspring */
void Create_Offspring (Population progenitors, Population offspring,  int baby, int focal, int other, int mate, Parameters info) 
{
	Offspring_Position (progenitors, offspring, baby, focal, info);
	Offspring_Genome (progenitors, offspring, baby, other, mate, info);
	offspring[baby]->species = baby;
	offspring[baby]->species_size = 1;
}
/* @ end */

/* @ Reproduction */
void Reproduction (Population progenitors, Population offspring, Parameters info)
{
	int focal, mate, other, baby, other_neighborhood, all, compatible_neighborhood, increase, n, expand, density;
	double occupation;

	occupation = ((double) info->population_size) / ((double) info->number_individuals);
	density = (int) (info->density*25*3.1416 / (1 + exp(5*(occupation - 1.075))));
	
	baby = 0;
	for (focal = 0; focal < info->population_size; focal++) {
		mate = -1;
		progenitors[focal]->radius_increase = 0;
		compatible_neighborhood = Find_Compatible_Neighborhood (progenitors, focal, info);
		all = Find_Neighborhood (progenitors, focal, info);
		//printf("local_density = %d\n", progenitors[focal]->local_density);
		if (info->population_size < info->number_individuals && progenitors[focal]->local_density < density) {
			if (compatible_neighborhood >= info->min_neighboors) {
				mate = Choose_Mate (progenitors, focal, info);
				for (n = 0; n < 2 && mate != -1; n++) {
					Create_Offspring (progenitors, offspring, baby, focal, focal, mate, info);
					baby ++;
				}
			}
		}
		else {
			for (increase = 0; all < 2 && increase < info->max_increase; increase++) {
				progenitors[focal]->radius_increase = increase + 1;
				all = Find_Neighborhood (progenitors, focal, info);
			}
			if (all < 2) continue;
			other = Choose_Other (progenitors, focal, info);
			if (other != -1) {
				other_neighborhood = Find_Compatible_Neighborhood (progenitors, other, info);
			}
			else other_neighborhood = 0;
			if (other_neighborhood > 1) {
				mate = Choose_Mate (progenitors, other, info);
				if (mate != -1) {
					Create_Offspring (progenitors, offspring, baby, focal, other, mate, info);
					baby ++;
				}
			}
		}
	}
	info->child_population_size = baby;
}
/* @ end */
