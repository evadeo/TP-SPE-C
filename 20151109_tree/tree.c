#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "tree.h"

size_t tree_size(struct tree *t)
{
  if (!t || (!t->left && !t->right))
    return 0;
  return 1 + tree_size(t->left) + tree_size(t->right);
}

/*
 * tree_height(t) compute the height of the tree t
 * Note: height of an empty tree is -1
 */
int tree_height(struct tree *t) {
  if (!t)
    return -1;
  if (!t->left && !t->right)
    return 0;
  int a = tree_height(t->left);
  int b = tree_height(t->right);
  if (a>b)
    return 1 + a;
  else
    return 1 + b;
}

/*
 * tree_find(t, key) search for key in t
 * returns the pointer to the node holding key
 * returns NULL if not found.
 */
struct tree* tree_find(struct tree *t, int key)
{
  if (!t || t->key == key)
    return t;
  if (key < t->key)
    return tree_find(t->left, key);
  else
    return tree_find(t->right,key);
}
/*
 * tree_build_regular(depth, &keys)
 * Build a perfect tree of height depth.
 * keys are set (and incremented) in infix order.
 * We first build recursively the left child (with its subtree)
 * Then we increment keys and use it to set the key of the current node
 * Finally we build recursively the right child.
 */
struct tree* tree_build_regular(int depth, int *keys)
{
  if (depth == -1)
    return NULL;
  struct tree *t = malloc(sizeof(struct tree));
  t->left = tree_build_regular(depth-1,keys);
  *keys = *keys+1;
  t->key = *keys;
  t->right = tree_build_regular(depth-1,keys);
  return t;
}
/*
 * Basic printing: print the keys with a single space between each keys.
 */

/*
 * Depth first printing in prefix, infix or suffix order.
 */

void tree_depth_prefix_print(struct tree *t)
{
  if (t) {
    printf("%d ",t->key);
    tree_depth_prefix_print(t->left);
    tree_depth_prefix_print(t->right);
  }
}

void tree_depth_infix_print(struct tree *t)
{
  if (t) {
    tree_depth_infix_print(t->left);
    printf("%d ",t->key);
    tree_depth_infix_print(t->right);
  }
}

void tree_depth_suffix_print(struct tree *t)
{
  if (t) {
    tree_depth_suffix_print(t->left);
    tree_depth_suffix_print(t->right);
    printf("%d ",t->key);
  }
}


void queue_push(struct queue **q, void *p) {
  struct queue *new = malloc(sizeof(struct queue));
  new->val = p;
  if (queue_is_empty(*q)) {
    new->next = new;
  }
  else {
    new->next = (*q)->next;
    (*q)->next = new;
  }
  *q = new;
}

void* queue_pop(struct queue **q) {
  if (*q == (*q)->next)
  {
    void *k = (*q)->val;
    free(*q);
    *q= NULL;
    return k;
  }
  struct queue *l = (*q)->next;
  (*q)->next = (*q)->next->next;
  void *v = l->val;
  free(l);
  return v;
}

/*
 * Printing using a breadth first traversal
 * Keys are separated by space
 * Each level are separated by a new-line.
 */
void tree_breadth_print(struct tree *t)
{
  if (t)
  {
    struct queue *q = queue_empty();
    queue_push(&q,t);
    while (!queue_is_empty(q)) {
      t = queue_pop(&q);
      printf("%d ", t->key);
      if (t->left)
        queue_push(&q,t->left);
      if (t->right)
        queue_push(&q,t->right);
    }
    printf("\n");
  }
}

/*
 * dot output (see the subject)
 */
void tree_dot_out(struct tree *t, char *fname)
{
  if (t) {
    FILE *file;
    // open file in create/replace mode
    if ((file = fopen(fname, "w")) == NULL) {
      err(3, "Error while creating %s", fname);
    }
    fprintf(file, "digraph Tree {\n");
    /* BFS printing of tree edges */
    struct queue *q = queue_empty();
    queue_push(&q,t);
    while (!queue_is_empty(q)) {
      t = queue_pop(&q);
      if (t->left)
      {
        queue_push(&q,t->left);
        fprintf(file, "%d -> %d;\n", t->key,t->left->key);
      }
      if (t->right)
      {
        queue_push(&q,t->right);
        fprintf(file, "%d -> %d;\n", t->key,t->right->key);
      }

    }

    fprintf(file, "}\n");
    // close the file
    fclose(file);
  }
}
