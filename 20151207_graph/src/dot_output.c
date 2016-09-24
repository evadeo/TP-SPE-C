/* dot_output.c: write graph in dot format */

# include <err.h>
# include <stdio.h>
# include <stdlib.h>

# include "dot_output.h"
# include "graph.h"

void dot_output(const char *fname, struct graph *g) {
  FILE *file;
  file = fopen(fname, "w");
  if (file == NULL) {
    warn("can't open %s", fname);
    return;
  }
  fprintf(file,"graph G {\n");

  for (unsigned i = 0; i < g->order; i++) {
    for (unsigned j = i; j <g->order; j++) {
      fprintf(file,"%i -- %i;\n",i,j);
    }
  }
  fprintf(file,"}\n");


  fclose(file);
}
