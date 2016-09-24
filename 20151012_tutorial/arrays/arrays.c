# define _XOPEN_SOURCE 600
# include "arrays.h"
# include <assert.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* print_array(begin, end) prints the ints stored between begin and end */
void print_array(int *begin, int *end)
{
  for(size_t i = 0; begin + i < end;i++)
  {
    printf("| %3d ", *(begin + i));
  }
  printf("|\n");
}

/* binsearch(x, begin, end) returns the pointer to the position of x,
 * the array between begin and end is supposed to be sorted.
 * binsearch returns the expected place of x: the pointer to the first cell
 * containing a value not smaller than x. If all cells contains smaller value,
 * the function returns end. */
int* binsearch(int x, int *begin, int *end)
{
  int dist = end - begin;
  if (dist < 1)
    return begin;
  int *mid;
  mid = begin + dist/(2);
  if (*mid < x)
    return binsearch(x, mid + 1,end);
  else
    return binsearch(x, begin, mid);
}

/* sorted_insert(x, begin, end) insert x at its place between begin and end,
 * the stored values are supposed to sorted in increasing order.
 * The function returns true (!= 0) if x wasn't in the array and false (0)
 * otherwise.
 * We assume that there is enough memory for an insertion. */
int sorted_insert(int x, int *begin, int *end)
{
  int *pos;
  pos = binsearch(x, begin, end);
  if (pos < end && *pos == x)
    return 0;
  if (pos < end)
  {
    memmove(pos + 1, pos, (end - pos)*sizeof(int) );
    end++;
  }
  *pos = x;
  return 1;
}


int *choose_pivot(int *begin, int *end)
{
  int *x;
  x = (begin + (end-begin)/2);
  return x;
}

void swap(int* a, int*b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

int* partition(int *begin, int *end, int *pivot)
{
  int pval = *pivot;
  swap(pivot,end-1);
  pivot = begin;
  int *i;
  for (i = begin; i != end - 1; i++) {
    if (*i < pval){
      swap(pivot,i);
      pivot++;
    }
  }
  swap(pivot,end-1);
  return pivot;
}
/* quick_sort(begin, end) sort the array between begin and end using the quick
 * sort algorithm. */
void quick_sort(int *begin, int *end)
{
  if (end-begin > 1)
  {
    int *pivot;
    pivot = choose_pivot(begin,end);
    pivot = partition(begin,end,pivot);
    quick_sort(begin,pivot);
    quick_sort(pivot + 1, end);
  }
}
