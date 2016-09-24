#include "dfs_spanning_tree.h"


void dfs_rec(struct graph *g, unsigned v, unsigned p,
            unsigned pre[], unsigned *c)
{
  pre[v] = *c;
  *c +=1;
  struct vertex ve=g->vertices[v];
  for(unsigned i=0;i<ve.degree;i++)
    if (ve.succ[i] != p && !(pre[ve.succ[i]]))
        dfs_rec(g,ve.succ[i],v,pre,c);

}


void dfs(struct graph *s, unsigned src)
{
  unsigned pre[s->order];
  for(unsigned i=0;i<s->order;i++)
    pre[i]=0;

  unsigned c = 1;
  dfs_rec(s,src,0,pre,&c);
  for(unsigned i=0;i<s->order;i++)
    if (pre[i]==0)
      dfs_rec(s,i,0,pre,&c);
}
