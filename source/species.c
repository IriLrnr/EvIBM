#include "../include/species.h"

int Find (Population individuals, int i) 
{
	if (individuals[i]->species == i) {
		return i;
	}
	individuals[i]->species = Find (individuals, individuals[i]->species);
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

void Add_To_Neighborhood (Population progenitors, int i, int j, Parameters info, int increase) 
{
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

void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, i_compatible, increase;

	info->population_size = info->child_population_size;

	Restart_Neighborhood (progenitors, info);

	for (increase = info->max_increase; increase >= 0 ; increase--) {
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
	for (i = 0; i < info->population_size; ++i) {
		//PrintList(progenitors[i]->compatible_neighbors);
		//PrintList(progenitors[i]->spatial_neighbors);
		for (increase = 0; increase < info->max_increase; increase++) {
			progenitors[i]->neighbors_address[2*increase + 2] += progenitors[i]->neighbors_address[2*increase];
			progenitors[i]->neighbors_address[2*increase + 3] += progenitors[i]->neighbors_address[2*increase + 1];
		}
		/*for (int j = 0; j < 6; ++j)
		{
			printf("%d ", progenitors[i]->neighbors_address[j]);
		}
		printf("\n");*/
	}
}

int Count_Species (Population individuals, Parameters info)
{
	int count, i;

	for (count = 0, i = 0; i < info->population_size; i++) {
		if (individuals[i]->species == i) count ++;
	}


	return count;
}