#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "linkedlist.h"

/* =======================  Definitions ========================== */

	/* Here we define and individual as a struct with genome, species, location and a list of neighbors. A
	population is as a vector of individuals */
	
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

/* The only problem here may be Verify_Distance. I need to check it */
/* =======================  Used everywhere  ========================== */

	/*Generates a random number between 0 and 1 */ /* TESTED OK */
	float random_number()
	{
		return ((float)rand()/RAND_MAX);
	}

	/*This is a binary genome generator. It generates the first genome.*/ /* TESTED OK */
	void Generate_Genome (int* first_genome, int genome_size)
	{
		int i;

		for (i = 0; i < genome_size; i++) {
			first_genome[i] = rand()%2;
		}
	}

	/* ** This function checks if an individual (j) is within the range of another individual */
	int Verify_Distance (Population individualsk, int focal, int mate, Parameters info, int increase)
	{
		int x_compatible, y_compatible, x_out_left, x_out_right, y_out_up, y_out_down;

		y_compatible = 0;
		x_compatible = 0;

		x_out_left = 0;
		x_out_right = 0;
		y_out_up = 0;
		y_out_down = 0;

		/* If an individual ratio reaches an end of the lattice, it will look on the other side, because the lattice work as a toroid */
		if (individualsk[mate]->x <= individualsk[focal]->x + info->radius + increase && individualsk[mate]->x >= individualsk[focal]->x - info->radius + increase) {
			x_compatible = 1;
		}
		if (individualsk[mate]->y <= individualsk[focal]->y + info->radius + increase && individualsk[mate]->y >= individualsk[focal]->y - info->radius + increase) {
			y_compatible = 1;
		}

		if (!x_compatible) {
			if (individualsk[focal]->x + info->radius + increase > info->lattice_width) {
				x_out_right = individualsk[focal]->x + info->radius + increase - info->lattice_width;
				if (individualsk[mate]->x <= x_out_right) {
					x_compatible = 1;
				}
			}
			else if (individualsk[focal]->x - info->radius + increase < 0) {
				x_out_left = individualsk[focal]->x - info->radius + increase + info->lattice_width;
				if (individualsk[mate]->x >= x_out_left) {
					x_compatible = 1;
				}
			}
		}

		if (!y_compatible) {
			if (individualsk[focal]->y + info->radius + increase > info->lattice_lenght) {
				y_out_up = individualsk[focal]->y + info->radius + increase - info->lattice_lenght;
				if (individualsk[mate]->y <= y_out_up) {
					y_compatible = 1;
				}
			}
			else if (individualsk[focal]->y - info->radius + increase < 0) {
				y_out_down = individualsk[focal]->y - info->radius + increase + info->lattice_lenght;
				if (individualsk[mate]->y >= y_out_down) {
					y_compatible = 1;
				}
			}
		}

		if (x_compatible && y_compatible) return 1;
		else return 0;
	}

	/* ok because the head always going to have the smallest value */
	int Verify_Neighborhood (Population individualsk, int focal)
	{
		return (-(individualsk[focal]->neighborhood->info + 1));
	}

	/*  This function computes the neighbors an individual can reproduce with and stores this info in a list */
	void neighborhood (Graph G, Population individualsk, int focal, Parameters info, int increase)
	{
		int mate;

		for (mate = 0; mate < (G->U); mate++) {
			if (G->adj[focal][mate] != 0 && Verify_Distance (individualsk, focal, mate, info, increase)){
				AddCellInOrder(&individualsk[focal]->neighborhood, mate);
			}
		}
	}

/* ==================================================================== */

/* This function is not ideal, but is not the problem either */
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
					InsertArc (G, i, j, (info->genome_size - divergences));
				}
				else if (G->adj[i][j] != 0) {
					RemoveArc (G, i, j);
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

/* THE PROBLEM IS HERE. I DON'T KNOW EXACLY WHERE, IF IT IS CONCEPTUAL OR A MODELING PROBLEM */
/* =======================  Used for Reproduction  ========================== */

	/* This function, called by Reproduction, defines the offspring position, that is, if it is going to move, how much,
	and in which direction. It can move in it's focal parent range, with 1% chance*/
	void Offspring_Position (Population individualsk, Population individualsk1, int baby, int focal, Parameters info)
	{
		float movement_x, movement_y;

		movement_x = movement_y = 0;

		individualsk1[baby]->x = individualsk[focal]->x;
		individualsk1[baby]->y = individualsk[focal]->y;

		if (random_number() <= 0.01) {
			movement_y = random_number()*info->radius;
			movement_x = random_number()*info->radius;
			if (random_number() < 0.5) {
				movement_x = -movement_x;
				movement_y = -movement_y;
			}

			/* If an individual moves out of the lattice, it will reapear in the other side, because the lattice work as a toroid */
			if (individualsk[focal]->x + movement_x <= info->lattice_width && individualsk[focal]->x + movement_x >= 0)
		  		individualsk1[baby]->x += movement_x;

			else if (individualsk[focal]->x + movement_x > info->lattice_width)
				individualsk1[baby]->x = individualsk1[baby]->x + movement_x - info->lattice_width;

			else if (individualsk[focal]->x + movement_x < 0)
				individualsk1[baby]->x = individualsk1[baby]->x + movement_x + info->lattice_width;

			if (individualsk[focal]->y + movement_y <= info->lattice_lenght && individualsk[focal]->y + movement_y >= 0)
		  	individualsk1[baby]->y = individualsk1[baby]->y + movement_y;

			else if (individualsk[focal]->y + movement_y > info->lattice_lenght)
				individualsk1[baby]->y = individualsk1[baby]->y + movement_y - info->lattice_lenght;

			else if (individualsk[focal]->y + movement_y < 0)
				individualsk1[baby]->y = individualsk1[baby]->y + movement_y + info->lattice_lenght;
		}
	}

	/* This function, called by Create_Offspring, allocates the mutation in the genome */
	void mutation (Population individualsk1, int baby, int mutation)
	{
		if (individualsk1[baby]->genome[mutation] == 1) {
			individualsk1[baby]->genome[mutation] = 0;
		}
		else {
			individualsk1[baby]->genome[mutation] = 1;
		}
	}

	/* This function, called by Reproduction, determines the characteristics of the offspring, based on the parent's.
	The new offspring will have the position of the focal individual (i). The genome of the offspring has, for
	each loci, 50% chance of coming from either of his parents */
	void Create_Offspring (Population individualsk, Population individualsk1, int baby, int focal, int mate, Parameters info)
	{
	  int i;
		
		Offspring_Position(individualsk, individualsk1, baby, focal, info);

		for (i = 0; i < info->genome_size; i++) {
			if (individualsk[focal]->genome[i] != individualsk[mate]->genome[i]) {
				if (rand()%2 == 1) {
					individualsk1[baby]->genome[i] = individualsk[mate]->genome[i];
				}
				else {
					individualsk1[baby]->genome[i] = individualsk[focal]->genome[i];
				}
			}
			else {
				individualsk1[baby]->genome[i] = individualsk[mate]->genome[i];
			}
		}

		for (i = 0; i < info->genome_size; i++) {
			if (random_number() <= 0.00025) {
				mutation (individualsk1, baby, i);
			}
		}
	}

	/* This function, called by Reproduction, chooses the mate of the focal individual (i) based on the graph
	(who it can reproduce with) and the distance of the others (who is in their range).*/
	int Choose_Mate (Graph G, int focal, Population individualsk, Parameters info)
	{
		int j, i, neighbors, radius_increase, radius, mate;
		List p;

		mate = -1;
		radius_increase = 0;

		while (radius_increase <= 3 && mate == -1) {
			if (radius_increase > 0) {
				DestroyList(&individualsk[focal]->neighborhood);
				individualsk[focal]->neighborhood = CreateHeadedList ();
				neighborhood (G, individualsk, focal, info, radius_increase);
			}

			neighbors = Verify_Neighborhood (individualsk, focal);

			if (neighbors) {
				i = rand()%neighbors;
			}

			for (j = 0, p = individualsk[focal]->neighborhood->next; 
				p != NULL && j < i; p = p->next, j++);
			if (j == i && p != NULL) mate = p->info;
			else mate = -1;
			if (mate == -1) {
				radius += 1;
				radius_increase += 1;
			}
		}
		return mate;
	}

	/* This function, called by main, makes the reproduction happen, with creation of a new individual,
	who is to be put in a paralel lattice, where the next generation will be */ /* IS IT CONCEPTUALY OK? */
	void Reproduction (Graph G, Population individualsk, Population individualsk1, Parameters info)
	{ 	
		int focal, mate, other, i, n;
		float rn;

		i = 0;

		if (info->population_size < info->number_individuals) {
			for (focal = 0; focal < info->population_size; focal++) {
				if (Verify_Neighborhood (individualsk, focal) < info->neighbors) {
					mate = Choose_Mate(G, focal, individualsk, info);
					if (mate != -1) {
						Create_Offspring (individualsk, individualsk1, i, focal, mate, info);
						i++;
						info->population_size ++;
					}
				}
			}
		} 

		for (focal = 0; focal < (G->U); focal++) {
			other = focal; 
			mate = -1;
			if (random_number() <= 0.63 && Verify_Neighborhood (individualsk, focal) >= 2) {
				mate = Choose_Mate (G, focal, individualsk, info);
			}

			for (n = 0; n < 2; n++) {
				if (mate == -1) {
					other = Choose_Mate (G, focal, individualsk, info);
					if (other != -1)
						mate = Choose_Mate (G, other, individualsk, info);
				}
			}

			if (mate != -1) {
				Create_Offspring (individualsk, individualsk1, i, other, mate, info);
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