#include "../include/space.h"

void Set_Initial_Position (Population progenitors, Parameters info)
{
	int i;
 
	for (i = 0; i < info->number_individuals; i++) {
    	progenitors[i]->x = random_number() * info->lattice_width;
    	progenitors[i]->y = random_number() * info->lattice_length;
    }
}

int Verify_Distance (Population progenitors, int focal, int mate, Parameters info, int increase)
{
	double x, x0, y, y0, r;
	
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

	if ((x - x0) * (x - x0) + (y - y0) * (y - y0) < r * r)
		return 1;
	else 
		return 0;
}

int Verify_Neighborhood (List neighborhood)
{
	return (Verify_Head (&neighborhood));
}

int Sort_Neighbor (Population progenitors, int i) 
{
	int j, k, compatible_neighbors, all, other;
	List p;

	if (i == -1) return -1;

	compatible_neighbors = Verify_Neighborhood (progenitors[i]->compatible_neighbors);
	all = compatible_neighbors + Verify_Neighborhood (progenitors[i]->spatial_neighbors);

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

int Site_Occupation (Graph G, Population progenitors, int focal, Parameters info) 
{
	int i, j, occupation, all, compatible_neighbors;
	List p;

	occupation = 0;
	
	compatible_neighbors = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);
	all = compatible_neighbors + Verify_Neighborhood (progenitors[focal]->spatial_neighbors);

	if (all) {
		if (compatible_neighbors) {
			for (p = progenitors[focal]->compatible_neighbors->next; p != NULL && j <= compatible_neighbors; p = p->next, j++) {
				if (p !=  NULL) {
					i = p->info;
					if (Verify_Distance (progenitors, focal, i, info, -(info->radius - 1)) == 1) {
						occupation++;
					}
				}
			}
		}
		if (all - compatible_neighbors > 0) {
			for (j = 1, p = progenitors[focal]->compatible_neighbors->next; p != NULL && j <= all - compatible_neighbors; p = p->next, j++) {
				if (p !=  NULL) {
					i = p->info;
					if (Verify_Distance (progenitors, focal, i, info, -(info->radius - 1)) == 1) {
						occupation++;
					}
				}
			}
		}
	}

	return occupation;
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

int Choose_Mate (Graph G, int focal, Population progenitors, Parameters info)
{
	int j, i, neighbors, mate;
	List p;

	mate = -1;

	neighbors = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);

	if (neighbors) {
		i = rand_1to (neighbors);
		
		for (j = 1, p = progenitors[focal]->compatible_neighbors->next; p != NULL && j < i; p = p->next, j++);
		
		if (j == i && p != NULL) {
			mate = p->info;
		} 
		else mate = -1;
	}
	else mate = -1;

	return mate;;;
}

int Choose_Other (Graph G, int focal, Population progenitors, Parameters info, int increase, int changed[])
{
	int j, i, all, compatible_neighbors, radius_increase, other, n, focal_neighbors;
	List p;

	other = focal;
	radius_increase = 0;
	compatible_neighbors = all = 0;

	for (i = 0; i < G->U; ++i) {
		if (i != focal)
			changed[i] = 0;
	}

	focal_neighbors = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);

	if (random_number() < 0.37 || focal_neighbors < info->min_neighboors) {
		other = Sort_Neighbor (progenitors, focal);
		compatible_neighbors = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
		all = compatible_neighbors + Verify_Neighborhood(progenitors[other]->spatial_neighbors);
		if (other == -1) printf("ERRO");
		if (increase > 0) Shrink_Neighborhood (G, progenitors, focal, info, increase);
		n = 0;
		while (compatible_neighbors < info->min_neighboors && radius_increase < info->max_increase) {
			if (n > 1) {
				radius_increase ++;
				n = 0;
				other = focal;
				Expand_Neighborhood (G, progenitors, focal, info, radius_increase);
				changed[focal] = radius_increase;
			}
			other = Sort_Neighbor (progenitors, other);
			if (other != -1) {
				for (j = 0; j < radius_increase; j++) {
					Expand_Neighborhood (G, progenitors, other, info, j + 1);
        		}
				changed[other] = radius_increase;
				compatible_neighbors = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
				all = compatible_neighbors + Verify_Neighborhood (progenitors[other]->spatial_neighbors);
			}
			n++;
    	}
	}

	for (i = 0; i < G->U; ++i) {
		if (changed[i] > 0 && i != focal && i != other) {
			Shrink_Neighborhood (G, progenitors, i, info, changed[i]);
 		}
	}

	return other;
}

void Stablish_Distances (Population progenitors, Parameters info) 
{
	int i, j, i_compatible, increase;

	RestartList (&progenitors[focal]->compatible_neighbors);
	RestartList (&progenitors[focal]->spatial_neighbors);

	for (i = 0; i < info->population_size; i++) {
		for (j = 0; j < info->population_size; j++) {
			if (Verify_Distance (progenitors, i, j, info, 0)) {
				if (Compare_Genomes (progenitors, i, j, info)) {
					AddCellInOrder (&progenitors[i]->compatible_neighbors, j);
					AddCellInOrder (&progenitors[j]->compatible_neighbors, i);
					progenitors[i]->neighbors_address[1]++;
					progenitors[j]->neighbors_address[1]++;
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
		increase = 0;
		i_compatible = Verify_Neighborhood (progenitors[i]->compatible_neighbors);
		while (i_compatible < info->min_neighboors && increase <= info->max_increase) {
			Expand_Neighborhood (progenitors, i, info, increase);
		}
	}
}



void Expand_Neighborhood (Population progenitors, int focal, Parameters info, int increase, Parameters info)
{
	int i;

	for (i = info->population_size - 1; i >= 0; i--) {
		if (focal != i) {
			if (Verify_Distance (progenitors, focal, i, info, increase - 1) == 0 && Verify_Distance (progenitors, focal, i, info, increase) == 1) {
				if (Compare_Genomes (progenitors, focal, i, info)) {
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
