#include "genome.h"

void Stablish_Distances (Graph G, Population individuals, Parameters info)
{
	int i, j, k, divergences, i_divergences, j_divergences;
	List p, q;

	G->U = info->population_size;

	for (i = 0; i < G->U; i++) {
		for (j = i + 1; j < G->U; j++) {
			divergences = Verify_Head (&individuals[i]->genome) + Verify_Head (&individuals[j]->genome);
			min_divergences = abs (Verify_Head (&individuals[i]->genome) - Verify_Head (&individuals[j]->genome));
			if (min_divergences <= info->reproductive_distance) {
				if (divergences > info->reproductive_distance) {
					for (p = individuals[i]->genome->next, q = individuals[j]->genome->next; p != NULL && q != NULL;) {
						if (p->info == q->info) {
							divergences -= 2;
							p = p->next;
							q = q->next;
						}
						else if (p->info < q->info) p = p->next;
						else q = q->next;
					}
				}

				if (divergences <= info->reproductive_distance) {
					if (G->adj[i][j] == 0) InsertArc (G, i, j, 1);
				}
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

void Mutation (Population offspring, int baby, Parameters info)
{
	unsigned int quantity;

	quantity = gsl_ran_binomial (GLOBAL_RNG, info->mutation, info->genome_size);

	if (quantity > 0) {
		AlterList (&(offspring[baby]->genome), rand_uptp (info->genome_size - 1));
	}
}

void Create_Offspring (Population progenitors, Population offspring, int baby, int focal, int other, int mate, Parameters info)
{
int i;
List p, q;

Offspring_Position (progenitors, offspring, baby, focal, info);

RestartList (&offspring[baby]->genome);

for (p = progenitors[other]->genome->next, q = progenitors[mate]->genome->next; p != NULL || q != NULL;) {
	if (p == NULL) {
		for (q; q != NULL; q = q->next) {
			if (rand()%2 == 1) AlterList (&offspring[baby]->genome, q->info);
		}
	}
	else if (q == NULL) {
		for (p; p != NULL; p = p->next) {
			if (rand()%2 == 1) AlterList (&offspring[baby]->genome, p->info);
		}
	}
	else {
		if (p->info < q->info) {
			if (rand()%2 == 1) AlterList (&(offspring[baby]->genome), p->info);
			p = p->next;
		}
		else if (p->info > q->info) {
			if (rand()%2 == 1) AlterList (&(offspring[baby]->genome), q->info);
			q = q->next;
		}
		else {
			AlterList (&(offspring[baby]->genome), q->info);
			p = p->next;
			q = q->next;
		}
	}
}

Mutation (offspring, baby, info);
}

int Count_Species (Graph G, Population individuals)
{
	int counter;

	DepthFirstSearch (G, &counter, individuals);

	return counter;
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
