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
		individuals[i]->neighbors_address = malloc (6 * sizeof (int));
		individuals[i]->neighbors_address = (-1, -1, -1, -1, -1, -1);	
	}
	printf("Individuals 12 adreessses\n");
	for (i = 0; i < 6; ++i)
	{
		printf("%d\n", individuals[12]->neighbors_address[i]);
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