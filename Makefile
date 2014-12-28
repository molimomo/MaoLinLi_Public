GXX = g++

FLAGS= -g -O2 -Wall

INCDIR = -I ./include

CFLAGS = $(FLAGS) $(INCDIR)

## source files

SRCS = *.cpp

OBJS = $(SRCS:%.cpp=%.o)

all: run_deck

.cpp.o: 
	$(GXX) $(CFLAGS) -c $< -o $@

run_deck: $(OBJS)
	$(GXX) -o run_deck $(OBJS) 

link: $(OBJS)
	rm -f run_deck
	$(GXX) -o run_deck $(OBJS)

run: run_deck
	./run_deck 2>&1 | tee output.txt

clean:
	@rm -f *.o run_deck
