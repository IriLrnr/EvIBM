#include "../include/structures.h"

Population Alloc_Population (Parameters info)
{
	Population individuals;
	int i, j;

	individuals  = (Population) malloc (info->individual_vector_size * sizeof (Individual));

	for (i = 0; i < info->individual_vector_size; i++) {
		individuals[i] = (Individual) malloc (sizeof (individual));
		individuals[i]->genome = CreateHeadedList ();
		individuals[i]->compatible_neighbors = CreateHeadedList ();
		individuals[i]->spatial_neighbors = CreateHeadedList ();
		individuals[i]->neighbors_address = malloc (6 * sizeof (int));
		individuals[i]->species = i;
		individuals[i]->species_size = 1;
		individuals[i]->radius_increase = 0;
		individuals[i]->local_density = 0;
		for (j = 0; j < 6; ++j) {
			individuals[i]->neighbors_address[j] = 0; 
		}
	}

	return individuals;
}

void Free_Population (Population individuals, Parameters info)
{
	int i;

	for (i = 0; i < info->individual_vector_size; i++) {
		DestroyList (&individuals[i]->genome);
		DestroyList (&individuals[i]->compatible_neighbors);
		DestroyList (&individuals[i]->spatial_neighbors);
		free(individuals[i]->neighbors_address);
		free(individuals[i]);
    }

    free (individuals);
}

void Swap_Generations (Population* progenitors_pointer, Population* offspring_pointer)
{
	Population helper;

	helper = (*progenitors_pointer);
	(*progenitors_pointer) = (*offspring_pointer);
	(*offspring_pointer) = helper;
}

int max (int i, int j) 
{
	if (i >= j) return i;
	return j;
}

int min (int i, int j) 
{
	if (i >= j) return j;
	return i;
}

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
