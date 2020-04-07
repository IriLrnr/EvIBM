/* Libraries */
#include <stdio.h>
#include <stdlib.h>

/* Structures used */
typedef struct cell {
  int info;
  struct cell* next;
} Cell;
typedef Cell* List;

/* functions from linkedlist.h */

List CreateHeadedList ();
void AddCellInOrder (List*, int);
void RemoveCell (List*, int);
List FindValue (int, List*);
void PrintList (List);
void AlterList (int, List*);
void DestroyList (List*);
void RestartList (List*);
