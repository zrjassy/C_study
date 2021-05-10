OBJS=test.o
cc=g++
CFLAGS=-c

all: test clean
test:$(OBJS)
	@$(cc) -o test $(OBJS) "-lavdevice" "-lavfilter" "-lavformat" "-lavcodec" "-lavutil" "-lswscale" "-lSDL2"
            

test.o:test.cpp 
	@$(cc) $(CFLAGS) test.cpp "-lavdevice" "-lavfilter" "-lavformat" "-lavcodec" "-lavutil" "-lswscale" "-lSDL2"

.PHONY clean :
	@rm -f *.o 