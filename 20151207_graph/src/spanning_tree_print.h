/* spanning_tree_print.h: tools for spanning tree display */

# ifndef S3_PRACTICAL_SPANNING_TREE_PRINT_H_
# define S3_PRACTICAL_SPANNING_TREE_PRINT_H_

# include <err.h>
# include <stdio.h>
# include <stdlib.h>

static FILE *target_file = NULL;

/* open and initilize spanning tree output */
static inline
int init_spanning_output(const char *fname) {
if (target_file != NULL) {
warnx("an output file is already opened");
return 0;
}
target_file = fopen(fname, "w");
if (target_file == NULL) {
warnx("can't open output file %s", fname);
return 0;
}
fprintf(target_file, "digraph Spanning {\n");
return 1;
}

/* finish and close spanning tree output */
static inline
int close_spanning_output() {
if (target_file == NULL) {
warnx("can't close not opened output file");
return 0;
}
fprintf(target_file, "}\n");
fclose(target_file);
target_file = NULL;
return 1;
}

/* print discovery edge */
static inline
void print_discovery(unsigned s, unsigned d) {
if (target_file)
  fprintf(target_file, "  %u -> %u;\n", s, d);
}

/* print backward edge */
static inline
void print_backward(unsigned s, unsigned d) {
if (target_file)
  fprintf(target_file, "  %u -> %u [constraint=false color=red];\n", s, d);
}

# endif /* S3_PRACTICAL_SPANNING_TREE_PRINT_H_ */
