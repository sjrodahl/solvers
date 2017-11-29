$CC = gcc
$CFLAGS = -Wall

newton: newton.c
	gcc -o newton -lm newton.c
fixpoint: fixpoint.c
	$(CC) -o $@ $< -lm



.PHONY: clean
clean:
	rm newton fixpoint
