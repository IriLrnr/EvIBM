#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
  int info;
  struct cell* next;
} Cell;
typedef Cell* List;

/* Creates a headed list, where the head holds a value, wich is -(size of the list + 1) */
List CreateHeadedList ()
{
  List p;
  p = malloc (sizeof (Cell));
  p->info = -1;
  return p;
}

/* This function add a cell to the list, if and only if it is not on the list already, and in order
it also updates the size of the list */
void AddCellInOrder (List *list, int value)
{
  List new, p;

  new = malloc (sizeof (Cell));
  new->info = value;

  if (*list == NULL) {
    new->next = NULL;
    *list = new;
  }

  else {
    if (value < (*list)->info) {
      p = (*list);
      (*list) = new;
      (*list)->next = p;
    }
    else {
      for (p = *list; p->next != NULL && (p->next)->info < value; p = p->next);
      if (p->next == NULL) {
        new->next = NULL;
        p->next = new;
        (*list)->info --;
      }
      if ((p->next)->info > value) {
        new->next = p->next;
        p->next = new;
        (*list)->info --;
      }
    }
  }
}

/* This function removes a cell with a certain value from the list, and updates the list size */
void RemoveCell (List *list, int value)
{
  List p, discard;

  if ((*list)->info == value) {
    discard = (*list);
    (*list) = (*list)->next;
  }
  else {
    for (p = *list; p->next != NULL && (p->next)->info < value; p = p->next);
    if ((p->next) != NULL) {
      if ((p->next)->info == value) {
        discard = p->next;
        p->next = discard->next;
        (*list)->info ++;
      }
    }
  }
  free (discard);
}

List FindValue (int value, List *list)
{
  List p;

  for (p = *list; p != NULL && p->info < value; p = p->next);
  if (p->info == value) return p;
  else return NULL;
}

void PrintList (List cell)
{
  if (cell) {
    printf ("%d -> ", cell->info);
    PrintList (cell->next);
  }
  else
  printf(".\n");
}

void AlterList (int value, List *list)
{
  if (FindValue (value, list) == NULL) {
    AddCellInOrder (list, value);
  }
  else {
    RemoveCell (list, value);
  }
}

void DestroyList (List *list)
{
  List p, discard;

  if (*list != NULL) {
    for (p = *list; p->next != NULL;) {
      discard = p;
      p = p->next;
      free (discard);
    }
    if (p != NULL)
    free (p);
  }
}
