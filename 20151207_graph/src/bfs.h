/* bfs.h: BFS traversal computing maximal distance */

# ifndef S3_PRACTICAL_BFS_H_
# define S3_PRACTICAL_BFS_H_

# include <stdlib.h>
#include "s3_practical_graph_queue.h"
# include "graph.h"

size_t simple_bfs(struct graph *g, unsigned src);

# endif /* S3_PRACTICAL_BFS_H_ */
