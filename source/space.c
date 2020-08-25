#include "../include/space.h"

void Set_Initial_Position (Population progenitors, Parameters info)
{
	int i;
 
	for (i = 0; i < info->number_individuals; i++) {
    	progenitors[i]->x = random_number() * info->lattice_width;
    	progenitors[i]->y = random_number() * info->lattice_length;
    	//progenitors[i]->neighbors_address = (-1, -1, -1, -1, -1, -1);
    }
}

int Verify_Distance (Population progenitors, int focal, int mate, Parameters info, int increase)
{
	double x, x0, y, y0, r, dist;
	
	r = info->radius + increase;

	x0 = progenitors[focal]->x;
	y0 = progenitors[focal]->y;
	x = progenitors[mate]->x;
	y = progenitors[mate]->y;

	if (y0 >= info->lattice_length - r && y <= r)
		y = y + info->lattice_length;

	if (y0 <= r && y >= info->lattice_length - r)
		y = y - info->lattice_length;

	if (x0 >= info->lattice_width - r && x <= r)
		x = x + info->lattice_width;

	if (x0 <= r && x >= info->lattice_width - r)
		x = x - info->lattice_length;

	dist = (x - x0) * (x - x0) + (y - y0) * (y - y0);

	if (dist < r * r)
		return 1;
	else 
		return 0;
}

int Find_Compatible_Neighborhood (Population progenitors, int focal, Parameters info, int increase)
{
	if (progenitors[focal]->neighbors_address[increase] == -1) {
		Expand_Neighborhood (progenitors, focal, info, increase);
	}
	return (progenitors[focal]->neighbors_address[increase + 1]);
}

int Find_Neighborhood (Population progenitors, int focal, Parameters info, int increase)
{
	if (progenitors[focal]->neighbors_address[increase] == -1) {
		Expand_Neighborhood (progenitors, focal, info, increase);
	}
	return (progenitors[focal]->neighbors_address[increase] + progenitors[focal]->neighbors_address[increase + 1]);
}

int Sort_Neighbor (Population progenitors, int i, Parameters info, int increase) 
{
	int j, k, compatible_neighbors, all, other;
	List p;

	if (i == -1) return -1;

	compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info, increase);
	all = Find_Neighborhood (progenitors, other, info, increase);

	if (all) {
		k = rand_1to (all);
		if (k <= compatible_neighbors)
			for (j = 1, p = progenitors[i]->compatible_neighbors->next; p != NULL && j < k; p = p->next, j++);
		else {
			k -= compatible_neighbors;
			for (j = 1, p = progenitors[i]->spatial_neighbors->next; p != NULL && j < k; p = p->next, j++);	
		}

		if (j == k && p != NULL) {
			other = p->info;
		}
		else other = -1;
	}
	else other = -1;

	return other;
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
	int j, k, neighbors, mate, increase;
	List p;

	mate = -1;

	for (increase = 1; increase <= info->max_increase; ++increase)
		if (progenitors[focal]->neighbors_address[increase] == -1) break;

	neighbors = Find_Compatible_Neighborhood (progenitors, focal, info, increase - 1);

	if (neighbors) {
		k = rand_1to (neighbors);
		
		for (j = 1, p = progenitors[focal]->compatible_neighbors->next; p != NULL && j < k; p = p->next, j++);
		
		if (j == k && p != NULL) {
			mate = p->info;
		} 
		else mate = -1;
	}
	else mate = -1;

	return mate;
}

int Choose_Other (Population progenitors, int focal, Parameters info, int increase)
{
	int j, i, all, compatible_neighbors, radius_increase, other, n, focal_neighbors;
	List p;

	other = focal;
	radius_increase = 0;
	compatible_neighbors = all = 0;

	focal_neighbors = Find_Compatible_Neighborhood (progenitors, focal, info, increase);

	if (random_number() < 0.37 || focal_neighbors < info->min_neighboors) {
		other = Sort_Neighbor (progenitors, focal, info, increase);
		compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info, 0);
		all = Find_Neighborhood (progenitors, other, info, 0);
		if (other == -1) printf("ERRO");
		while (compatible_neighbors < info->min_neighboors && radius_increase < info->max_increase) {
			if (n > 1) {
				radius_increase ++;
				n = 0;
				other = focal;
				compatible_neighbors = Find_Neighborhood (progenitors, focal, info, radius_increase);
			}
			other = Sort_Neighbor (progenitors, other, info, radius_increase);
			if (other != -1) {
				compatible_neighbors = Find_Compatible_Neighborhood (progenitors, other, info, radius_increase);
				all = Find_Neighborhood (progenitors, other, info, radius_increase);
			}
			n++;
    	}
	}

	return other;
}

void Expand_Neighborhood (Population progenitors, int focal, Parameters info, int increase)
{
	int i;

	if (increase > 2) {
		printf ("Error in Expand_Neighborhood (increase > 2)");	
	}

	if (progenitors[focal]->neighbors_address[increase] != -1) {
		progenitors[i]->neighbors_address[increase] = 0;
		progenitors[i]->neighbors_address[increase + 1] = 0;
		for (i = info->population_size - 1; i >= 0; i--) {
			if (focal != i) {
				if (Verify_Distance (progenitors, focal, i, info, increase - 1) == 0 && Verify_Distance (progenitors, focal, i, info, increase) == 1) {
					if (progenitors[focal]->species == progenitors[i]->species) {
						AddCellInOrder(&progenitors[focal]->compatible_neighbors, i);
						progenitors[focal]->neighbors_address[1 + increase] ++;
					}
					else {
						AddCellInOrder(&progenitors[focal]->spatial_neighbors, i);
						progenitors[focal]->neighbors_address[1 + increase] ++;
					}
				}
			}	
		}
	}
}


