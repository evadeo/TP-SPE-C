/* graph.h: Simple Graph implementation */

# ifndef S3_PRACTICAL_GRAPH_H_
# define S3_PRACTICAL_GRAPH_H_

# include <stdlib.h>

struct vertex {
size_t       degree;
unsigned    *succ;
};

struct graph {
unsigned             order;
struct vertex       *vertices;
};

/* new_graph(order) create an empty (no link) graph */
/* order: number of vertices */
struct graph* new_graph(unsigned order);

/* graph_set_max_degree(g, vertex, degree) pre-allocate vertex's successors
 * array for the given degree, vertex degree field is set to 0. */
void graph_set_max_degree(struct graph *g, unsigned vertex, size_t degree);

/* graph_add_edge(g, v0, v1) add an edge between v0 and v1 */
/* max degree must have been set for both vertices */
/* edges are undirected and successors must be added to both v0 and v1 */
void graph_add_edge(struct graph *g, unsigned v0, unsigned v1);


/* graph_delete(g) delete and release g */
void graph_delete(struct graph *g);

/* foreach macro for successors */
/* s_name_ must be a predeclared var of type unsigned* */
# define for_successors(g_, v_, s_name_)                             \
  for (s_name_ = (g_)->vertices[v_].succ;                            \
       s_name_ < (g_)->vertices[v_].succ + (g_)->vertices[v_].degree; \
       s_name_++ )

# endif /* S3_PRACTICAL_GRAPH_H_ */
