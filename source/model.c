#include "../include/model.h"

Parameters Set_Parameters () 
{
	Parameters info;
	double rho, epslon = 0.74;

	info = (Parameters) malloc (sizeof (parameters));

	info->number_individuals     = 1000;
	info->population_size        = 1000;
	/* The population can grow and sink. Here we estimate the grown aoround 20% */
	info->individual_vector_size = (int)(info->number_individuals * 1.05);
	info->genome_size            = 150;
	info->reproductive_distance  = (int) floor(0.05*info->genome_size);
	info->number_generations     = 1000;
	info->lattice_length         = 100;
	info->lattice_width          = 100;
	info->radius                 = 5;
	info->mutation               = 0.00025;
	info->dispersion             = 0.01;
	info->min_neighboors         = 3;
	info->max_increase           = 2;
	info->max_spot_density       = 100;
	/* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
	individuals that mark the density limit (60% of the original density) */
	rho = 0.83*((double) info->number_individuals)/((double) (info->lattice_length * info->lattice_width));
	info->density = (int) ceil(3.1416*rho*info->radius*info->radius * 0.6 - epslon);
	
	return info;
}

Parameters Set_Mini_Parameters () 
{
	Parameters info;
	double rho, epslon = 0.74;

	info = (Parameters) malloc (sizeof (parameters));

	info->number_individuals     = 10;
	info->population_size        = 10;
	/* The population can grow and sink. Here we estimate the grown aoround 20% */
	info->individual_vector_size = (int)(info->number_individuals * 1.05);
	info->genome_size            = 20;
	info->reproductive_distance  = (int) floor(0.05*info->genome_size);
	info->number_generations     = 2000;
	info->lattice_length         = 5;
	info->lattice_width          = 5;
	info->radius                 = 1;
	info->mutation               = 0.00025;
	info->dispersion             = 0.01;
	info->min_neighboors         = 3;
	info->max_increase           = 2;
	info->max_spot_density       = 100;
	/* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
	individuals that mark the density limit (60% of the original density) */
	rho = 0.83*((double) info->number_individuals)/((double) (info->lattice_length * info->lattice_width));
	info->density = (int) ceil(3.1416*rho*info->radius*info->radius * 0.6 - epslon);
	
	return info;
}

void Create_Offspring (Population progenitors, Population offspring,  int baby, int focal, int other, int mate, Parameters info) 
{
	Offspring_Position (progenitors, offspring, baby, focal, info);
	Offspring_Genome (progenitors, offspring, baby, other, info);
}


void Reproduction (Population progenitors, Population offspring, Parameters info)
{
	int focal, mate, other, baby, other_neighborhood, all_neighborhood, compatible_neighborhood, increase, n, occupation, expand, density;
	int changed[G->U];

	baby = 0;
	for (focal = 0; focal < info->population_size; focal++) {
		mate = -1;
		compatible_neighborhood = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);
		all_neighborhood = compatible_neighborhood + Verify_Neighborhood (progenitors[focal]->spatial_neighbors);
		if ((G->U) < info->number_individuals && all_neighborhood < info->density) {
			occupation = Site_Occupation (G, progenitors, focal, info);
			if (compatible_neighborhood >= info->min_neighboors && occupation < info->max_spot_density/3) {
				mate = Choose_Mate (G, focal, progenitors, info);
				for (n = 0; n < 2 && mate != -1; n++) {
					Create_Offspring (progenitors, offspring, baby, focal, focal, mate, info);
					baby ++;
				}
			}
		}
		else {
			for (increase = 0; all_neighborhood < 2 && increase < info->max_increase; increase++) {
				Expand_Neighborhood (G, progenitors, focal, info, increase + 1);
				compatible_neighborhood = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);
				all_neighborhood = compatible_neighborhood + Verify_Neighborhood (progenitors[focal]->spatial_neighbors);
				changed[focal] = increase + 1;
			}
			if (all_neighborhood > 1) {
				other = Choose_Other (G, focal, progenitors, info, increase, changed);
				if (other != -1) other_neighborhood = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
				else other_neighborhood = 0;
				if (other_neighborhood > 1) {
					mate = Choose_Mate (G, other, progenitors, info);
					if (mate != -1) {
						Create_Offspring (progenitors, offspring, baby, focal, other, mate, info);
						baby ++;
					}
				}
				if (other != focal && other != -1 && changed[other] > 0) {
					Shrink_Neighborhood (G, progenitors, other, info, changed[other]);
				}
			}
			if (changed[focal] > 0) {
				Shrink_Neighborhood (G, progenitors, focal, info, changed[focal]);
			}
		}
	}
	info->child_population_size = baby;
}

