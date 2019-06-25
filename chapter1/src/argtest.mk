PROGRAM =	argc_argv
OBJS    =	argcargv_test.o
SRCS    =	$(OBJS:%.o=%.c)
CC      =	gcc
CFLAGS  =	-g -O3 -Wall
LDFLAGS =

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	$(RM) *.o

clean:
	@rm -rf *.exe *.o *~