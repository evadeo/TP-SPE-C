#include "vector.h"

void extend_cap(struct vector *vect)
{
  vect->data = realloc(vect->data, vect->capacity * 2);
  vect->capacity = vect->capacity * 2;
}

struct vector* vector_make(size_t capacity)
{
  struct vector *v = malloc(sizeof(struct vector));
  v->capacity = capacity;
  v->size = 0;
  v->data = malloc(capacity * sizeof(int));
  return v;
}

void vector_push_back(struct vector *vect, int x)
{
  if (vect->capacity == vect ->size)
    extend_cap(vect);
  *(vect->data + vect->size) = x;
  vect->size = vect->size + 1;
}

int  vector_pop_back(struct vector *vect, int *x)
{
  if (!vect->size)
    return 0;
  *x = vect->data[vect->size-1];
  vect->size -= 1;
  return 1;
}

void vector_push_front(struct vector *vect, int x)
{
  if (vect->capacity == vect ->size)
    extend_cap(vect);
  for (size_t i =vect->size - 1; i == 0; i--) {
    int tmp = *(vect->data+i);
    *(vect->data + i+1) = tmp;
  }
  vect->size = vect->size + 1;
  *(vect->data) = x;
}

int  vector_pop_front(struct vector *vect, int *x)
{
  if (!vect->size)
    return 0;
  *x = *vect->data;
  for (size_t i = 0;i < vect->size -1;i++)
    vect->data[i] = vect->data[i+1];
  vect->size = vect->size -1;
  return 1;
}

int vector_insert_at(struct vector *vect, size_t pos, int x)
{
  if (pos == 0)
    vector_push_front(vect,x);
  else {
    if (pos == vect->size)
      vector_push_back(vect,x);
    else {
      if (vect->capacity == vect ->size)
        extend_cap(vect);
      for (size_t i = vect->size; i > pos;i--)
        vect->data[i] = vect->data[i-1];
      vect->data[pos] = x;
      vect->size += 1;
    }
  }
  return pos <= vect->size;
}

int vector_extract_at(struct vector *vect, size_t pos, int *x)
{
  if (vect->size == 0 || pos >= vect->size)
    return 0;
  if (pos == 0)
    vector_pop_front(vect,x);
  else if (pos == vect->size - 1)
    vector_pop_back(vect,x);
  else {
    *x = vect->data[pos];
    for (size_t i = pos;i<vect->size - 1;i++)
      vect->data[i] = vect->data[i+1];
    vect->size -= 1;
  }
  return 1;
}


struct vector* vector_clone(struct vector *vect)
{
  struct vector *cp = malloc(sizeof(struct vector));
  cp->capacity = vect->capacity;
  cp->size = vect->size;
  cp->data = malloc(sizeof(int)*cp->capacity);
  for (size_t i = 0; i < cp->size;i++)
    cp->data[i] = vect->data[i];
  return cp;
}

int main()
{
  struct vector *v = vector_make(3);
  assert(vector_insert_at(v,0,2));
  assert(vector_insert_at(v,0,1));
  assert(vector_insert_at(v,2,8));
  assert(vector_insert_at(v,2,3));
  for (int i = 0; i < 4;i++)
    printf("| %d ",v->data[i]);
  printf("|\n");
  struct vector *v2 = vector_clone(v);
  int x;
  printf("size: %lu; capacity: %lu\n",v2->size,v2->capacity);
  assert(vector_extract_at(v2,3,&x));
  printf("position 4: %d\n",x);
  assert(vector_extract_at(v2,0,&x));
  printf("position 1: %d\n",x);
  assert(vector_extract_at(v2,1,&x));
  printf("position 3: %d\n",x);
  assert(vector_extract_at(v2,0,&x));
  printf("position 2: %d\n",x);
  return 0;
}
