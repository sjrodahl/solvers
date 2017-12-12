CC := gcc
CFLAGS := -Wall
OBJS := main.o linalg_iterations.o

test_linalg_iters: $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

%.o: %.c linalg_iterations.h
	$(CC) -c $<

#main.o: main.c linalg_iterations.h
#	$(CC) -c $<
#
#linalg_iterations.o: linalg_iterations.c linalg_iterations.h
#	$(CC) -c $<

.PHONY : clean
clean:
	-rm test_linalg_iters *.o
