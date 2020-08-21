/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structures used */
#define Vertix int

typedef struct {
  int V;
  int U;
  int A;
  int **adj;
} graph;

typedef graph * Graph;

/* Functions from graph.h */
int** AlocateMatrix (int, int, int);
Graph CreateGraph (int, int);
void InsertArc (Graph, Vertix, Vertix, int);
void RemoveArc (Graph, Vertix, Vertix);
void PrintGraph (Graph);
void DestroyGraph (Graph);
