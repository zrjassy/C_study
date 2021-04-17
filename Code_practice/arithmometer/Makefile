OBJS=main.o oper.o
cc=gcc
CFLAGS=-c

oper:$(OBJS)
	@$(cc) -o oper $(OBJS)

main.o:main.c oper.h
	@$(cc) $(CFLAGS) main.c

hellow.o : oper.c oper.h
	@$(cc) $(CFLAGS) oper.c

.PHONY clean :
	@rm -f *.o oper
