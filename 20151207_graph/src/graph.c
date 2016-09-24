/* graph.c: Simple Graph implementation */

# include <stdlib.h>

# include "graph.h"

/* new_graph(order) create an empty (no link) graph */
/* order: number of vertices */
struct graph* new_graph(unsigned order) {
  struct graph *g = malloc(sizeof (struct graph));
  g->order = order;
  g->vertices = calloc(order, sizeof (struct vertex));
  return g;
}

/* graph_set_max_degree(g, vertex, degree) pre-allocate vertex's successors
 * array for the given degree, vertex degree field is set to 0. */
void graph_set_max_degree(struct graph *g, unsigned vertex, size_t degree) {
  struct vertex *v = g->vertices + vertex;
  v->succ = calloc(degree, sizeof (unsigned));
  v->degree = 0;
}

/* graph_add_edge(g, v0, v1) add an edge between v0 and v1 */
/* max degree must have been set for both vertices */
/* edges are undirected and successors must be added to both v0 and v1 */
void graph_add_edge(struct graph *g, unsigned v0, unsigned v1) {
  struct vertex *pv0 = g->vertices + v0;
  struct vertex *pv1 = g->vertices + v1;
  pv0->succ[pv0->degree] = v1;
  pv0->degree += 1;
  pv1->succ[pv1->degree] = v0;
  pv1->degree += 1;
}

void graph_delete(struct graph *g) {
  for (unsigned i = 0; i < g->order; i++) {
    struct vertex *v = g->vertices + i;
    free(v->succ);
  }
  free(g->vertices);
  free(g);
}
