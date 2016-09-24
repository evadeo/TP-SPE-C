# define _XOPEN_SOURCE 500

# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>

/* Provided code for testing and inspiration */

static inline
void swap(int *a, int *b) {
//  printf("s(%d,%d) -|-|-|- ", *a,*b); //test
  int c = *a;
  *a = *b;
  *b = c;
//  printf("s(%d,%d)\n", *a,*b); //test
}


static
void fill_array(int arr[], size_t len) {
  for (size_t i = 0; i < len; i++)
    arr[i] = random() % 1000;
}

static
void print_array(int arr[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    printf("| %3d ", arr[i]);
  }
  printf("|\n");
}

/**********************************/
/* Code to be completed  */
/* See subject for specifications */
/**********************************/

int* min_pos(int arr[], size_t len) {
  int *res;
  res = arr;
  for (size_t i = 0; i < len;i++)
  {
    if (arr[i] < *res)
      res = arr + i;
  }
//  printf("min_pos : %d\n", *res);
  return res;
}

void select_sort(int arr[], size_t len) {
  for (size_t i = 0; i < len - 1; i++) {
//    print_array(arr,len); // test
    int *min;
    min = min_pos(arr + i,len - i);
//    printf("-%d-\n", *min);
    int *my_point;
    my_point = arr + i;
    swap(my_point, min);
  }
}

int is_sorted(int arr[], size_t len) {
  for (size_t i = 1; i < len; i++) {
//    printf("i_s : %3d\n", arr[i]);
    if (arr[i-1] > arr[i])
      return 0;
  }
  return 1;
}

/* entry point */

int main(int argc, char *argv[]) {
  // Need a length
  if (argc < 2)
    errx(1, "missing array len");
  size_t len = strtoul(argv[1], NULL, 10);
  // Create and fill array
  int *arr = malloc(len * sizeof (int));
  fill_array(arr, len);
  // Print the array
  print_array(arr, len);

  // Sort array using your code
  select_sort(arr, len);

  // Print it again
  print_array(arr, len);

  // Assertion: verify that array is sorted
  assert(is_sorted(arr, len));
  return 0;
}
