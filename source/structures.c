#include "structures.h"

/* @ Alloc_Population*/
Population Alloc_Population (Parameters info)
{
	Population individuals;
	int i, j, all_individuals;

	all_individuals = (int)(info->number_individuals*1.5);

	individuals  = (Population) malloc (all_individuals * sizeof (Individual));

	for (i = 0; i < all_individuals; i++) {
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
/* @ end */

/* @ Free_Population*/
void Free_Population (Population individuals, Parameters info)
{
	int i, all_individuals;

	all_individuals = (int)(info->number_individuals*1.5);

	for (i = 0; i < all_individuals; i++) {
		DestroyList (&individuals[i]->genome);
		DestroyList (&individuals[i]->compatible_neighbors);
		DestroyList (&individuals[i]->spatial_neighbors);
		free(individuals[i]->neighbors_address);
		free(individuals[i]);
    }

    free (individuals);
}
/* @ end */

/* @ Swap_Generations */
void Swap_Generations (Population* progenitors_pointer, Population* offspring_pointer)
{
	Population helper;

	helper = (*progenitors_pointer);
	(*progenitors_pointer) = (*offspring_pointer);
	(*offspring_pointer) = helper;
}
/* @ end */

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

/* @ Union_Find */
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
/* @ end */
