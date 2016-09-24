#define _XOPEN_SOURCE 500
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>


static inline
size_t word_align(size_t n)
{
  n = (n-1)>>2;
  n = n<<2;
  return n+4;
}

/* zerofill(ptr, len): write len 0 bytes at the address ptr */
static inline
void zerofill(void *ptr, size_t len)
{
  char *new = ptr;
  for (size_t i = 0; i < len; i++) {
    new[i]=0;
  }

}
/* wordcpy(dst, src, len) copy len bytes from src to dst */
static inline
void wordcpy(void *dst, void *src, size_t len)
{
  size_t i;
  for (i = 0; i<len; i++) {
    *((char *)dst + i) = *((char *)src + i);
  }

}

struct chunk {
    struct chunk *next, *prev;
    size_t        size;
    long          free;
    void         *data;
};

static
struct chunk* get_base(void) {
  static struct chunk *base = NULL;
  if (base == NULL) {
    base = sbrk(sizeof(struct chunk));
    if (base == (void*)(-1)) {
      _exit(71);
    }
    base->next = NULL;
    base->prev = NULL;
    base->size = 0;
    base->free = 0;
    base->data = NULL;
  }
  return base;
}


/*
 * extend_heap(last, size) extends the heap with a new chunk
 * containing a data block of size bytes.
 * Return 1 in case of success, and return 0 if sbrk(2) fails.
 */
static
int extend_heap(struct chunk *last, size_t size)
{
  struct chunk *new = sbrk(0);
  if (sbrk(sizeof(struct chunk)+size) == (void *)(-1))
    return 0;
  if (last)
    last->next = new;
  new->next = NULL;
  new->prev = last;
  new->size = size;
  new->free = 0;
  new->data = (char*)new + sizeof( struct chunk);
  if (!new->data)
    return 0;
  return 1;
}

static
struct chunk* find_chunk(size_t size)
{
  /*struct chunk *k = get_base();
  while (k && !(k->size >= size && k->free)) {
    k=k->next;
  }
  return k->prev;*/
  struct chunk *cur, *prev = NULL;
  for (cur=get_base(); cur && (!cur->free || cur->size < size); cur=cur->next)
    prev = cur;
  return prev;
}


static
struct chunk* get_chunk(void *p)
{
  if(!(p && (p == (void*)word_align((size_t)p))))
    return NULL;
  if (p >= sbrk(0) || (size_t)p < (size_t)get_base())
    return NULL;
  struct chunk *k = (void *)((char *)p - sizeof(struct chunk));
  return k;
}


void* malloc(size_t size)
{
  if(!size)
    return NULL;
  size = word_align(size);
  struct chunk *k = find_chunk(size);
  //if (k)
  //  k=k->next;
  //if (!k->next)
  //{
    struct chunk *last =get_base();
    while (last->next)
      last = last->next;
    if (extend_heap(last,size))
    {
      k = last->next;
    }
    if (!k)
      return NULL;
    //}
  k->free = 0;
  return k->data;
}

void* calloc(size_t nb, size_t size)
{
  size_t *x = malloc(nb*size);
  if (!x)
    return NULL;
  size = word_align(nb*size);
  zerofill(x,size);
  return x;
}

void* realloc(void *old, size_t newsize)
{
  if (!newsize)
  {
    free(old);
    return NULL;
  }
  if (old) {
    struct chunk *k = get_chunk(old);
    if (newsize < k->size)
      return old;
    struct chunk *x = (struct chunk *)((char*)malloc(newsize) - sizeof(struct chunk));
    // PROBLEM HERE
    if (k->size > x->size)
      wordcpy(x->data,old,x->size);
    else
      wordcpy(x->data,old,k->size);
    free(old);
    return x->data;
  }
  return malloc(newsize);
}


/*
    Get the pointer to the chunk
    Check if you can satisfy the new size without another allocation
    Allocate a new block
    Copy the data from the old block to the new one
    Free the old block
 */
void  free(void *p)
{
  if ((size_t)get_base() < (size_t)p && (size_t)p < (size_t)sbrk(0))
  {
    struct chunk *k = get_chunk(p);
    if (k)
      k->free = 1;
  }
}

