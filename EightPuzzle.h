#pragma once
#include <iostream>
using namespace std;


class EightPuzzle
{
public:
	EightPuzzle();
	~EightPuzzle();

	// Heuristic One: Count number of tiles out of place
	int countingTilesOutOfPlace();

	// Heuristic Two: Measure distance of tiles out of place to correct position
	int distanceTilesOutOfPlace();

	// Heuristic Three: Count number of swaps between blank space and tile that 
	//					belongs in blank space's current index
	int countingTileSwapsWithBlank();


	// Steepest Hill Climb
	void steepestHillClimb(int heuristic);
	
	// Check child heuristic value for next move
	int checkChildHeuristic(int direction);

	// Move tile in given direction
	void moveTile(char board[][3], int direction);


	// Check for Win
	bool checkForWin(char board1[][3], char board2[][3]);

	// Print the initial board state
	void printBoard(char board1[][3]);

	// Initial Board
	char initBoard[3][3];

	// Target Board
	char targetBoard[3][3];
};

