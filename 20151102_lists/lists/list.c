#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "list.h"


struct list* list_empty(void)
{
  struct list* l = malloc(sizeof(struct list));
  l->next = NULL;
  return l;
}

size_t list_len(struct list *l)
{
  struct list *s = l->next;
  int x = 0;
  while(s!=NULL)
  {
    s=s->next;
    x++;
  }
  return x;
}

void list_push_front(struct list *l, struct list *elm)
{
  elm->next = l->next;
  l->next = elm;
}

struct list* list_find(struct list *l, int value)
{
  struct list* k = l->next;
  while(k!=NULL && k->value != value)
    k=k->next;
  return k;
}

struct list* list_pop_front(struct list *l)
{
  struct list *k = l->next;
  if (!k)
    return NULL;
  l->next = k->next;
  return k;
}

void list_insert(struct list *l, struct list *elm)
{
  struct list *k = l;
  while (k->next !=NULL && k->next->value < elm->value)
    k = k->next;
  list_push_front(k,elm);
}

void list_sort(struct list *l)
{
  struct list *head = l->next;
  l->next = NULL;
  while (head)
  {
    struct list *cur = head;
    head = head ->next;
    if (!cur)
      break;
    list_insert(l,cur);
  }
}

iterator list_begin(struct list *l)
{
  return l;
}

int list_is_end(iterator it)
{
  return it->next == NULL;
}

void list_next(iterator *it)
{
  if ((*it)->next)
    *it = (*it)->next;
}

int list_get(iterator it)
{
  return it->next->value;
}

void list_insert_at(iterator it, struct list *elm)
{
  elm->next = it;
}

void iterator_print(struct list *l) {
  int                           line;
  line = printf("l = [");

  // Iterate using iterators
  for (iterator it = list_begin(l); !list_is_end(it); list_next(&it)) {
    assert(it && it->next);
    if (line > 72) // break long lines
      line = printf("\n     ") - 1;
    line += printf(" %3d;", list_get(it));
  }

  printf("%s]\n", line>72 ? "\n" : " ");
}

int main()
{
  struct list *l = list_empty();
  int index = 0;
  while (index < 8)
  {
    struct list *k = malloc(sizeof(struct list));
    k->value = index++;
    k->next = NULL;
    list_push_front(l,k);
  }
  iterator_print(l);
  printf("nb of elements in list: %lu\n", list_len(l));
  list_sort(l);
  iterator_print(l);
  return 1;
}
