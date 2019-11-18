#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

/*This defines and individual as a struct with genome and location*/
typedef struct
{
	int* genome;
	float x;
	float y;
} individual;

typedef individual * Individual;

typedef Individual * Population;

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

/*Generates a random number between 0 and 1*/
float random_number()
{
	return ((float)rand()/RAND_MAX);
}

/*This function determines if other individual is within the range of the focal individual.*/
int Verify_Distance (Population individualsk, int i, int j, Parameters info)
{
	if (individualsk[j]->x <= (individualsk[i]->x + info->radius) && individualsk[j]->x >= (individualsk[i]->x - info->radius)) {
		if (individualsk[j]->y <= individualsk[i]->y + info->radius && individualsk[j]->y >= individualsk[i]->y - info->radius) {
			return 1;
		}
	}
	return 0;
}

/*This is a binary genome generator. It generates the first genome.*/
void Generate_Genome (int* first_genome, int genome_size)
{
	int i;

	for (i = 0; i < genome_size; i++) {
		first_genome[i] = rand()%2;
	}
}

/* Calculates the number of neigbors an individual i can reproduce with */
int neighborhood (Graph G, Population individualsk, int i, Parameters info)
{
	int neighbors, j;

	neighbors = 0;

	for (j = 0; j < (G->U); j++) {
		if (G->adj[i][j] != 0 && Verify_Distance (individualsk, i, j, info))
			neighbors++;
	}

	return neighbors;
}

/*This function compares the genomes and creates a Graph, where vertix are individuals,
arches means they can reproduce (similar genomes). The weight of the arch is the distance
between genomes. Currently very inneficient*/
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
}

/*This function defines the offspring position, that is, if it is going to move, how much, and in which direction.
It can move in it's focal parent range, with 1% chance*/
void Offspring_Position (Population individualsk, Population individualsk1, int i, int k, Parameters info)
{
	float movement_x, movement_y;

	movement_x = movement_y = 0;

	if (random_number() <= 0.01) {
			movement_y = random_number()*info->radius;
			movement_x = random_number()*info->radius;
			if (random_number() < 0.5) {
				movement_x = -movement_x;
			}
			if (random_number() < 0.5) {
				movement_y = -movement_x;
			}
	}

  individualsk1[i]->x = individualsk[k]->x + movement_x;
  individualsk1[i]->y = individualsk[k]->y + movement_y;
}

/*This function, called by Create_Offspring, allocates the mutation in the genome */
void mutation (Population individualsk1, int i, int mutation)
{
	if (individualsk1[i]->genome[mutation] == 1) {
		individualsk1[i]->genome[mutation] = 0;
	}
	else {
		individualsk1[i]->genome[mutation] = 1;
	}
}

/*This function determines the characteristics of the offspring, based on the parent's.
The new offspring will have the position of the focal individual (i).*/
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


/*This function chooses the mate of the focal individual (i) based on the graph
(who it can reproduce with) and the distance of the others (who is in their range).*/
int Choose_Mate (Graph G, int i, Population individualsk, Parameters info)
{
	int j, l, radius_increase, radius, mate;

	mate = -1;
	radius_increase = 0;

	while (radius_increase <= 3 && mate == -1) {
		for (l = 0; l < (G->U); l++) {
			j = rand()%(G->U);
			if (i != j && G->adj[i][j] > 0 && Verify_Distance (individualsk, i, j, info)) {
				mate = j;
				break;
			}
		}
		if (mate == -1) {
			radius += 1;
			radius_increase += 1;
		}
	}
	return mate;
}

/* Chooses a neighbor of the same species as i */
int Choose_Neighbor (Graph G, Population individualsk, int i, Parameters info)
{
	int j, k;

	k = -1;
	for (j = 0; j < (G->U); j++) {
		if (G->adj[i][j] && Verify_Distance (individualsk, i, j, info)) {
			k = j;
			break;
		}
	}

	return k;
}
/*k should be randomly choosen. How do I do that? */

/*This function makes the reproduction happen, with creation of a new individual,
who is to be put in a paralel lattice, where the next generation will be*/
/*PROBLEMATIC*/
void Reproduction (Graph G, Population individualsk, Population individualsk1, Parameters info)
{
	int i, j, k, l, n;

	l = 0;

	if (info->population_size < info->number_individuals) {
		for (i = 0; i < info->population_size; i++) {
			if (neighborhood (G, individualsk, i, info) < info->neighbors) {
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

		if (random_number() <= 0.64 && neighborhood (G, individualsk, i, info) < 3) {
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

}

/*Exchanges the generation's vector's pointers*/
void New_Generation_k (Population* individualsk_pointer, Population* individualsk1_pointer)
{
	Population helper;

	helper = (*individualsk_pointer);
	(*individualsk_pointer) = (*individualsk1_pointer);
	(*individualsk1_pointer) = helper;
}

/* Calls DFS to count the number of connected components in the graph */
int Count_Species (Graph G)
{
	int counter;

	DepthFirstSearch (G, &counter);

	return counter;
}
