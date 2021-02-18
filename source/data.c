#include "../include/data.h"

void Write_Data (FILE ** nspecies, FILE ** size, FILE ** distances, int sizes[], int number_species, int i, int l, Population progenitors, Parameters info) 
{
  int j;

  if (i % 1 == 0) {
      //if (info->genome < 15000) FindSpecies (progenitors, info);
      printf(" %d \t %d \t  %d \t %d\n", l, i, number_species, info->population_size);
  }

  fprintf (*nspecies, "%d;%d;%d;%d\n", i, number_species, info->population_size, l);
  if (i % 20 == 0) {  
    for (j = 0; j < number_species; ++j) {
      fprintf (*size, "%d;%d;%d;%d;%d\n", l, i, j, sizes[j], info->population_size);
    }
  } 
}

void Open_Files (FILE ** nspecies, FILE ** size, FILE ** distances, Parameters info, int l)
{
  char nome_arq[100] = "";

  sprintf (nome_arq, "./data/sizes_tests/%.f/%.f/species/numsp_%02d.csv", info->radius, info->lattice_length, l);
  *nspecies = fopen (nome_arq, "w");
  fputs ("gen;sp;pop;sim\n", *nspecies);

  sprintf (nome_arq, "./data/sizes_tests/%.f/%.f/sizes/sizes_%02d.csv", info->radius, info->lattice_length, l);
  *size = fopen (nome_arq, "w");
  fputs ("sim;gen;sp;size;pop\n", *size);

  sprintf (nome_arq, "./data/sizes_tests/%.f/%.f/distances/distances_%02d.csv", info->radius, info->lattice_length, l);
  *distances = fopen (nome_arq, "w");  
  fputs ("sim;i;dg;ds\n", *distances);
}

void Close_Files (FILE ** nspecies, FILE ** size, FILE ** distances)
{
  fclose (*nspecies);
  fclose (*size);
  fclose (*distances);
}

void Write_Distance_Data (FILE ** distances, Population progenitors, int i, int l, Parameters info)
{
  int j, k;

  if (i == info->number_generations - 1) {
    for (j = 0; j < info->population_size; j++) {
      fprintf(*distances, "%d;%d;%d;%f\n", l, j, Calculate_Genetic_Distance (progenitors, 0, j, info), Calculate_Spatial_Distance (progenitors, 0, j, info));
    }
  }
}