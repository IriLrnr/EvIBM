#include "../include/species.h"

void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, k, i_compatible, increase;

	Restart_Neighborhood (progenitors, info);

	for (i = 0; i < info->population_size; i++) {
		for (j = info->population_size; j > i; j--) {
			if (Verify_Distance (progenitors, i, j, info, 0)) {
				if (Compare_Genomes (progenitors, i, j, info)) {
					AddCellInOrder (&progenitors[i]->compatible_neighbors, j);
					AddCellInOrder (&progenitors[j]->compatible_neighbors, i);
					progenitors[i]->neighbors_address[1]++;
					progenitors[j]->neighbors_address[1]++;
					if (progenitors[j]->species < progenitors[i]->species)
						progenitors[i]->species = progenitors[j]->species;
					else
						progenitors[j]->species = progenitors[i]->species;
				}
				else {
					AddCellInOrder (&progenitors[i]->spatial_neighbors, j);
					AddCellInOrder (&progenitors[j]->spatial_neighbors, i);
					progenitors[i]->neighbors_address[0]++;
					progenitors[j]->neighbors_address[0]++;
				}
			}
		}
		i_compatible = progenitors[i]->neighbors_address[1];
		for (increase = 1; increase <= info->max_increase && i_compatible < info->min_neighboors; increase++) {
			i_compatible = Find_Compatible_Neighborhood (progenitors, i, info, increase);
		}
	}
}

int Find (Population individuals, int i) 
{
	if (individuals[i]->species == i) {
		return i;
	}
	individuals[i]->species = Find(individuals, individuals[i]->species);
	return (individuals[i]->species);
}

void Union (Population individuals, int i, int j, int sizes[]) {
	int spp_i, spp_j, k;

	spp_i = Find(individuals, i);
	spp_j = Find(individuals, j);

	if (spp_j != spp_i) {
		if (sizes[spp_i] < sizes[spp_j]) {
			k = i;
			i = j;
			j = k;
		}
	}
	individuals[j]->species = i;
	sizes[i] += sizes[j];
}

int Kruskal (Population individuals, Parameters info) {
	int i, j, spp_i, spp_j, count;
	int* sizes;

	sizes = malloc (info->population_size*(sizeof (int)));
	for (i = 0; i < info->population_size; ++i) {
		sizes[i] = 1;
	}

	for (i = 0; i < info->population_size; ++i) {
		for (j = i+1; j < info->population_size; j++) {
			if (Find(individuals, i) == Find(individuals, i)) {
				Union (individuals, i, j, sizes);
			}
		}
	}

	for (count = 0, i = 0; i < info->population_size; i++) {
		if (individuals[i]->species == i && sizes[i] > 1) count ++;
	}

	free (sizes);

	return count;
}

int Count_Species (Population individuals, Parameters info)
{
	int i, j, count;

	return Kruskal (individuals, info);
}