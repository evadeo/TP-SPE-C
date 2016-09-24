## Simple SDL mini code

CC=gcc

CPPFLAGS=
CFLAGS= -fsanitize=address -Wall -Wextra -std=c99 -O0 -pedantic -g -o
LDFLAGS=
LDLIBS=

SRC= *.c
OBJ= ${SRC}

all: main

main: ${OBJ}
	gcc ${CFLAGS} main ${OBJ}

clean:
	rm -f *~ *.o
	rm -f main

# END
