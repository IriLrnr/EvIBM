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

	/*Generates a random number between 0 and 1*/
	float random_number()
	{
		return ((float)rand()/RAND_MAX);
	}

	/*This is a binary genome generator. It generates the first genome.*/
	void Generate_Genome (int* first_genome, int genome_size)
	{
		int i;

		for (i = 0; i < genome_size; i++) {
			first_genome[i] = rand()%2;
		}
	}

	/* This function checks if an individual (j) is within the range of another individual (i) 
	PROBLEMATIC */
	int Verify_Distance (Population individualsk, int i, int j, Parameters info, int increase)
	{
		int x_compatible, y_compatible, x_out_left, x_out_right, y_out_up, y_out_down;

		y_compatible = 0;
		x_compatible = 0;

		x_out_left = 0;
		x_out_right = 0;
		y_out_up = 0;
		y_out_down = 0;

		/* If an individual ratio reaches an end of the lattice, it will look on the other side, because the lattice work as a toroid */
		if (individualsk[j]->x <= individualsk[i]->x + info->radius + increase && individualsk[j]->x >= individualsk[i]->x - info->radius + increase) {
			x_compatible = 1;
		}
		if (individualsk[j]->y <= individualsk[i]->y + info->radius + increase && individualsk[j]->y >= individualsk[i]->y - info->radius + increase) {
			y_compatible = 1;
		}

		if (!x_compatible) {
			if (individualsk[i]->x + info->radius + increase > info->lattice_width) {
				x_out_right = individualsk[i]->x + info->radius + increase - info->lattice_width;
				if (individualsk[j]->x <= x_out_right) {
					x_compatible = 1;
				}
			}
			else if (individualsk[i]->x - info->radius + increase < 0) {
				x_out_left = individualsk[i]->x - info->radius + increase + info->lattice_width;
				if (individualsk[j]->x >= x_out_left) {
					x_compatible = 1;
				}
			}
		}

		if (!y_compatible) {
			if (individualsk[i]->y + info->radius + increase > info->lattice_lenght) {
				y_out_up = individualsk[i]->y + info->radius + increase - info->lattice_lenght;
				if (individualsk[j]->y <= y_out_up) {
					y_compatible = 1;
				}
			}
			else if (individualsk[i]->y - info->radius + increase < 0) {
				y_out_down = individualsk[i]->y - info->radius + increase + info->lattice_lenght;
				if (individualsk[j]->y >= y_out_down) {
					y_compatible = 1;
				}
			}
		}

		if (x_compatible && y_compatible) return 1;
		else return 0;
	}

	int Verify_Neighborhood (Population individualsk, int i)
	{
		return (-(individualsk[i]->neighborhood->info + 1));
	}

	/* This function computes the neighbors an individual i can reproduce with and stores this info in a list */
	void neighborhood (Graph G, Population individualsk, int i, Parameters info, int increase)
	{
		int j;

		for (j = 0; j < (G->U); j++) {
			if (G->adj[i][j] != 0 && Verify_Distance (individualsk, i, j, info, increase)){
				AddCellInOrder(&individualsk[i]->neighborhood, j);
			}
		}
	}

/* ==================================================================== */


/* =======================  Used for Creating the graph  ========================== */

	/* This function, called by main, compares the genomes and creates a Graph, where vertix are individuals,
	arches means they can reproduce (similar genomes). The weight of the arch is the distance
	between genomes. */
	void Stablish_Distances (Graph G, Population individuals, Parameters info)
	{
		int i, j, k, divergences, size_difference;

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
					InsertArch (G, i, j, (info->genome_size - divergences));
				}
				else if (G->adj[i][j] != 0) {
					RemoveArch (G, i, j);
				}	
			}
		}
		for (i = 0; i < G->U; ++i)
		{
			DestroyList(&individuals[i]->neighborhood);
			individuals[i]->neighborhood = CreateHeadedList ();
			neighborhood (G, individuals, i, info, 0);
		}
	}

/* =================================================================================== */


/* =======================  Used for Reproduction  ========================== */

	/* This function, called by Reproduction, defines the offspring position, that is, if it is going to move, how much,
	and in which direction. It can move in it's focal parent range, with 1% chance*/
	void Offspring_Position (Population individualsk, Population individualsk1, int i, int k, Parameters info)
	{
		float movement_x, movement_y;

		movement_x = movement_y = 0;

		individualsk1[i]->x = individualsk[k]->x;
		individualsk1[i]->y = individualsk[k]->y;

		if (random_number() <= 0.01) {
			movement_y = random_number()*info->radius;
			movement_x = random_number()*info->radius;
			if (random_number() < 0.5) {
				movement_x = -movement_x;
				movement_y = -movement_y;
			}

			/* If an individual moves out of the lattice, it will reapear in the other side, because the lattice work as a toroid */
			if (individualsk1[i]->x + movement_x <= info->lattice_width && individualsk[k]->x + movement_x >= 0)
		  		individualsk1[i]->x += movement_x;

			else if (individualsk[k]->x + movement_x > info->lattice_width)
				individualsk1[i]->x = individualsk1[i]->x + movement_x - info->lattice_width;

			else if (individualsk[k]->x + movement_x < 0)
				individualsk1[i]->x = individualsk1[i]->x + movement_x + info->lattice_width;

			if (individualsk[k]->y + movement_y <= info->lattice_lenght && individualsk[k]->y + movement_y >= 0)
		  	individualsk1[i]->y = individualsk1[i]->y + movement_y;

			else if (individualsk[k]->y + movement_y > info->lattice_lenght)
				individualsk1[i]->y = individualsk1[i]->y + movement_y - info->lattice_lenght;

			else if (individualsk[k]->y + movement_y < 0)
				individualsk1[i]->y = individualsk1[i]->y + movement_y + info->lattice_lenght;
		}
		//printf("(%f, %f\n", individualsk1[i]->x, individualsk1[i]->y);
	}

	/* This function, called by Create_Offspring, allocates the mutation in the genome */
	void mutation (Population individualsk1, int i, int mutation)
	{
		if (individualsk1[i]->genome[mutation] == 1) {
			individualsk1[i]->genome[mutation] = 0;
		}
		else {
			individualsk1[i]->genome[mutation] = 1;
		}
	}

	/* This function, called by Reproduction, determines the characteristics of the offspring, based on the parent's.
	The new offspring will have the position of the focal individual (i). The genome of the offspring has, for
	each loci, 50% chance of coming from either of his parents */
	void Create_Offspring (Population individualsk, Population individualsk1, int i, int k, int j, Parameters info)
	{
	  int l;
		
		Offspring_Position(individualsk, individualsk1, i, k, info);

		for (l = 0; l < info->genome_size; l++) {
			if (individualsk[k]->genome[l] != individualsk[j]->genome[l]) {
				if (rand()%2 == 1) {
					individualsk1[i]->genome[l] = individualsk[j]->genome[l];
				}
				else {
					individualsk1[i]->genome[l] = individualsk[k]->genome[l];
				}
			}
			else {
				individualsk1[i]->genome[l] = individualsk[j]->genome[l];
			}
		}

		for (l = 0; l < info->genome_size; l++) {
			if (random_number() <= 0.00025) {
				mutation (individualsk1, i, l);
			}
		}
	}


	/* This function, called by Reproduction, chooses the mate of the focal individual (i) based on the graph
	(who it can reproduce with) and the distance of the others (who is in their range).*/
	int Choose_Mate (Graph G, int i, Population individualsk, Parameters info)
	{
		int j, l, neighbors, radius_increase, radius, mate;
		List p;

		mate = -1;
		radius_increase = 0;

		while (radius_increase <= 3 && mate == -1) {
			if (radius_increase > 0) {
				DestroyList(&individualsk[i]->neighborhood);
				individualsk[i]->neighborhood = CreateHeadedList ();
				neighborhood (G, individualsk, i, info, radius_increase);
			}
			neighbors = Verify_Neighborhood (individualsk, i);
			if (neighbors) {
				l = rand()%neighbors;
			}
			for (j = 0, p = individualsk[i]->neighborhood->next; p != NULL && j < l; p = p->next, j++);
			if (j == l) mate = p->info;
			else mate = -1;

			if (mate == -1) {
				radius += 1;
				radius_increase += 1;
			}
		}
		return mate;
	}

	/* This function, called by main, makes the reproduction happen, with creation of a new individual,
	who is to be put in a paralel lattice, where the next generation will be */
	void Reproduction (Graph G, Population individualsk, Population individualsk1, Parameters info)
	{ 	
		int i, j, k, l, n;

		l = 0;

		if (info->population_size < info->number_individuals) {
			for (i = 0; i < info->population_size; i++) {
				if (Verify_Neighborhood (individualsk, i) < info->neighbors) {
					j = Choose_Mate(G, i, individualsk, info);
					if (j != -1) {
						Create_Offspring (individualsk, individualsk1, l, i, j, info);
						l++;
						info->population_size ++;
					}
				}
			}
		}

		for (i = 0; i < (G->U); i++) {
			k = i;
			j = -1;

			if (random_number() <= 0.64 && Verify_Neighborhood (individualsk, i) >= info->neighbors) {
				j = Choose_Mate(G, i, individualsk, info);
			}

			for ( n = 0; n < 2; n++) {
				if (j == -1) {
					k = Choose_Mate (G, i, individualsk, info);
					if (k != -1)
						j = Choose_Mate(G, k, individualsk, info);
				}
			}

			if (j != -1 && k != -1) {
				Create_Offspring (individualsk, individualsk1, l, k, j, info);
				l++;
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
	void New_Generation_k (Population* individualsk_pointer, Population* individualsk1_pointer)
	{
		Population helper;

		helper = (*individualsk_pointer);
		(*individualsk_pointer) = (*individualsk1_pointer);
		(*individualsk1_pointer) = helper;
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