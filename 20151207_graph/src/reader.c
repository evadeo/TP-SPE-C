/* reader.c: Reading graph out of NDE format */

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "graph.h"
# include "reader.h"

static inline
size_t read_order(FILE *fin) {
  unsigned      order;
  if (fscanf(fin, "%u\n", &order) != 1)
    errx(3, "Unable to read order");
  return order;
}

static inline
void read_degrees(FILE *fin, struct graph *g) {
  for (size_t c = 0; c < g->order; ++c) {
    unsigned    v, d;
    if (fscanf(fin, "%u %u\n", &v, &d) != 2)
      errx(3, "Unable to read degree");
    graph_set_max_degree(g, v, d);
  }
}

static inline
void read_edges(FILE *fin, struct graph *g) {
  for (;;) {
    unsigned    s,d;
    if (fscanf(fin, "%u %u\n", &s, &d) != 2)
      break;
    graph_add_edge(g, s, d);
  }
}

struct graph* read_graph(const char *fname) {
  struct graph *g = NULL;
  FILE         *fin;
  fin = fopen(fname, "r");
  if (fin == NULL)
    err(3, "Error opening %s", fname);
  g = new_graph(read_order(fin));
  read_degrees(fin, g);
  read_edges(fin, g);
  fclose(fin);
  return g;
}
