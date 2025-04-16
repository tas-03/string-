CC = gcc
CFLAGS = -c -std=c11 -Wall -Wextra -Werror
CFLAGS_TEST = -lcheck -lsubunit -lm

INPUT_FILE_STRING = s21_string.c
INPUT_FILE_SPRINTF = s21_sprintf.c
INPUT_FILE_SSCANF = s21_sscanf.c
COMPILED_FILE_STRING = s21_string.o
COMPILED_FILE_SPRINTF = s21_sprintf.o
COMPILED_FILE_SSCANF = s21_sscanf.o
OUTPUT_FILE = s21_string.a
TEST_FILE = test.c

.PHONY: all clean rebuild clang

all: s21_string.a

clean:
	rm -f $(OUTPUT_FILE) $(COMPILED_FILE_STRING) $(COMPILED_FILE_SPRINTF) $(COMPILED_FILE_SSCANF) *.o *.gcda *.gcno test.c test *.info *.out -r report

rebuild: clang clean all

clang:
	clang-format -n *.c *.h

s21_string.a:
	$(CC) $(CFLAGS) $(INPUT_FILE_STRING) -lm
	$(CC) $(CFLAGS) $(INPUT_FILE_SPRINTF) -lm
	$(CC) $(CFLAGS) $(INPUT_FILE_SSCANF) -lm
	ar r $(OUTPUT_FILE) $(COMPILED_FILE_STRING) $(COMPILED_FILE_SPRINTF) $(COMPILED_FILE_SSCANF)
	ranlib $(OUTPUT_FILE)
	rm -rf *.o

test: clean
	checkmk test.check > test.c
	$(CC) $(CFLAGS) $(TEST_FILE) $(INPUT_FILE_STRING) $(INPUT_FILE_SPRINTF) $(INPUT_FILE_SSCANF) $(CFLAGS_TEST)

	$(CC) --coverage $(TEST_FILE) $(INPUT_FILE_STRING) $(INPUT_FILE_SPRINTF) $(INPUT_FILE_SSCANF) $(CFLAGS_TEST) -o test
	./test

gcov_report: clean test
	lcov --directory . --capture -o coverage.info
	genhtml --output-directory report --legend coverage.info --ignore-errors unmapped,unmapped
	open report/index.html
