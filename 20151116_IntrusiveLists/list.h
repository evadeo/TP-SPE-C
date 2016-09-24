#ifndef LIST_H_
# define LIST_H_
#include <stddef.h>
# define CONTAINER_OF_(TYPENAME_, FIELDNAME_, PTR_)         \
  ((TYPENAME_*)(((char*)PTR_ - offsetof(TYPENAME_, FIELDNAME_))))

struct list {
    struct list          *next;
};
/*
struct data {
    char                *firstname, *lastname;
    unsigned             uid;
    struct list          list_;
};
*/
/*
 * list_init(sentinel)
 * Initialize list sentinel
 */
static inline
void list_init(struct list *sentinel) { sentinel->next = NULL;}

/*
 * list_is_empty(l)
 * test for empty list (doesn't work for uninitialized list)
 */
static inline
int list_is_empty(struct list *l) { return l->next == NULL;}

/*
 * list_len(l)
 * compute the length of l (without the sentinel)
 */
static inline
size_t list_len(struct list *l) {
  if (!l)
    return -1;
  struct list *t = l->next;
  size_t x = 0;
  while (t) {
    x++;
    t = t->next;
  }
  return x;
}

/*
 * list_push_front(l, cell)
 * add cell in front of the l
 * (keep sentinel unchanged)
 */
static inline
void list_push_front(struct list *l, struct list *cell) {
  struct list *tmp=l->next;
  l->next = cell;
  cell->next = tmp;
}

/*
 * list_pop_front(l)
 * extract and return the first element of the list
 * returns NULL if the list is empty
 * (keep sentinel unchanged)
 */
static inline
struct list* list_pop_front(struct list *l) {
  struct list *cell = l->next;
  l->next = cell->next;
  return cell;
}

/*** ACESSORS ***/

/*
 * Accessors always return a pointer to the cell *before* the wanted element,
 * so that we can use them as input for push_front/pop_front operations.
 * Unsuccessful accesses (empty list, or access after the last element) always
 * return NULL.
 * You can assume that whether the accessor returns NULL or it returns a
 * pointer p such that p->next != NULL and p->next is the expected cell.
 */

/*
 * list_nth(l, n)
 * returns the n-th element, where 0 is the head (not the sentinel)
 */
static inline
struct list* list_nth(struct list *l, size_t n) {
  if (!n)
    return list_pop_front(l);
  struct list *k = l->next;
  while (k->next && (--n))
    k = k->next;
  if (!n || k->next == NULL)
    return NULL;
  return k;
}

/*
 * list_last(l)
 * same as list_nth(l, list_len(l) - 1) but faster
 */
static inline
struct list* list_last(struct list *l) {
  struct list *k = l;
  if (!k || !k->next)
    return NULL;
  while (k->next->next)
    k = k->next;
  return k;
}

/*
 * reverse(l)
 * pop all element one by one and push them in a new list reusing the original
 * cells.
 * Your function must:
 *   - allocate a new sentinel
 *   - free the original sentinel when done
 */
struct list* reverse(struct list *l)
{
  struct list *k = malloc(sizeof(struct list));
  list_init(k);
  do
  {
    list_push_front(k,list_pop_front(l));
  }
  while (!list_is_empty(l));
  return k;
}

#endif /* !LIST_H_ */
