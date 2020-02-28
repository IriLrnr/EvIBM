#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "linkedlist.h"

/* =======================  Definitions ========================== */
	/* Here we define and individual as a struct with genome, species and location, and
	a population as a vector of individuals*/
	typedef struct
	{
		int* genome;
		int species;
		float x;
		float y;
		List neighborhood;
	} individual;

	typedef individual * Individual;

	typedef Individual * Population;

	/* Here we define a struct to keep all the fixed parameters wildely used in the simulation,
	because this way they're easy to pass between functions */

	typedef struct
	{
		int number_individuals;
		int individual_vector_size;
		int population_size;
		int genome_size;
		int reproductive_distance;
		int number_generations;
		int neighbors;
		float lattice_width;
		float lattice_lenght;
		float radius;
	} parameters;

	typedef parameters * Parameters;

/* ======================================================================= */


/* =======================  Used everywhere  ========================== */

	/*Generates a random number between 0 and 1 */ /* TESTED OK */
	float random_number()
	{
		return((float)rand() / ((float)RAND_MAX + 1));
	}

	int rand_upto (int n)
	{
		return (rand() / (RAND_MAX / n + 1));
	}


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

	/* This function checks if an individual (j) is within the range of another individual */
	int Verify_Distance (Population progenitors, int focal, int mate, Parameters info, int increase)
	{
		int x_compatible, y_compatible, x_out_left, x_out_right, y_out_up, y_out_down;

		y_compatible = 0;
		x_compatible = 0;

		x_out_left = 0;
		x_out_right = 0;
		y_out_up = 0;
		y_out_down = 0;

		/* If an individual ratio reaches an end of the lattice, it will look on the other side, because the lattice work as a toroid */
		if (progenitors[mate]->x <= progenitors[focal]->x + info->radius + increase && progenitors[mate]->x >= progenitors[focal]->x - info->radius + increase) {
			x_compatible = 1;
		}
		if (progenitors[mate]->y <= progenitors[focal]->y + info->radius + increase && progenitors[mate]->y >= progenitors[focal]->y - info->radius + increase) {
			y_compatible = 1;
		}

		if (!x_compatible) {
			if (progenitors[focal]->x + info->radius + increase > info->lattice_width) {
				x_out_right = progenitors[focal]->x + info->radius + increase - info->lattice_width;
				if (progenitors[mate]->x <= x_out_right) {
					x_compatible = 1;
				}
			}
			else if (progenitors[focal]->x - info->radius + increase < 0) {
				x_out_left = progenitors[focal]->x - info->radius + increase + info->lattice_width;
				if (progenitors[mate]->x >= x_out_left) {
					x_compatible = 1;
				}
			}
		}

		if (!y_compatible) {
			if (progenitors[focal]->y + info->radius + increase > info->lattice_lenght) {
				y_out_up = progenitors[focal]->y + info->radius + increase - info->lattice_lenght;
				if (progenitors[mate]->y <= y_out_up) {
					y_compatible = 1;
				}
			}
			else if (progenitors[focal]->y - info->radius + increase < 0) {
				y_out_down = progenitors[focal]->y - info->radius + increase + info->lattice_lenght;
				if (progenitors[mate]->y >= y_out_down) {
					y_compatible = 1;
				}
			}
		}

		if (x_compatible && y_compatible) return 1;
		else return 0;
	}

	int Verify_Neighborhood (List neighborhood)
	{
		return (-(neighborhood->info + 1));
	}

	/* This function computes the neighbors an individual i can reproduce with and stores this info in a list */
	void neighborhood (Graph G, Population progenitors, int focal, Parameters info, int increase)
	{
		int mate;

		for (mate = 0; mate < (G->U); mate++) {
			if (G->adj[focal][mate] != 0 && Verify_Distance (progenitors, focal, mate, info, increase)){
				AddCellInOrder(&progenitors[focal]->neighborhood, mate);
			}
		}
	}

	void expand_neighborhood (Graph G, List bigger_neighborhood, Population progenitors, int focal, Parameters info, int increase)
	{
		int mate;

		for (mate = 0; mate < (G->U); mate++) {
			if (G->adj[focal][mate] != 0 && Verify_Distance (progenitors, focal, mate, info, increase)) {
				if (!Verify_Distance (progenitors, focal, mate, info, increase - 1)) {
					AddCellInOrder(&bigger_neighborhood, mate);
				}
			}
		}
	}

/* ====================================================================== */

/* ========================== Initializing ============================== */
	Parameters Set_Parameters () 
	{
		Parameters info;

		info = (Parameters) malloc (sizeof (parameters));

		info->number_individuals     = 1000;
		info->population_size        = 1000;
		/* The population can grow and sink. Here we estimate the grown aoround 20% */
		info->individual_vector_size = (int)(info->number_individuals * 1.2);
		info->reproductive_distance  = 7;
		info->genome_size            = 150;
		info->number_generations     = 20;
		info->lattice_lenght         = 100;
		info->lattice_width          = 100;
		info->radius                 = 5;
		/* We need to know if the density around an individual is less than sufficient for reproduction, Here is the number os
		individuals that mark the density limit (60% of the original density) */
		info->neighbors = (int)(0.6*info->radius*info->radius*3.14159*info->number_individuals) / (info->lattice_lenght * info->lattice_width);
		
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
			individuals[i]->neighborhood = CreateHeadedList ();
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
	      progenitors[i]->y = random_number() * info->lattice_lenght;
	    }

	    free (first_genome);
	}

/* ==================================================================== */

/* =======================  Used for Creating the graph  ========================== */

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
				for (k = 0; k < info->genome_size; k++) {
					if (individuals[i]->genome[k] != individuals[j]->genome[k]) {
						divergences++;
					}
				}

				if (divergences <= info->reproductive_distance) {
					InsertArc (G, i, j, (info->genome_size - divergences));
				}
				else if (G->adj[i][j] != 0) {
					RemoveArc (G, i, j);
				}	
			}
		}
		for (i = 0; i < G->U; i++) {
			RestartList (&individuals[i]->neighborhood);
			neighborhood (G, individuals, i, info, 0);
		}
	}

/* =================================================================================== */

/* =======================  Used for Reproduction  ========================== */

	/* This function, called by Reproduction, defines the offspring position, that is, if it is going to move, how much,
	and in which direction. It can move in it's focal parent range, with 1% chance*/
	void Offspring_Position (Population progenitors, Population offspring, int baby, int focal, Parameters info)
	{
		float movement_x, movement_y;

		movement_x = movement_y = 0;

		offspring[baby]->x = progenitors[focal]->x;
		offspring[baby]->y = progenitors[focal]->y;

		if (random_number() <= 0.01) {
			movement_y = random_number()*info->radius;
			movement_x = random_number()*info->radius;
			if (random_number() < 0.5) {
				movement_x = -movement_x;
				movement_y = -movement_y;
			}

			/* If an individual moves out of the lattice, it will reapear in the other side, because the lattice work as a toroid */
			if (offspring[baby]->x + movement_x <= info->lattice_width && progenitors[focal]->x + movement_x >= 0)
		  		offspring[baby]->x += movement_x;

			else if (progenitors[focal]->x + movement_x > info->lattice_width)
				offspring[baby]->x = offspring[baby]->x + movement_x - info->lattice_width;

			else if (progenitors[focal]->x + movement_x < 0)
				offspring[baby]->x = offspring[baby]->x + movement_x + info->lattice_width;

			if (progenitors[focal]->y + movement_y <= info->lattice_lenght && progenitors[focal]->y + movement_y >= 0)
		  	offspring[baby]->y = offspring[baby]->y + movement_y;

			else if (progenitors[focal]->y + movement_y > info->lattice_lenght)
				offspring[baby]->y = offspring[baby]->y + movement_y - info->lattice_lenght;

			else if (progenitors[focal]->y + movement_y < 0)
				offspring[baby]->y = offspring[baby]->y + movement_y + info->lattice_lenght;
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
	void Create_Offspring (Population progenitors, Population offspring, int baby, int focal, int mate, Parameters info)
	{
	  int i;
		
		Offspring_Position(progenitors, offspring, baby, focal, info);

		for (i = 0; i < info->genome_size; i++) {
			if (progenitors[focal]->genome[i] != progenitors[mate]->genome[i]) {
				if (rand_upto(1) == 1) {
					offspring[baby]->genome[i] = progenitors[mate]->genome[i];
				}
				else {
					offspring[baby]->genome[i] = progenitors[focal]->genome[i];
				}
			}
			else {
				offspring[baby]->genome[i] = progenitors[mate]->genome[i];
			}
		}

		for (i = 0; i < info->genome_size; i++) {
			if (random_number() <= 0.00025) {
				mutation (offspring, baby, i);
			}
		}
	}

	/* This function, called by Reproduction, chooses the mate of the focal individual (i) based on the graph
	(who it can reproduce with) and the distance of the others (who is in their range).*/
	int Choose_Mate (Graph G, int focal, Population progenitors, Parameters info)
	{
		int j, i, neighbors, expand, radius_increase, radius, mate;
		List p;
		List bigger_neighborhood;

		mate = -1;
		radius_increase = 0;

		bigger_neighborhood = CreateHeadedList ();

		while (radius_increase <= 3 && mate == -1) {
			if (radius_increase > 0) {
				expand_neighborhood (G, bigger_neighborhood, progenitors, focal, info, radius_increase);
			}

			neighbors = Verify_Neighborhood (progenitors[focal]->neighborhood);
			expand = Verify_Neighborhood (bigger_neighborhood);

			if (neighbors + expand) {
				i = rand_upto(neighbors + expand);
				
				if (i <= neighbors) {
					for (j = 0, p = progenitors[focal]->neighborhood->next; p != NULL && j < i; p = p->next, j++);
				}
				else {
					i -= neighbors;
					for (j = 0, p = bigger_neighborhood->next; p != NULL && j < i; p = p->next, j++);	
				}

				if (j == i && p != NULL) {
					mate = p->info;
				} 
				else mate = -1;
			}

			else mate = -1;
			if (mate == -1) {
				radius += 1;
				radius_increase += 1;
			}

		}
		DestroyList (&bigger_neighborhood);
		
		return mate;
	}

	/* This function, called by main, makes the reproduction happen, with creation of a new individual,
	who is to be put in a paralel lattice, where the next generation will be */ /* IS IT CONCEPTUALY OK? */
	void Reproduction (Graph G, Population progenitors, Population offspring, Parameters info)
	{ 	
		int focal, mate, other, i, n;

		i = 0;

		if (info->population_size < info->number_individuals) {
			for (focal = 0; focal < info->population_size; focal++) {
				if (Verify_Neighborhood (progenitors[focal]->neighborhood) < info->neighbors) {
					mate = Choose_Mate(G, focal, progenitors, info);
					if (mate != -1) {
						Create_Offspring (progenitors, offspring, i, focal, mate, info);
						i++;
						info->population_size ++;
					}
				}
			}
		} 

		for (focal = 0; focal < (G->U); focal++) {
			other = focal; 
			mate = -1;

			if (random_number() < 0.63 && Verify_Neighborhood (progenitors[focal]->neighborhood) > 2) {
				mate = Choose_Mate(G, focal, progenitors, info);
			}

			for (n = 0; n < 2; n++) {
				if (mate == -1) {
					other = Choose_Mate (G, focal, progenitors, info);
					if (other != -1)
						mate = Choose_Mate(G, other, progenitors, info);
				}
			}

			if (mate != -1 && other != -1) {
				Create_Offspring (progenitors, offspring, i, other, mate, info);
				i++;
			}
			else {
				info->population_size --;
			}
		}
		printf("pop size: %d\n", info->population_size);
	}

/* ========================================================================= */


/* =======================  Exchange Generations  ========================== */

	/*This function, called by main, Exchanges the generation's vector's pointers*/
	void Swap_Generations (Population* progenitors_pointer, Population* offspring_pointer)
	{
		Population helper;

		helper = (*progenitors_pointer);
		(*progenitors_pointer) = (*offspring_pointer);
		(*offspring_pointer) = helper;
	}

/* ============================================================================ */


/* =======================  Used for Counting species  ========================== */

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
	  int* parent;

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

	/* This function, called by main, calls DFS to count the number of maximal connected components in the graph */
	int Count_Species (Graph G, Population individuals)
	{
		int counter;

		DepthFirstSearch (G, &counter, individuals);

		return counter;
	}

/* ========================================================================== */

/* ============================== freeing =====================================*/

	void Free_Population (Population individuals, Parameters info)
	{
		int i;

		for (i = 0; i < info->individual_vector_size; i++) {
			if (individuals[i]->genome != NULL)
			free (individuals[i]->genome);
			DestroyList (&individuals[i]->neighborhood);
			free(individuals[i]);
	    }

	    free (individuals);
	}

/* ========================================================================== */