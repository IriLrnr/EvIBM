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
void AddCell (List*, int);
void AddCellInOrder (List*, int);
void RemoveCell (List*, int);
List FindValue (int, List*);
void PrintList (List);
void AlterList (List*, int);
void DestroyList (List*);
void RestartList (List*);
int Verify_Head (List*);
