#include "../include/genome.h"

/* @ Compare_Genomes */
int Compare_Genomes (Population individuals, int i, int j, Parameters info)
{
	int divergences, min_divergences;
	List p, q;

	divergences = Verify_Head (&individuals[i]->genome) + Verify_Head (&individuals[j]->genome);
	min_divergences = abs (Verify_Head (&individuals[i]->genome) - Verify_Head (&individuals[j]->genome));
	if (min_divergences <= info->reproductive_distance) {
		for (p = individuals[i]->genome->next, q = individuals[j]->genome->next; (p != NULL && q != NULL) && divergences > info->reproductive_distance;) {
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
		return 1;
	}
	else {
		return 0;
	}	
}
/* @ end */

int Calculate_Genetic_Distance (Population individuals, int i, int j, Parameters info) 
{
 	int divergences;
	List p, q;

	divergences = Verify_Head (&individuals[i]->genome) + Verify_Head (&individuals[j]->genome);
	for (p = individuals[i]->genome->next, q = individuals[j]->genome->next; (p != NULL && q != NULL);) {
		if (p->info == q->info) {
			divergences -= 2;
			p = p->next;
			q = q->next;
		}
		else if (p->info < q->info) p = p->next;
		else q = q->next;
	}
	return divergences;
}

/* @ Mutation */
void Mutation (Population offspring, int baby, Parameters info)
{
	unsigned int quantity;
	int i;

	quantity = gsl_ran_binomial (GLOBAL_RNG, info->mutation, info->genome_size);
	
	if (quantity > 0) {
		for (i = 0; i < quantity; ++i) {
			AlterList (&(offspring[baby]->genome), rand_upto (info->genome_size - 1));
		}
	}
}
/* @ end */

/* @ Offspring_Genome */
void Offspring_Genome (Population progenitors, Population offspring, int baby, int other, int mate, Parameters info)
{
	int i;
	List p, q;

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
/* @ end */
