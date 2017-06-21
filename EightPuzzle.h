/*
 * Class: CPSC-481
 * Assignment: 1
 *
 * Authors: Chase Delgadillo
 *			Dennis Wu
 * Date: 6/20/2017
 *
 * Implementing a steepest-ascent/-descent hill-climbing algorithm
 * and A* algorithm to solve the 8-puzzle problem.
 */
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include "Tools.h"
#include "Heuristics.h"
using namespace std;

// CLASS:	EightPuzzle
//			Holds the board states and algorithms for
//			finding best path to solution.
//			Keeps primary tool functions inside.
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

