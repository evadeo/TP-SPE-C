#ifndef ITERATOR_H_
#define ITERATOR_H_
#include <stdlib.h>

struct iterator {
    struct tree          *cur;
    struct queue         *q;
};

/*
 * tree_iterator(t) returns an iterator on t
 */
struct iterator* tree_iterator(struct tree *t);

/*
 * iterator_next(it) move to next element
 * if it is not the end of the iteration
 */
void iterator_next(struct iterator *it);
/*
 * iterator_is_end(it) returns true if it is the end of the iteration
 */
int  iterator_is_end(struct iterator *it);

/*
 * iterator_get(it) returns the key of the current node
 * undefined if it is the end
 */
int iterator_get(struct iterator *it);

#endif /* !ITERATOR_H_ */
