#include "../include/data.h"

void Write_Data (FILE ** nspecies, FILE ** size, FILE ** position, int sizes[], int number_species, int i, int l, Population progenitors, Parameters info) 
{
  int j;

  if (i % 25 == 0) {
      //if (info->genome < 15000) FindSpecies (progenitors, info);
      printf(" %d \t %d \t  %d \t %d\n", l, i, number_species, info->population_size);
  }

  if (l == 1 && i % 100 == 0) {
    for (j = 0; j < info->population_size; j++) {
      fprintf(*position, "%d;%d;%f;%f;%d;%d\n", l, j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, i); 
    }
  }

  fprintf (*nspecies, "%d;%d;%d;%d\n", i, number_species, info->population_size, l);
  if (i % 20 == 0) {  
    for (j = 0; j < number_species; ++j) {
      fprintf (*size, "%d;%d;%d;%d;%d\n", l, i, j, sizes[j], info->population_size);
    }
  } 
}

void Open_Files (FILE ** nspecies, FILE ** size, FILE ** distances, FILE ** position, Parameters info, int l)
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
  fputs ("sim;gen;i;j;spp;d\n", *distances);

  sprintf (nome_arq, "./data/sizes_tests/%.f/%.f/position/indloc_%02d.csv", info->radius, info->lattice_length, l);
  *position = fopen (nome_arq, "w");  
  fputs ("sim;i;x;y;sp;gen\n", *position);
}

void Close_Files (FILE ** nspecies, FILE ** size, FILE ** distances, FILE ** position)
{
  fclose (*nspecies);
  fclose (*size);
  fclose (*distances);
  fclose (*position);
}

/*void Write_Distance_Data (FILE ** distances, Population progenitors, int i, int l, Parameters info)
{
  int j, k;

  if (i == 180 || i == 1000) {
    for (j = 0; j < info->population_size; j++) {
      fprintf(*distances, "%d;%d;%d;%d;%f\n", l, i, j, Calculate_Genetic_Distance (progenitors, 0, j, info), Calculate_Spatial_Distance (progenitors, 0, j, info));
    }
  }
}*/

void Write_Distance_Data (FILE ** distances, Population progenitors, int gen, int sim, Parameters info)
{
  int j, k, d, spp;
  double d_dist;

  if (gen == 180 || gen == 1000) {
    for (j = 0; j < info->population_size; j++) {
      d = 0;
      d_dist = 0;
      spp = Find (progenitors, j);
      for (k = 0; k < info->population_size; k++) {
        if (k != j) {
          if (Find (progenitors, k) == spp) {
            if (Calculate_Spatial_Distance (progenitors, j, k, info) > d_dist) {
              d = k;
              d_dist = Calculate_Spatial_Distance (progenitors, j, k, info);
            }  
          }
        }
      }
      fprintf(*distances, "%d;%d;%d;%d;%d;%f\n", sim, gen, j, d, spp, d_dist);
    }
  }
}  