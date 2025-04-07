CC = gcc
CFLAGS = -O2

SRC_FILES :=  bsort.c bsort_mt.c
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))

all: 01 02 03 04 05

01: 01.c bsort.o bsort_mt.o
	$(CC) $^ -o $@

02: 02.c
	$(CC) $^ -o $@

03: 03.c bsort.o bsort_mt.o
	$(CC) $^ -o $@

04: 04.c
	$(CC) $^ -o $@

05: 05.c
	$(CC) $^ -o $@

clean:
	rm a.out *.o 01 02 03 04 05
	
$(OBJ_FILES): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
