#include "../include/species.h"

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
				if (increase > 0 && Verify_Distance (progenitors, i, j, info, increase - 1)) continue;
				if (Verify_Distance (progenitors, i, j, info, increase)) {
					if (Compare_Genomes (progenitors, i, j, info)) {
						AddCell (&progenitors[i]->compatible_neighbors, j);
						AddCell (&progenitors[j]->compatible_neighbors, i);
						progenitors[i]->neighbors_address[2*increase + 1]++;
						progenitors[j]->neighbors_address[2*increase + 1]++;
						Union (progenitors, i, j);
					}
					else {
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

int Count_Species (Population individuals, Parameters info)
{
	int count, i;

	for (count = 0, i = 0; i < info->population_size; i++) {
		if (individuals[i]->species == i && individuals[i]->species_size > 1) count ++;
	}


	return count;
}