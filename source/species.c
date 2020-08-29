#include "../include/species.h"

void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, k, i_compatible, increase;

	info->population_size = info->child_population_size;

	Restart_Neighborhood (progenitors, info);

	for (i = 0; i < info->population_size; i++) {
		for (j = info->population_size; j > i; j--) {
			if (Verify_Distance (progenitors, i, j, info, 0)) {
				if (Compare_Genomes (progenitors, i, j, info)) {
					AddCellInOrder (&progenitors[i]->compatible_neighbors, j);
					AddCellInOrder (&progenitors[j]->compatible_neighbors, i);
					progenitors[i]->neighbors_address[1]++;
					progenitors[j]->neighbors_address[1]++;
					if (progenitors[j]->species < progenitors[i]->species) {
						progenitors[i]->species = progenitors[j]->species;
						progenitors[j]->species_size += progenitors[i]->species_size;
					}
					else {
						progenitors[j]->species = progenitors[i]->species;
						progenitors[i]->species_size += progenitors[j]->species_size;
					}
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

void Union (Population individuals, int i, int j) {
	int k;

	i = Find(individuals, i);
	j = Find(individuals, j);

	if (i == j)  return;
	if (individuals[i]->species_size > individuals[j]->species_size) {
		k = i;
		i = j;
		j = k;
	}
	individuals[i]->species = j;
	individuals[j]->species_size += individuals[i]->species_size;
}

int Kruskal (Population individuals, Parameters info) {
	int i, j, spp_i, spp_j, count;
	List p, q;

	for (i = 0; i < info->population_size; ++i) {
		for (j = i+1; j < info->population_size; j++) {
			if (Find(individuals, i) == Find(individuals, j)) {
				Union (individuals, i, j);
			}
			else {
				if (!Compared (individuals, i, j, info)) {
					if (Compare_Genomes (individuals, i, j, info)) {
						Union (individuals, i, j);
					}
				}
			}
		}
	}

	for (count = 0, i = 0; i < info->population_size; i++) {
		if (individuals[i]->species == i) count ++;
	}

	return count;
}

int Count_Species (Population individuals, Parameters info)
{
	/*int i, j;
	printf("antes\n");
	for (i = 0; i < info->population_size; i++) {
		printf("%d ", individuals[i]->species_size);
	}
	printf("\ndps\n");
	j = Kruskal(individuals, info);
	for (i = 0; i < info->population_size; i++) {
		printf("%d ", individuals[i]->species_size);
	}
	printf("\n");

	return j;*/

	return Kruskal (individuals, info);
}