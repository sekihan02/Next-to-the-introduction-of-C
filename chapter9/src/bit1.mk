PROGRAM =	bit1
OBJS    =	bit1.o
SRCS    =	$(OBJS:%.o=%.c)
CC      =	gcc
CFLAGS  =	-g -O0 -Wall
LDFLAGS =


$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
	$(RM) *.o

clean:
	@rm -rf *.exe