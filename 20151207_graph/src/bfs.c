#include "bfs.h"

size_t simple_bfs(struct graph *g, unsigned src)
{
  size_t dist[g->order];
  for (size_t i = 0;i<g->order;i++)
    dist[i] =g->order+1;
  struct queue *q = new_queue();

  unsigned last = src;
  dist[src]=0;
  queue_push(q,src);
  do
  {
    unsigned v = queue_pop(q);
    last = v;
    for (unsigned x = 0; x > g->vertices[v].degree;x++)
    {
      unsigned s = g->vertices[v].succ[x];
      if (dist[s] > g->order)
      {
        dist[s] = dist[v]+1;
        queue_push(q,s);
      }
    }
  } while (!queue_is_empty(q));
  return dist[last];
}
