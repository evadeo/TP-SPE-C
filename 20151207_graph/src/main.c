/* Some tests */

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "bfs.h"
# include "dfs_spanning_tree.h"
# include "dot_output.h"
# include "graph.h"
# include "reader.h"

void basic_test(const char *fname, const char *fname_out) {
  struct graph *g;
  g = read_graph(fname);
  if (g == NULL)
    errx(3, "Error while opening file %s", fname);
  printf("Graph order: %u\n", g->order);
  dot_output(fname_out, g);
  dfs(g, 0);
  size_t maxdist;
  maxdist = simple_bfs(g, 0);
  printf("Maximal distance from 0: %zu\n", maxdist);
  graph_delete(g);
}

int main(int argc, char *argv[]) {
  if (argc < 3)
    errx(1, "missing arguments");
  basic_test(argv[1], argv[2]);
  return 0;
}
