
/* string_len.c */

# include <stdio.h>
# include <stdlib.h>

size_t mystrlen(char *s)
{
  size_t i;
  for(i=0; *(s+i)!= 0;i++) {}
  return i;
}

int main() {
  char *s = "abcdefghijklmnopqrstuvwxyz";
  printf("sizeof(s) = %zu\n", sizeof (s));
  return 0;
}
