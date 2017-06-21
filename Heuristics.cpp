#include "Heuristics.h"



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

	// setup temp
	char tempBoard[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}

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

		if (outOfPlace) {
			// find target tile position on initial board
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


		// swap blank with random out of place tile
		if (inPlace) {
			// grab out of place tile
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

		// Test print steps to swaps to finish
		//printBoard(tempBoard);
		//cout << endl;


		count++;
		victory = checkForWin(tempBoard, targetBoard);
	}

	return count;
}