#include "stdlib.h"
#include "stdio.h"

void print_matrix(int M[], size_t m, size_t n) {
  for (size_t i = 0; i < m; i++) {
    size_t line_offset = i * n;
    for (size_t j = 0; j < n; j++) {
      printf("| %3d ", M[line_offset + j]);
    }
    printf("|\n");
  }
}

void fill_matrix(int M[], size_t m, size_t n)
{
  for (size_t i = 0; i < m; i++) {
    size_t line_offset = i*n;
    for (size_t j = 0; j < n; j++) {
      *(M+line_offset+j) = j*m + i;
    }

  }

}

int main()
{
  size_t m = 3, n = 5;
  int *M = malloc(sizeof(int)*m*n);
  fill_matrix(M,m,n);
  print_matrix(M,m,n);
  return 0;
}
