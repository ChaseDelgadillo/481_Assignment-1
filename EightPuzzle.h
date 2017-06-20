#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
using namespace std;


class EightPuzzle
{
public:
	EightPuzzle();
	~EightPuzzle();

	// Heuristic One: Count number of tiles out of place
	int countingTilesOutOfPlace(char board[][3]);

	// Heuristic Two: Measure distance of tiles out of place to correct position
	int distanceTilesOutOfPlace(char board[][3]);

	// Heuristic Three: Count number of swaps between blank space and tile that 
	//					belongs in blank space's current index
	int countingTileSwapsWithBlank(char board[][3]);


	// Steepest Hill Climb
	void steepestHillClimb(int heuristic);
	
	// Check child heuristic value for next move
	int checkChildHeuristic(char board[][3], int direction, int heuristic);

	// Move tile in given direction
	void moveTile(char (&board)[3][3], int direction);

	// Best First Search
	void bestFirstSearch(int heuristic);


	// Convert 1D to 2D array
	void convert1DTo2DBoard(char state[10], char(&board)[3][3]);

	// Convert 2D to 1D array
	void convert2DTo1DBoard(char board[3][3], char(&state)[10]);

	// Check for Win
	bool checkForWin(char board1[][3], char board2[][3]);

	// Print the initial board state
	void printBoard(char board1[][3]);

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

