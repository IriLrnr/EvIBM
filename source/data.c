#include "data.h"

void Write_Data (FILE ** nspecies, FILE ** size, FILE** distances, FILE ** status, int sizes[], int number_species, int i, int l, Population progenitors, Parameters info) 
{
  int j;
  char g[1500];

  if (i > 0)Reopen_Files (nspecies, size, distances, status, info, l);

  for (j = 0; j < info->population_size; j++) {
    sprintf(g, " ");
    PrintGenome(progenitors, j, g);
    fprintf(*status, "%d;%d;%f;%f;%d;%s;%d\n", l, j, progenitors[j]->x, progenitors[j]->y, progenitors[j]->species, g, i); 
  }

  fprintf (*nspecies, "%d;%d;%d;%d\n", i, number_species, info->population_size, l);
  for (j = 0; j < number_species; ++j) {
    fprintf (*size, "%d;%d;%d;%d;%d\n", l, i, j, sizes[j], info->population_size);
  }
  Write_Distance_Data (distances, progenitors, i, l, info);

  Close_Files (nspecies, size, distances, status); 
}

void Open_Files (FILE ** nspecies, FILE ** size, FILE ** distances, FILE ** status, Parameters info, int l)
{
  char nome_arq[100] = "";

  sprintf (nome_arq, "./data/article/%.f/%.f/species/numsp_%02d.csv", info->radius, info->lattice_length, l);
  *nspecies = fopen (nome_arq, "w");
  fputs ("gen;sp;pop;sim\n", *nspecies);

  sprintf (nome_arq, "./data/article/%.f/%.f/sizes/sizes_%02d.csv", info->radius, info->lattice_length, l);
  *size = fopen (nome_arq, "w");
  fputs ("sim;gen;sp;size;pop\n", *size);

  sprintf (nome_arq, "./data/article/%.f/%.f/distances/distances_%02d.csv", info->radius, info->lattice_length, l);
  *distances = fopen (nome_arq, "w");  
  fputs ("sim;gen;i;j;spp;d\n", *distances);

  sprintf (nome_arq, "./data/article/%.f/%.f/status/status_%02d.csv", info->radius, info->lattice_length, l);
  *status = fopen (nome_arq, "w");  
  fputs ("sim;i;x;y;sp;genome;gen\n", *status);
}

void Reopen_Files (FILE ** nspecies, FILE ** size, FILE ** distances, FILE ** status, Parameters info, int l)
{
  char nome_arq[100] = "";

  sprintf (nome_arq, "./data/article/%.f/%.f/species/numsp_%02d.csv", info->radius, info->lattice_length, l);
  *nspecies = fopen (nome_arq, "a");

  sprintf (nome_arq, "./data/article/%.f/%.f/sizes/sizes_%02d.csv", info->radius, info->lattice_length, l);
  *size = fopen (nome_arq, "a");

  sprintf (nome_arq, "./data/article/%.f/%.f/distances/distances_%02d.csv", info->radius, info->lattice_length, l);
  *distances = fopen (nome_arq, "a");  

  sprintf (nome_arq, "./data/article/%.f/%.f/status/status_%02d.csv", info->radius, info->lattice_length, l);
  *status = fopen (nome_arq, "w");  
  fputs ("sim;i;x;y;sp;genome;gen\n", *status);
}

void Close_Files (FILE ** nspecies, FILE ** size, FILE ** distances, FILE ** status)
{
  fclose (*nspecies);
  fclose (*size);
  fclose (*distances);
  fclose (*status);
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
