#include "functions.h"

/* ==================  Functions for randomness  ===================== */

	/*Generates a random number between 0 and 1 */
	double random_number()
	{
		return((double) rand() / ((double) RAND_MAX + 1));
	}

	int rand_upto (int n)
	{
		return (rand() / (RAND_MAX / (n + 1)));
	}

	int rand_1ton (int n)
	{
		return (rand() / (RAND_MAX / (n)) + 1);
	}

	/*Generates a random number between 0 and 1 
		double random_numberP ()
		{
			return (gsl_rng_uniform_pos (GLOBAL_RNG));
		}

		int rand_uptoP (int n)
		{
			return (gsl_rng_uniform_int (GLOBAL_RNG, n + 1));
		} 

		unsigned int poisson (double mu) 
		{
			return (gsl_ran_poisson(GLOBAL_RNG, mu));
  	} 
    other options

    double random_number()
    {
      return((double) rand() / ((double) RAND_MAX + 1));
    }

    int rand_upto (int n)
    {
      return ((int) floor(random_number() * (n + 1)));
    }

    int rand_1ton (int n)
    {
      return ((int) ceil(random_number() * (n + 1)));
    }

  */

	/*This is a binary genome generator. It generates the first genome.*/
	int* Generate_Genome (int genome_size)
	{
		int i;
		int* first_genome;

		first_genome = (int*) malloc (genome_size * sizeof(int));

		for (i = 0; i < genome_size; i++) {
			first_genome[i] = rand_upto(1);
		}
		return first_genome;
	}

/* =================================================================== */


/* ========================= Initializing ============================ */
	Parameters Set_Parameters () 
	{
		Parameters info;
		double rho;

		info = (Parameters) malloc (sizeof (parameters));

		info->number_individuals     = 1000;
		info->population_size        = 1000;
		/* The population can grow and sink. Here we estimate the grown aoround 20% */
		info->individual_vector_size = (int)(info->number_individuals * 1.5);
		info->genome_size            = 150;
		info->reproductive_distance  = (int) floor(0.05*info->genome_size);
		info->number_generations     = 2000;
		info->lattice_length         = 100;
		info->lattice_width          = 100;
		info->radius                 = 5;
		info->mutation               = 0.00025;
		info->dispersion             = 0.01;
		info->min_neighboors         = 3;
		info->max_increase           = 2;
		info->max_spot_density       = 100;
		/* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
		individuals that mark the density limit (60% of the original density) */
		rho = 0.83*((double) info->number_individuals)/((double) (info->lattice_length * info->lattice_width));
		info->density = (int) ceil(3.1416*rho*info->radius*info->radius*0.6);
		
		return info;
	}

	Population Alloc_Population (Parameters info)
	{
		Population individuals;
		int i;

		individuals  = (Population) malloc (info->individual_vector_size * sizeof (Individual));

		for (i = 0; i < info->individual_vector_size; i++) {
			individuals[i] = (Individual) malloc (sizeof (individual));
			individuals[i]->genome = (int*) malloc(info->genome_size * sizeof (int));
			individuals[i]->compatible_neighbors = CreateHeadedList ();
			individuals[i]->spatial_neighbors = CreateHeadedList ();
		}

		return individuals;
	}

	void Set_Initial_Values (Population progenitors, Parameters info)
	{
		int i, j;
		int* first_genome;

    	first_genome = Generate_Genome(info->genome_size);

    	for (i = 0; i < info->individual_vector_size; i++) {
    		for (j = 0; j < info->genome_size; j++) {
	        	progenitors[i]->genome[j] = first_genome[j];
	    	}
    	}
	 
    	for (i = 0; i < info->number_individuals; i++) {
	      progenitors[i]->x = random_number() * info->lattice_width;
	      progenitors[i]->y = random_number() * info->lattice_length;
	    }

	    free (first_genome);
	}

/* =================================================================== */


/* ======================== Space Functions ========================== */

	/* This function checks if an individual (j) is within the range of another individual */
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

		if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= r * r)
			return 1;
		else 
			return 0;
	}

	int Verify_Neighborhood (List neighborhood)
	{
		return (-(neighborhood->info + 1));
	}

	/* This function computes the neighbors an individual i can reproduce with and stores this info in a list */
	void Neighborhood (Graph G, Population progenitors, int focal, Parameters info, int increase)
	{
		int i;

		RestartList (&progenitors[focal]->compatible_neighbors);
		RestartList (&progenitors[focal]->spatial_neighbors);

		for (i = G->U - 1; i >= 0; i--) {
			if (focal != i) {
				if (Verify_Distance (progenitors, focal, i, info, increase)) {
					if (G->adj[focal][i] != 0) {
						AddCellInOrder(&progenitors[focal]->compatible_neighbors, i);
					}
					else {
						AddCellInOrder(&progenitors[focal]->spatial_neighbors, i);
					}
				}
			}	
		}
	}

	void Expand_Neighborhood (Graph G, Population progenitors, int focal, Parameters info, int increase)
	{
		int i;

		for (i = G->U - 1; i >= 0; i--) {
			if (focal != i) {
				if (Verify_Distance (progenitors, focal, i, info, increase - 1) == 0 && Verify_Distance (progenitors, focal, i, info, increase) == 1) {
					if (G->adj[focal][i] != 0) {
						AddCellInOrder(&progenitors[focal]->compatible_neighbors, i);
					}
					else {
						AddCellInOrder(&progenitors[focal]->spatial_neighbors, i);
					}
				}
			}	
		}
	}

	void Shrink_Neighborhood (Graph G, Population progenitors, int focal, Parameters info, int increase)
	{
		int i;

		if (increase > 0) {
			for (i = 0; i < G->U; i++) {
				if (focal != i) {
					if (Verify_Distance (progenitors, focal, i, info, 0) == 0 && Verify_Distance (progenitors, focal, i, info, increase) == 1) {
						if (G->adj[focal][i] != 0) {
							RemoveCell(&progenitors[focal]->compatible_neighbors, i);
						}
						else {
							RemoveCell(&progenitors[focal]->spatial_neighbors, i);
						}
					}
				}	
			}
		}
	}

	int Sort_Neighbor (Population progenitors, int i) 
	{
		int j, k, compatible_neighbors, all, other;
		List p;

		compatible_neighbors = Verify_Neighborhood (progenitors[i]->compatible_neighbors);
		all = compatible_neighbors + Verify_Neighborhood (progenitors[i]->spatial_neighbors);

		if (all) {
			k = rand_1ton (all);
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
		int i, occupation;

		occupation = 0;
		for (i = 0; i < G->U; ++i) {
			if (progenitors[i]->x == progenitors[focal]->x && progenitors[i]->y == progenitors[focal]->y) {
				occupation ++;
			}
		}

		return occupation;
	}

/* =================================================================== */


/* ======================= Graph functions =========================== */

	/* This function, called by main, compares the genomes and creates a Graph, where vertix are individuals,
	arches means they can reproduce (similar genomes). The weight of the arch is the distance
	between genomes. */
	void Stablish_Distances (Graph G, Population individuals, Parameters info)
	{
		int i, j, k, divergences;

		G->U = info->population_size;

		for (i = 0; i < G->U; i++) {
			for (j = i + 1; j < G->U; j++) {
				divergences = 0;
				for (k = 0; k < info->genome_size && divergences <= info->reproductive_distance + 1; k++) {
					if (individuals[i]->genome[k] != individuals[j]->genome[k]) {
						divergences++;
					}
				}

				if (divergences <= info->reproductive_distance) {
					InsertArc (G, i, j, divergences + 1);
				}
				else if (G->adj[i][j] != 0) {
					RemoveArc (G, i, j);
				}	
			}

			Neighborhood (G, individuals, i, info, 0);
		}
	}


	void DSFvisit (Graph G, Vertix v, int* parent, Population individuals, int species)
	{
	  int i;

	  for (i = 0; i < (G->U); i++) {
	    if (G->adj[v][i] != 0 && parent[i] == -1) {
	      parent[i] = v;
	      individuals[i]->species = species;
	      DSFvisit (G, i, parent, individuals, species);
	    }
	  }
	}

	void DepthFirstSearch (Graph G, int* counter_adress, Population individuals)
	{
	  int i;
	  int *parent, *comp;

	  parent = (int*) malloc ((G->U) * sizeof (int));
	  for (i = 0; i < (G->U); i++) {
	    parent[i] = -1;
	  }

	  (*counter_adress) = 0;

	  for (i = 0; i < (G->U); i++) {
	    if (parent[i] == -1) {
	      parent[i] = -2;
	      individuals[i]->species = (*counter_adress);
	      DSFvisit (G, i, parent, individuals, (*counter_adress));
	      (*counter_adress)++;
	    }
	  }

	  free (parent);
	}

/* =================================================================== */


/* ===================== Used for Reproduction ======================= */

	/* This function, called by Reproduction, defines the offspring position, that is, if it is going to move, how much,
	and in which direction. It can move in it's focal parent range, with 1% chance*/
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

	/* This function, called by Create_Offspring, allocates the mutation in the genome */
	void mutation (Population offspring, int baby, int mutation)
	{
		if (offspring[baby]->genome[mutation] == 1) {
			offspring[baby]->genome[mutation] = 0;
		}
		else {
			offspring[baby]->genome[mutation] = 1;
		}
	}

	/* This function, called by Reproduction, determines the characteristics of the offspring, based on the parent's.
	The new offspring will have the position of the focal individual (i). The genome of the offspring has, for
	each loci, 50% chance of coming from either of his parents */
	void Create_Offspring (Population progenitors, Population offspring, int baby, int focal, int other, int mate, Parameters info)
	{
	 	int i;
		
		Offspring_Position (progenitors, offspring, baby, focal, info);

		for (i = 0; i < info->genome_size; i++) {
			if (progenitors[other]->genome[i] != progenitors[mate]->genome[i]) {
				if (rand()%2 == 1) {
					offspring[baby]->genome[i] = progenitors[mate]->genome[i];
				}
				else {
					offspring[baby]->genome[i] = progenitors[other]->genome[i];
				}
			}
			else {
				offspring[baby]->genome[i] = progenitors[mate]->genome[i];
			}
			if (random_number() < info->mutation) {
				mutation (offspring, baby, i);
			}
		}
	}

	int Choose_Other (Graph G, int focal, Population progenitors, Parameters info, int increase, int changed[])
	{
		int j, i, all, compatible_neighbors, radius_increase, other, n;
		List p;

		radius_increase = 0;
		compatible_neighbors = 0;
		all = 0;

		for (i = 0; i < G->U; ++i) {
			if (i != focal)
				changed[i] = 0;
		}

		other = Sort_Neighbor (progenitors, focal);
		if (other != -1) {
			compatible_neighbors = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
			all = compatible_neighbors + Verify_Neighborhood(progenitors[other]->spatial_neighbors);
		}
	
		n = 0;
		while (compatible_neighbors < 2 && radius_increase < info->max_increase) {
			if (n > 1) {
				radius_increase ++;
				n = 0;
				other = focal;
				if (radius_increase > increase) {
					Expand_Neighborhood (G, progenitors, focal, info, radius_increase);
					changed[focal] = radius_increase;
				}
			}
			if (other != -1) other = Sort_Neighbor (progenitors, other);
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

		for (i = 0; i < G->U; ++i) {
			if (changed[i] > 0 && i != focal && i != other) {
				Shrink_Neighborhood (G, progenitors, i, info, changed[i]);
      }
		}

		return other;
	}

	/* This function, called by Reproduction, chooses the mate of the focal individual (i) based on the graph
	(who it can reproduce with) and the distance of the others (who is in their range).*/
	int Choose_Mate (Graph G, int focal, Population progenitors, Parameters info)
	{
		int j, i, neighbors, mate;
		List p;

		mate = -1;

		neighbors = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);

		if (neighbors) {
			i = rand_1ton (neighbors);
			
			for (j = 1, p = progenitors[focal]->compatible_neighbors->next; p != NULL && j < i; p = p->next, j++);
			
			if (j == i && p != NULL) {
				mate = p->info;
			} 
			else mate = -1;
		}
		else mate = -1;

		return mate;
	}

	void Reproduction (Graph G, Population progenitors, Population offspring, Parameters info)
	{
	int focal, mate, other, baby, other_neighborhood, all_neighborhood, compatible_neighborhood, increase, n, occupation, expand;
	int changed[G->U];

	baby = 0;

	for (focal = 0; focal < (G->U); focal++) {
		mate = -1;
		compatible_neighborhood = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);
		all_neighborhood = compatible_neighborhood + Verify_Neighborhood (progenitors[focal]->spatial_neighbors);
		if ((G->U) < info->number_individuals && all_neighborhood < info->density) {
			occupation = Site_Occupation (G, progenitors, focal, info);
			if (compatible_neighborhood >= info->min_neighboors && occupation < info->max_spot_density/3) {
				mate = Choose_Mate (G, focal, progenitors, info);
				for (n = 0; n < 2 && mate != -1; n++) {
					Create_Offspring (progenitors, offspring, baby, focal, focal, mate, info);
					baby ++;
				}
			}
		}
		else {
			for (increase = 0; all_neighborhood < 2 && increase < info->max_increase; increase++) {
				Expand_Neighborhood (G, progenitors, focal, info, increase + 1);
				compatible_neighborhood = Verify_Neighborhood (progenitors[focal]->compatible_neighbors);
				all_neighborhood = compatible_neighborhood + Verify_Neighborhood (progenitors[focal]->spatial_neighbors);
			}
			if (all_neighborhood > 1) {
				changed[focal] = increase;
				other = focal;
				other_neighborhood = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
				if (random_number() < 0.37 || compatible_neighborhood < info->min_neighboors) {
					other = Choose_Other (G, focal, progenitors, info, increase, changed);
					if (other != -1) other_neighborhood = Verify_Neighborhood (progenitors[other]->compatible_neighbors);
					else other_neighborhood = 0;
				}
				if (other != -1) {
					if (other_neighborhood > 1) {
					mate = Choose_Mate (G, other, progenitors, info);
						if (mate != -1) {
						Create_Offspring (progenitors, offspring, baby, focal, other, mate, info);
						baby ++;
						}
					}
					if (other != focal && changed[other] > 0) {
						Shrink_Neighborhood (G, progenitors, other, info, changed[other]);
					}
				}
				if (changed[focal] > 0) 
					Shrink_Neighborhood (G, progenitors, focal, info, changed[focal]);
			}
		}
	}
	info->population_size = baby;
	}

/* =================================================================== */


/* ==================== Exchange Generations ========================= */

	/*This function, called by main, Exchanges the generation's vector's pointers*/
	void Swap_Generations (Population* progenitors_pointer, Population* offspring_pointer)
	{
		Population helper;

		helper = (*progenitors_pointer);
		(*progenitors_pointer) = (*offspring_pointer);
		(*offspring_pointer) = helper;
	}

/* =================================================================== */


/* ====================== Counting species =========================== */

	/* This function, called by main, calls DFS to count the number of maximal connected components in the graph */
	int Count_Species (Graph G, Population individuals)
	{
		int counter;

		DepthFirstSearch (G, &counter, individuals);

		return counter;
	}

/* =================================================================== */


/* =========================== Freeing =============================== */

	void Free_Population (Population individuals, Parameters info)
	{
		int i;

		for (i = 0; i < info->individual_vector_size; i++) {
			if (individuals[i]->genome != NULL)
			free (individuals[i]->genome);
			DestroyList (&individuals[i]->compatible_neighbors);
			DestroyList (&individuals[i]->spatial_neighbors);
			free(individuals[i]);
	    }

	    free (individuals);
	}

/* =================================================================== */


/* =========================== Testing =============================== */

	int CheckSpecies (Graph G, Population individuals, Parameters info) {
		int i, j;

		for (i = 0; i < G->U; ++i) {
			for (j = i + 1; j < G->U; ++j) {
				if (G->adj[i][j] >= 1) {
					if (G->adj[j][i] != G->adj[i][j]) {
						printf("ERRO NA CONSTRUÇÃO DAS ARESTAS +\n");
						return 0;
					} 
					if (individuals[i]->species != individuals[j]->species) {
						printf("ERRO NA BUCCA DE ESPECIES 1\n");
						return 0;
					}
				}
				else {
					if (G->adj[j][i] != G->adj[i][j]) {
						printf("G->A: %d\n", G->A);
						printf("ERRO NA CONSTRUÇÃO DAS ARESTAS -\n");
						return 0;
					}
				}
			}
		}
		return 1;
	}

	void Count_Sizes (Graph G, Population individuals, int total, Parameters info, int sizes[]) 
	{
		int i;

		for (i = 0; i <= total; ++i) {
			sizes[i] = 0;
		}

		for (i = 0; i < G->U; ++i) {
			sizes[individuals[i]->species]++;
			if (individuals[i]->species > total || individuals[i]->species < 0) {
				printf("species error\n");
			}
		}
	}

/* =================================================================== */