# Makefile

CC=clang -fsanitize=address
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=

SRC= main.c graph.c dot_output.c reader.c dfs_spanning_tree.c bfs.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

main: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	rm -f ${OBJ} ${DEP}
	rm -f main

# END
