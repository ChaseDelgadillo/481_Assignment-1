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
#include "Tools.h"

// TOOL: Convert 1D Board to 2D Board
//			This function is used for converting
//			a given 1D board to 2D array by reference.
// PARAMETERS:	state[] - char 1D array board state
//				board[][] - char 2D array board
// OUTPUT:		void
void convert1DTo2DBoard(char state[10], char(&board)[3][3]) {
	int temprow = -1;
	int tempcol = 0;

	for (int i = 0; i < 9; i++) {
		tempcol = i % 3;
		if (tempcol == 0) {
			temprow++;
		}

		board[temprow][tempcol] = state[i];
	}
}

// TOOL: Convert 2D Board to 1D Board
//			This function is used for converting
//			a given 2D board to 1D array by reference.
// PARAMETERS:	board[][] - char 2D array board
//				state[] - char 1D array board state
// OUTPUT:		void
void convert2DTo1DBoard(char board[3][3], char(&state)[10]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state[((i * 3) + j)] = board[i][j];
		}
	}
}

// TOOL: Evaluate Win Condition
//			This function compares board1 to board2
//			to see if they are equal.
// PARAMETERS:	board1[][] - current board state
//				board2[][] - target board state
// OUTPUT:		bool - boolean [true = victory]
bool checkForWin(char board1[][3], char board2[][3]) {
	bool victory = true;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board1[i][j] != board2[i][j]) {
				victory = false;
			}
		}
	}

	return victory;
}

// TOOL: Print Board
//			This function is used for printing the given
//			board to the file.
// PARAMETERS:	board1[][] - current board state
// OUTPUT:		void
void printBoard(char board1[][3]) {
	ofstream outfile("out.txt", ios::app);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			outfile << board1[i][j] << ' ';
		}
		outfile << endl;
	}
}