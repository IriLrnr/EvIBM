#include "../include/species.h"

/* @ Find_Species */
void Find_Species (Population individuals, Parameters info) 
{
	int i, j, count = 0;
	for (i = 0; i < info->population_size; i++) {
		for (j = i+1; j < info->population_size; j++) {
			if (!Verify_Distance (individuals, i, j, info, info->max_increase)) {
				if (Find (individuals, i) != Find (individuals, j)) {
					if (Compare_Genomes (individuals, i, j, info)) {
						count++;
						Union (individuals, i, j);
					}
				}
			}
		}		
	}
	//printf("%d genomes compared\n", count);
}
/* @ */

/* @ Stablish_Distances */
void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, i_compatible, increase;

	info->population_size = info->child_population_size;

	Restart_Neighborhood (progenitors, info);

	for (increase = info->max_increase; increase >= 0 ; increase--) {
		if (increase < info->max_increase) {
			progenitors[i]->neighbors_address[2*increase + 2] += progenitors[i]->neighbors_address[2*increase];
			progenitors[i]->neighbors_address[2*increase + 3] += progenitors[i]->neighbors_address[2*increase + 1];
		}
		for (i = 0; i < info->population_size; i++) {
			for (j = i + 1; j < info->population_size; j++) {
				if (increase == 0 && Verify_Distance (progenitors, i, j, info, 5 - info->radius)) {
					progenitors[i]->local_density ++;
					progenitors[j]->local_density ++;
				}
				if (increase > 0 && Verify_Distance (progenitors, i, j, info, increase - 1)) continue;
				if (Verify_Distance (progenitors, i, j, info, increase)) {
					if (Compare_Genomes (progenitors, i, j, info)) {
						if (increase <= info->max_increase) {
							AddCell (&progenitors[i]->compatible_neighbors, j);
							AddCell (&progenitors[j]->compatible_neighbors, i);
							progenitors[i]->neighbors_address[2*increase + 1]++;
							progenitors[j]->neighbors_address[2*increase + 1]++;
						}
						Union (progenitors, i, j);
					}
					else {
						if (increase <= info->max_increase) {
							AddCell (&progenitors[i]->spatial_neighbors, j);
							AddCell (&progenitors[j]->spatial_neighbors, i);
							progenitors[i]->neighbors_address[2*increase]++;
							progenitors[j]->neighbors_address[2*increase]++;	
						}
					}
				}
			}
		}
	}
}
/* @ */

/* @ Count_Species */
int Count_Species (Population individuals, Parameters info, int sizes[])
{
	int count, i;

	//FindSpecies (individuals, info);

	for (count = 0, i = 0; i < info->population_size; i++) {
		if (individuals[i]->species == i && individuals[i]->species_size > 1) {
			sizes[count] = individuals[i]->species_size;
			count ++;
		}
	}


	return count;
}
/* @ */