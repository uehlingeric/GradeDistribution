CFLAGS	=	-c -Wall -Wextra -std=c11 -Werror -g

all:  dist

dist: main.o dist.o
	gcc -o dist main.o dist.o

dist.o: dist.c dist.h
	gcc ${CFLAGS} dist.c

main.o: main.c dist.h
	gcc ${CFLAGS} main.c

clean:
	rm *.o  dist generator
