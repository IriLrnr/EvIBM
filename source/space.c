#include "../include/space.h"

void Set_Initial_Position (Population individuals, Parameters info)
{
	int i;
 
	for (i = 0; i < info->number_individuals; i++) {
    	individuals[i]->x = random_number() * info->lattice_width;
    	individuals[i]->y = random_number() * info->lattice_length;
    }
}

int Verify_Distance (Population individuals, int i, int j, Parameters info, int increase)
{
	double x, x0, y, y0, r;
	
	r = info->radius + increase;

	x0 = progenitors[i]->x;
	y0 = progenitors[i]->y;
	x = progenitors[j]->x;
	y = progenitors[j]->y;

	if (y0 >= info->lattice_length - r && y <= r)
		y = y + info->lattice_length;

	if (y0 <= r && y >= info->lattice_length - r)
		y = y - info->lattice_length;

	if (x0 >= info->lattice_width - r && x <= r)
		x = x + info->lattice_width;

	if (x0 <= r && x >= info->lattice_width - r)
		x = x - info->lattice_length;

	if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < r * r) 
		return 1;
	else 
		return 0;
}

int Find_Compatible_Neighborhood (Population individuals, int i, Parameters info)
{
	int increase = individuals[i]->radius_increase;
	return (individuals[i]->neighbors_address[increase*2 + 1]);
}

int Find_Neighborhood (Population individuals, int i, Parameters info)
{
	int increase = individuals[i]->radius_increase;
	return (individuals[i]->neighbors_address[increase*2] + individuals[i]->neighbors_address[increase*2 + 1]);
}

void Restart_Neighborhood (Population individuals, Parameters info)
{
	int i, j;

	for (i = 0; i < info->population_size; ++i) {
		RestartList (&individuals[i]->compatible_neighbors);
		RestartList (&individuals[i]->spatial_neighbors);
		for (j = 0; j < 6; j++) {
			individuals[i]->neighbors_address[j] = 0;
		}
	}
}

int Sort_Neighbor (Population progenitors, int i, Parameters info) 
{
	int j, k, compatible_neighbors, all, neighbor;
	List p;

	if (i == -1) return -1;

	compatible_neighbors = Find_Compatible_Neighborhood (progenitors, i, info);
	all = Find_Neighborhood (progenitors, i, info);

	if (all > 0) {
		k = rand_1to (all);
		if (k <= compatible_neighbors)
			for (j = 1, p = progenitors[i]->compatible_neighbors->next; p != NULL && j < k; p = p->next, j++);
		else {
			k -= compatible_neighbors;
			for (j = 1, p = progenitors[i]->spatial_neighbors->next; p != NULL && j < k; p = p->next, j++);	
		}

		if (j == k && p != NULL) {
			neighbor = p->info;
		}
		else neighbor = -1;
	}
	else neighbor = -1;

	return neighbor;
}

void Offspring_Position (Population progenitors, Population offspring, int baby, int focal, Parameters info)
{
	double movement_x, movement_y, r, theta;

	movement_x = movement_y = 0;

	offspring[baby]->x = progenitors[focal]->x;
	offspring[baby]->y = progenitors[focal]->y;

	if (random_number() <= info->dispersion) {
		while (movement_x == 0 && movement_y == 0) {
			r = random_number() * info->radius;
			theta = random_number() * 2 * 3.14159265359;

			movement_y = sin(theta) * r;
			movement_x = cos(theta) * r;
		}

		/* If an individual moves out of the lattice, it will reapear in the other side, because the lattice work as a toroid */
		if (offspring[baby]->x + movement_x <= info->lattice_width && progenitors[focal]->x + movement_x >= 0)
	  		offspring[baby]->x += movement_x;

		else if (progenitors[focal]->x + movement_x > info->lattice_width)
			offspring[baby]->x = offspring[baby]->x + movement_x - info->lattice_width;

		else if (progenitors[focal]->x + movement_x < 0)
			offspring[baby]->x = offspring[baby]->x + movement_x + info->lattice_width;

		if (progenitors[focal]->y + movement_y <= info->lattice_length && progenitors[focal]->y + movement_y >= 0)
	  		offspring[baby]->y = offspring[baby]->y + movement_y;

		else if (progenitors[focal]->y + movement_y > info->lattice_length)
			offspring[baby]->y = offspring[baby]->y + movement_y - info->lattice_length;

		else if (progenitors[focal]->y + movement_y < 0)
			offspring[baby]->y = offspring[baby]->y + movement_y + info->lattice_length;
	}
}

int Choose_Mate (Population progenitors, int focal, Parameters info)
{
	int j, k, neighbors, mate;
	List p;

	mate = -1;

	neighbors = Find_Compatible_Neighborhood (progenitors, focal, info);

	if (neighbors) {
		k = rand_1to (neighbors);
		
		for (j = 1, p = progenitors[focal]->compatible_neighbors->next; p != NULL && j < k; p = p->next, j++);
		
		if (j == k && p != NULL) {
			mate = p->info;
		} 
		else mate = -1;
	}
	else mate = -1;

	//printf("mate = %d\n", mate);

	return mate;
}

int Choose_Other (Population progenitors, int focal, Parameters info)
{
	int j, i, all, compatible_neighbors, radius_increase, other, n, focal_neighbors;

	other = focal;
	radius_increase = 0;
	compatible_neighbors = all = 0;


	focal_neighbors = Find_Compatible_Neighborhood (progenitors, focal, info);

	if (random_number() < 0.37 || focal_neighbors < info->min_neighboors) {
		other = Sort_Neighbor (progenitors, focal, info);
		progenitors[other]->radius_increase	 = radius_increase;
		compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info);
		while (compatible_neighbors < 2 && radius_increase < info->max_increase) {
			if (n > 1) {
				radius_increase ++;
				other = focal;
				progenitors[other]->radius_increase	 = radius_increase;
				compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info);
				n = 0;
			}
			other = Sort_Neighbor (progenitors, other, info);
			if (other != -1) {
				progenitors[other]->radius_increase = radius_increase;
				compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info);
			}
			n++;
    	}
	}

	return other;
}