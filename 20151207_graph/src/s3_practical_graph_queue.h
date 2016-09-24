# ifndef S3_PRACTICAL_GRAPH_QUEUE_H
# define S3_PRACTICAL_GRAPH_QUEUE_H

# include <assert.h>
# include <stdlib.h>

struct qcell {
struct qcell *next;
unsigned      val;
};

/* queue sentinel */
struct queue {
struct qcell *entry;
};

static inline
struct queue* new_queue() {
return calloc(1, sizeof (struct queue));
}

static inline
int queue_is_empty(struct queue *queue) {
return queue->entry == NULL;
}

static inline
void queue_push(struct queue *queue, unsigned x) {
struct qcell *tmp = malloc(sizeof (struct qcell));
tmp->val = x;
tmp->next = tmp;
if (queue->entry) {
tmp->next = queue->entry->next;
queue->entry->next = tmp;
}
queue->entry = tmp;
}

static inline
unsigned queue_pop(struct queue *queue) {
assert(queue->entry);
struct qcell *tmp = queue->entry->next;
unsigned r = tmp->val;
if (tmp->next == tmp)
  queue->entry = NULL;
else
  queue->entry->next = tmp->next;
free(tmp);
return r;
}

# endif
