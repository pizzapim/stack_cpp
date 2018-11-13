CXX = g++-7
CC = g++-7
CXXFLAGS = -Wall -Wextra

all: main

main.o: main.cpp Stack.h
	$(CXX) $(CXXFLAGS) -c main.cpp

main: main.o

clean:
	rm -f *.o *.h.gch *.exe main

run: all
	./main