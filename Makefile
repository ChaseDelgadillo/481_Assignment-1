#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CC = g++
CFLAGS  = -std=c++11 -g -Wall

default: assignment1

assignment1:  hw1.o EightPuzzle.o Heuristics.o Tools.o 
	$(CC) $(CFLAGS) -o assignment1 hw1.o EightPuzzle.o Heuristics.o Tools.o

hw1.o: hw1.h hw1.cpp 
	$(CC) $(CFLAGS) -c hw1.cpp

EightPuzzle.o: EightPuzzle.h EightPuzzle.cpp 
	$(CC) $(CFLAGS) -c EightPuzzle.cpp

Heuristics.o: Heuristics.h Heuristics.cpp 
	$(CC) $(CFLAGS) -c Heuristics.cpp

Tools.o: Tools.h Tools.cpp 
	$(CC) $(CFLAGS) -c Tools.cpp

clean: 
	$(RM) assignment1 *.o *~