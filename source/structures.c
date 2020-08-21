#include "../include/structures.h"

Population Alloc_Population (Parameters info)
{
	Population individuals;
	int i;

	individuals  = (Population) malloc (info->individual_vector_size * sizeof (Individual));

	for (i = 0; i < info->individual_vector_size; i++) {
		individuals[i] = (Individual) malloc (sizeof (individual));
		individuals[i]->genome = CreateHeadedList ();
		individuals[i]->compatible_neighbors = CreateHeadedList ();
		individuals[i]->spatial_neighbors = CreateHeadedList ();
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