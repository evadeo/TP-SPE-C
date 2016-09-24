// testing.c
// Testing intrusive lists

# include <stdlib.h>
# include <stdio.h>

# include "list.h"

// Basic usage: list of integers

struct data {
int           value;
struct list   list_;
};

struct list* build_int_list(int len, struct data storage[]) {
struct list          *sentinel;
sentinel = malloc(sizeof (struct list));
list_init(sentinel);
for (int i = 0; i < len; ++i) {
storage[i].value = i;
list_push_front(sentinel, &(storage[i].list_));
}
return sentinel;
}

void print_list(struct list *l) {
int                   line;
line = printf("[");
for (struct list *cur = l->next; cur != NULL; cur = cur->next) {
if (line > 72) {
printf("\n");
line = printf(" ");
}
line += printf(" %3d;", CONTAINER_OF_(struct data, list_, cur)->value);
}
if (line > 72) printf("\n");
printf(" ]\n");
}

# define LEN 100

int main() {
struct list          *l;
struct data          *storage;
storage = calloc(LEN, sizeof (struct data));
l = build_int_list(LEN, storage);
print_list(l);
l = reverse(l);
print_list(l);
free(l);
free(storage);
return 0;
}

