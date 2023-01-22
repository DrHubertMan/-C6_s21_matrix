CC = gcc -Wall -Werror -Wextra -fsanitize=address
CFLAGS = -c
OFLFAGS = -o

all: test

test: s21_matrix.o
	$(CC) $(OFLFAGS) test.out *.o
	rm -rf *.o
	./test.out

s21_matrix.o: 
	$(CC) $(CFLAGS) *.c

clean: 
	rm -rf *.out *.o

rebuild: clean all