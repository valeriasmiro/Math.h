CC0=gcc
CC1=gcc
CFLAGS=-c
LDFLAGS= #-Wall -Wextra -Werror
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC1 += -D OS_MAC
else
	CC1 += -D OS_LINUX
endif

all: clean s21_math.a test  

test: s21_math.a test.c
ifeq ($(OS), Darwin)
	$(CC0) $(LDFLAGS) -o test test.c s21_math.a -lcheck
	./test
else
	gcc test.c s21_math.a -o test -lcheck -lsubunit -lrt -lpthread -lm
	./test
endif

s21_math.a: s21_math.o
	ar rcs s21_math.a s21_math.o
	ranlib $@
	cp $@ lib$@
	
s21_math.o: s21_math.c
	$(CC1) $(LDFLAGS) -c -o s21_math.o s21_math.c

clean:
	rm -rf test *.a *.o *.out fizz *.gc* *.info report

rebuild: clean all

gcov_report: 
ifeq ($(OS), Darwin)
	$(CC1) --coverage $(LDFLAGS) test.c s21_math.c -o test -lcheck
else
	$(CC1) --coverage $(LDFLAGS) test.c s21_math.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
