#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Tools.h"
#include "Heuristics.h"
using namespace std;


class EightPuzzle
{
public:
	EightPuzzle();
	~EightPuzzle();

	// Algorithm 1: Steepest Hill Climb
	void steepestHillClimb(int heuristic);
	
	// Check child heuristic value for next move
	int checkChildHeuristic(char board[][3], int direction, int heuristic);

	// Move tile in given direction
	void moveTile(char (&board)[3][3], int direction);

	// Algorithm 2: Best First Search
	void bestFirstSearch(int heuristic);


	// Initial Board
	char initBoard[3][3];

	// Target Board
	char targetBoard[3][3];

private:
	const int NORTH = 0;
	const int SOUTH = 1;
	const int EAST  = 2;
	const int WEST  = 3;

};

