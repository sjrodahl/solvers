CC = gcc
LIBS = -lm
CFLAGS = -Wall

simpson: simpson.o
	$(CC) $(CFLAGS) -o simpson simpson.o $(LIBS)

.PHONY: clean
clean:
	rm simpson *.o
