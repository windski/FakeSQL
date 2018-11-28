CXX = g++
CFLAGES = -std=c++11 -Wall -g

OBJS = bplustree.o main.o

all: $(OBJS)
	$(CXX) -o a.out $(OBJS)

.c.o: $(OBJS)
	$(CXX) $(CFLAGES) -c -o $*.o $<

.PHONY: clean

clean:
	rm *.o

