PROGRAM = ptr_base
OBJS 	= ptr_base.o
SRCS	= $(OBJS:%.o=%.c)
CC		= gcc
CFLAGS	= -g -O3 -Wall

$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)
	$(RM) *.o

clean:
	@rm -rf *.exe