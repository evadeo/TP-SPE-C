#include "iterator.h"
#include "tree.h"

/*
 * tree_iterator(t) returns an iterator on t
 */
struct iterator* tree_iterator(struct tree *t)
{
  struct iterator *i = malloc(sizeof(struct iterator));
  i->cur = t;
  struct queue *q = queue_empty();
  if (t->left)
    queue_push(&q,t->left);
  if (t->right)
    queue_push(&q,t->right);
  i->q = q;
  return i;
}

/*
 * iterator_next(it) move to next element
 * if it is not the end of the iteration
 */
void iterator_next(struct iterator *it)
{
  if (!iterator_is_end(it))
  {
    struct tree *t = queue_pop(&(it->q));
    if (t->left)
      queue_push(&(it->q),t->left);
    if (t->right)
      queue_push(&(it->q),t->right);
  }
}

/*
 * iterator_is_end(it) returns true if it is the end of the iteration
 */
int  iterator_is_end(struct iterator *it)
{
  return queue_is_empty(it->q);
}
/*
 * iterator_get(it) returns the key of the current node
 * undefined if it is the end
 */
int iterator_get(struct iterator *it)
{
  if (iterator_is_end(it))
    return -1;
  struct tree *t = (it->q->next->val);
  return t->key;
}
