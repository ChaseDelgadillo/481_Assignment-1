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
#include "Heuristics.h"


// HEURISTIC ONE: Count number of tiles out of place
//				This function finds heuristic value by
//				counting the number of tiles out of place.
// PARAMETERS:	board[][] - current board state
//				targetBoard[][] - target board state
// OUTPUT:		int - heuristic value
int countingTilesOutOfPlace(char board[][3], char targetBoard[][3]) {
	int count = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != targetBoard[i][j] && (board[i][j] >= '1' && board[i][j] <= '8')) {
				count++;
			}
		}
	}

	return count;
}

// HEURISTIC TWO: Sum distance of tiles out of place to target tile position
//				This function finds the heuristic value by
//				totaling the distance for each tile to reach its goal position.
// PARAMETERS:	board[][] - current board state
//				targetBoard[][] - target board state
// OUTPUT:		int - heuristic value
int distanceTilesOutOfPlace(char board[][3], char targetBoard[][3]) {
	int count = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != targetBoard[i][j] && (board[i][j] >= '1' && board[i][j] <= '8')) {
				//cout << "out of place : " << board[i][j] << "\trow: " << i << "\tcol: " << j << endl;
				for (int targetrow = 0; targetrow < 3; targetrow++) {
					for (int targetcol = 0; targetcol < 3; targetcol++) {
						if (targetBoard[targetrow][targetcol] == board[i][j]) {
							//cout << "correct place: " << targetBoard[targetrow][targetcol] << "\trow: " << targetrow << "\tcol: " << targetcol << endl;
							count += (abs(targetrow - i) + abs(targetcol - j));
							//cout << (abs(targetrow - i) + abs(targetcol - j)) << endl;
						}
					}
				}
			}
		}
	}

	return count;
}

// HEURISTIC THREE: Count amount of tile swaps with blank tile
//				This function finds the heuristic value by
//				performing tile swaps with the blank tile and 
//				the tile whose target position it is in OR
//				moving with a random out of place tile if
//				blank tile is in its own goal state and returning
//				total moves.
// PARAMETERS:	board[][] - current board state
//				targetBoard[][] - target board state
// OUTPUT:		int - heuristic value
int countingTileSwapsWithBlank(char board[][3], char targetBoard[][3]) {
	int count = 0;
	bool victory = checkForWin(board, targetBoard);
	int rowOne = 0;
	int colOne = 0;
	int rowTwo = 0;
	int colTwo = 0;
	bool outOfPlace = false;
	bool inPlace = false;
	char targetTile = ' ';
	char placeholderTile = ' ';

	// Setup Temp Board to check with
	char tempBoard[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}

	// Blank Tile swap loop
	while (!victory) {
		outOfPlace = false;
		inPlace = false;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tempBoard[i][j] != targetBoard[i][j] && !(tempBoard[i][j] >= '1' && tempBoard[i][j] <= '8')) {
					rowOne = i;
					colOne = j;
					targetTile = targetBoard[i][j];
					outOfPlace = true;
				}
				if (tempBoard[i][j] == targetBoard[i][j] && !(tempBoard[i][j] >= '1' && tempBoard[i][j] <= '8')) {
					rowOne = i;
					colOne = j;
					inPlace = true;
				}
			}
		}

		// If Blank tile is out of target position
		if (outOfPlace) {
			// Find target tile position on initial board
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (tempBoard[i][j] == targetTile) {
						rowTwo = i;
						colTwo = j;
					}
				}
			}

			// Swap blank and target tile
			placeholderTile = tempBoard[rowOne][colOne];
			tempBoard[rowOne][colOne] = tempBoard[rowTwo][colTwo];
			tempBoard[rowTwo][colTwo] = placeholderTile;
		}


		// If blank tile is in target position
		if (inPlace) {
			// Grab out of place tile
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (tempBoard[i][j] != targetBoard[i][j] && (tempBoard[i][j] >= '1' && tempBoard[i][j] <= '8')) {
						rowTwo = i;
						colTwo = j;
					}
				}
			}

			// Swap blank and target tile
			placeholderTile = tempBoard[rowOne][colOne];
			tempBoard[rowOne][colOne] = tempBoard[rowTwo][colTwo];
			tempBoard[rowTwo][colTwo] = placeholderTile;
		}

		count++;
		victory = checkForWin(tempBoard, targetBoard);
	}

	return count;
}