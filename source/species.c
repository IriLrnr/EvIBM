#include "../include/species.h"

void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, k, i_compatible, increase;

	Restart_Neighborhood (progenitors, info);

	for (i = 0; i < info->population_size; i++) {
		//PrintList(progenitors[i]->compatible_neighbors);
		//PrintList(progenitors[i]->spatial_neighbors);
		for (j = info->population_size; j > i; j--) {
			if (Verify_Distance (progenitors, i, j, info, 0)) {
				if (Compare_Genomes (progenitors, i, j, info)) {
					AddCellInOrder (&progenitors[i]->compatible_neighbors, j);
					AddCellInOrder (&progenitors[j]->compatible_neighbors, i);
					progenitors[i]->neighbors_address[1]++;
					progenitors[j]->neighbors_address[1]++;
					progenitors[j]->species = progenitors[i]->species; /* will this work? dont know*/
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

		//printf("fim\n");
		//for (k = 0; k < 6; k++) {
		//	printf("%d ", progenitors[i]->neighbors_address[k]);
		//}
		//printf("\n");
		//PrintList(progenitors[i]->compatible_neighbors);
		//PrintList(progenitors[i]->spatial_neighbors);
	}
}

int Count_Species (Population individuals)
{
	int counter = 10;
	return counter;
}

void Count_Sizes (Population individuals, int total, Parameters info, int sizes[]) 
{
	int i;

	for (i = 0; i <= total; ++i) {
		sizes[i] = 0;
	}

	for (i = 0; i < info->population_size; ++i) {
		sizes[individuals[i]->species]++;
		if (individuals[i]->species > total || individuals[i]->species < 0) {
			printf("species error\n");
		}
	}
}