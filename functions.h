#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"

/*This defines and individual as a struct with genome, location*/
typedef struct
{
	int* genome;
	float x;
	float y;
} individual;

typedef individual * Population;

/*For now the size of the genome, for it is fixed, is a global.*/

int colliding (Population individualsk, int i, int number_individuals)
{
	int j;

	for (j = 0; j < number_individuals; j++) {
		if (i != j &&
				individualsk[j].x == individualsk[i].x &&
				individualsk[j].y == individualsk[i].y)
				return 1;
	}
	return 0;
}

float random_number()
{
	return ((float)rand()/RAND_MAX);
}

/*This is a RANDOM binary genome generator. It generates the first genome. It needs a better random number generator*/
void Generate_Genome (int* first_genome, int genome_size)
{
  int i;

  for (i = 0; i < genome_size; i++) {
    first_genome[i] = rand()%2;
  }
}


/*This function compares the genomes and creates a Graph, where vertix are individuals, arches means they can reproduce (similar genomes). The weight of the arch is the distance between genomes. I think it could be faster.
Notice: G->V = number_individuals*/
void Stablish_Distances (Graph G, Population individuals, int genome_size, int reproductive_distance)
{
  int i, j, k, divergences;

	for (i = 0; i < (G->V); i++) {
		for (j = i + 1; j < (G->V); j++) {

      divergences = 0;
      for (k = 0; k < genome_size; k++) {
        if (individuals[i].genome[k] != individuals[j].genome[k]) {
           divergences++;
         }
      }

      if (divergences <= reproductive_distance) {
        InsertArch (G, i, j, (genome_size - divergences));
      }
			else
				RemoveArch (G, i, j);
    }
  }
  /*PrintGraph(G);*/
}

/*This function defines the offspring position, that is, if it is going to move, how much, and in which direction*/
void Offspring_Position (Population individualsk, Population individualsk1, int i, int j, float radius)
{
	float movement_x, movement_y;

	movement_x = movement_y = 0;

	if (random_number() <= 0.45) {
			movement_x = random_number()*radius;
			if (random_number() < 0.5) {
				movement_x = -movement_x;
			}
	}

	if (random_number() <= 0.45) {
			movement_y = random_number()*radius;
			if (random_number() < 0.5) {
				movement_y = -movement_x;
			}
	}

  individualsk1[i].x= individualsk[i].x + movement_x;
  individualsk1[i].y = individualsk[i].y  + movement_y;
	/*printf("x, y antes: (%f, %f), x, y depois: (%f, %f)\n", individualsk[i].x, individualsk[i].y, individualsk1[i].x, individualsk1[i].y);*/
}

/*This function, called by Create Create_Offspring, allocates the mutation in the genome */
void mutation (Population individualsk1, int i, int mutation)
{
	if (individualsk1[i].genome[mutation] == 1) {
		individualsk1[i].genome[mutation] = 0;
	}
	else {
		individualsk1[i].genome[mutation] = 1;
	}
}

/*This function determines the characteristics of the offspring, based on the parent's. The new offspring will have the position of the focal individual (i), for now*/
void Create_Offspring (Population individualsk, Population individualsk1, int i, int j, int genome_size, float radius)
{
  int l;
	float rn;

	Offspring_Position(individualsk, individualsk1, i, j, radius);

  for (l = 0; l < genome_size; l++) {
    if (rand()/2 < 5) {
      individualsk1[i].genome[l] = individualsk[i].genome[l];
    }
    else {
      individualsk1[i].genome[l] = individualsk[j].genome[l];
    }
		if (random_number() <= 0.00025) {
			mutation(individualsk1, i, l);
		}
  }
}


/*This function determines if other individuals are within the range of the focal individual.*/
int Verify_Distance (Population individualsk, int i, int j, float radius)
{
	if (individualsk[j].x <= (individualsk[i].x + radius) && individualsk[j].x >= (individualsk[i].x - radius)) {
		if (individualsk[j].y <= individualsk[i].y + radius && individualsk[j].y >= individualsk[i].y - radius) {
			return 1;
		}
	}
	return 0;
}

/*This function chooses the mate of the focal individual (i) based on the graph (who it can reproduce with) and the distance of the others (who is in their range).
HERE THERE IS A POSSIBLE LOOP. HAVE TO BE FIXED
*/
int Choose_Mate (Graph G, int i, Population individualsk, float radius)
{
	int j, l, radius_increase, mate;
	int *tested = calloc ((G->V), sizeof (int));

	mate = -1;
	radius_increase = 0;

	while (radius_increase <= 3 && mate == -1) {
		for (l = 0; l < (G->V); l++) {
			j = rand()%(G->V);
			if (i != j && G->adj[i][j] > 0 && Verify_Distance(individualsk, i, j, radius)) {
				mate = j;
				break;
			}
		}
		if (mate == -1) {
			radius += 1;
			radius_increase += 1;
		}
	}
	free (tested);
	return mate;
}


/*This function makes the reproduction happen, with creation of a new individual, who is to be put in a paralel lattice, where the next generation will be*/
void Reproduction (Graph G, Population individualsk, Population individualsk1, float radius, int genome_size)
{
	int i, j, k;

	for (i = 0; i < (G->V); i++) {
		k = i;
		j = -1;  /*N TIRA*/
		while (j == -1) {
			j = Choose_Mate(G, k, individualsk, radius);
		 	if (j == -1){
				k = rand()%(G->V);
			}
			/*printf("loopsy\n");*/
		}
    Create_Offspring (individualsk, individualsk1, k, j, genome_size, radius);
	}
}

void New_Generation_k (Population* individualsk_pointer, Population* individualsk1_pointer)
{
	Population helper;

	helper = (*individualsk_pointer);
	(*individualsk_pointer) = (*individualsk1_pointer);
	(*individualsk1_pointer) = helper;
}

int Count_Species (Graph G)
{
	int counter;

	DepthFirstSearch (G, &counter);

	return counter;
}

/*
Problema em dar free nos genomas dos individuos -- e nos vetores de individuos.

loop na função de encontrar o parceiro -- O que fazer se eu não encontrar? AINDA NÃO SEI E ISSO TA FODENDO

Será que devo compartimentalizar mais?

Precisamos de números aleatórios com precisão de 10^(-8);

Possíveis problemas (espécies de mais):
	- Numero aleatório
	- Contador de espécies - CORRIGIDO, ERA ERRO
	- Reprodução e escolha de parceiro
	- testar com o dfs da iGraph (biblioteca para C)

População pode flutuar em torno de 1000. Como diminuir? Como aumentar?

SUGESTÂO:
- Distribuição aleatória de N numeros diferentes com criptografia

*/
