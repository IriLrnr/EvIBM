#include "linkedlist.h"

/* Creates a headed list, where the head holds a value, wich is -(size of the list + 1) */
List CreateHeadedList ()
{
  List head;

  head = malloc (sizeof (Cell));  
  head->info = -1;
  head->next = NULL;

  return head;
}

/* This function add a cell to the list, if and only if it is not on the list already, and in order
it also updates the size of the list */
void AddCellInOrder (List *list, int value)
{
  List add, p;

  add = malloc (sizeof (Cell));
  add->info = value;
  add->next = NULL;

  if (*list == NULL) {
    add->next = NULL;
    *list = add;
  }

  else {
    if (value < (*list)->info) {
      p = (*list);
      (*list) = add;
      (*list)->next = p;
    }
    else {
      for (p = *list; p->next != NULL && (p->next)->info < value; p = p->next);
      if (p->next == NULL) {
        add->next = NULL;
        p->next = add;
        (*list)->info --;
      }
      else if ((p->next)->info > value) {
        add->next = p->next;
        p->next = add;
        (*list)->info --;
      }
      else 
        free (add);
    }
  }
}

/* This function removes a cell with a certain value from the list, and updates the list size */
void RemoveCell (List *list, int value)
{
  List p, discard;

  discard = NULL;

  if ((*list) != NULL) {

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
        else if ((p->next)->info > value)
          return;
      }
    }
    if (discard != NULL)
      free (discard);
  }

}

List FindValue (int value, List *list)
{
  List p;

  for (p = *list; p != NULL && p->info < value; p = p->next);
  if (p != NULL) {
    if (p->info == value) return p;
  }
  return NULL;
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

void AlterListW (List *list, int value)
{
  if (FindValue (value, list) == NULL) {
    AddCellInOrder (list, value);
  }
  else {
    RemoveCell (list, value);
  }
}

void AlterList (List *list, int value)
{
  List add, del, p;

  add = malloc (sizeof (Cell));
  add->info = value;
  add->next = NULL;

  if (*list == NULL) {
    printf("ERRO\n");
  }

  else {
    if (value < (*list)->info) {
      p = (*list);
      (*list) = add;
      (*list)->next = p;
      (*list)->info --;
    }
    else {
      for (p = *list; p->next != NULL && (p->next)->info < value; p = p->next);
      if (p->next == NULL) {
        add->next = NULL;
        p->next = add;
        (*list)->info --;
      }
      else if ((p->next)->info > value) {
        add->next = p->next;
        p->next = add;
        (*list)->info --;
      }
      else {
        del = p->next;
        p->next = (p->next)->next;
        free (del);
        free (add);
        (*list)->info ++;
      }
    }
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

void RestartList (List *list)
{
  List p, discard;

  if (*list != NULL) {
    for (p = *list; p->next != NULL;) {
      discard = p;
      p = p->next;
      free (discard);
    }
    free (p);

    (*list) = malloc (sizeof (Cell));
    (*list)->info = -1;
    (*list)->next = NULL;
  }
}

  int Verify_Head (List *list)
  {
    return (-((*list)->info + 1));
  }
