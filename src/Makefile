CC = gcc -Wall -Werror -Wextra
CFLAGS = -c
CFLAGSCOV = -c -fprofile-arcs  -lcheck -ftest-coverage
OFLFAGS = -o

all: gcov_report

valgrind: test
	valgrind --log-file="valgrind.txt" --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./test_coverage.out > valgrind.txt

gcov_report: test
	gcov -f *.gcda
	lcov -t "test" -o test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report test.info  --rc lcov_branch_coverage=1
	open report/index.html

test: s21_matrix.a
	$(CC) --coverage $(OFLFAGS) test_coverage.out test.o -lcheck -L. s21_matrix.a
	./test_coverage.out

s21_matrix.a: s21_matrix.o
	ar rc s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o: check_s21_matrix.o
	$(CC) $(CFLAGSCOV) s21_matrix.c

check_s21_matrix.o:
	$(CC) $(CFLAGS) test.c

clean: 
	rm -rf *.out *.o *.a *.gcov *.gcda *.gcno *.info report

rebuild: clean all