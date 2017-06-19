#include "EightPuzzle.h"


EightPuzzle::EightPuzzle(){
}


EightPuzzle::~EightPuzzle() {
}

int EightPuzzle::countingTilesOutOfPlace() {
	int count = 0; 

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (initBoard[i][j] != targetBoard[i][j] && (initBoard[i][j] >= '1' && initBoard[i][j] <='8')) {
				count++;
			}
		}
	}

	return count;
}

int EightPuzzle::distanceTilesOutOfPlace() {
	int count = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (initBoard[i][j] != targetBoard[i][j] && (initBoard[i][j] >= '1' && initBoard[i][j] <= '8')) {
				//cout << "out of place : " << initBoard[i][j] << "\trow: " << i << "\tcol: " << j << endl;
				for (int targetrow = 0; targetrow < 3; targetrow++) {
					for (int targetcol = 0; targetcol < 3; targetcol++) {
						if (targetBoard[targetrow][targetcol] == initBoard[i][j]) {
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

int EightPuzzle::countingTileSwapsWithBlank() {
	int count = 0;
	bool victory = false;
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
			tempBoard[i][j] = initBoard[i][j];
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


		printBoard(tempBoard);
		cout << endl;


		count++;
		victory = checkForWin(tempBoard, targetBoard);
	}

	return count;
}

//Steepest Hill Climb
void EightPuzzle::steepestHillClimb(int heuristic) {
	bool victory = checkForWin(initBoard, targetBoard);

	//
	//victory = checkForWin
	//
	//while (not solved && steps < 100)
	//
	//	array store 4 heuristic values of directions
	//
	//for i, j of temp
	//find blank
	//if i > 0 && previous not DOWN
	//up
	//array[0] = childTraverse(temp, target, UP)
	//if i < 2 && previous not UP
	//	down
	//	array[1] = childTraverse(temp, target, DOWN)
	//if j > 0 && previous not RIGHT
	//left
	//if j < 2 && previous not LEFT
	//	right
	//	int bestHeur = 100
	//for i -> 4
	//if array[i] < bestHeur
	//	bestHeur = array[i]
	//	index = direction
	//
	//	makeMove(temp, direction)
	//
	//	print temp board
	//	checkForWin
}


//	childTraverse(init, target, dir)
int EightPuzzle::checkChildHeuristic(int direction) {
	//
	//	create temp
	//	makeMove(temp, dir)
	//	print temp
	//	check heur of temp
	//	return heuristic value
}


//	makeMove(board, dir)
void EightPuzzle::moveTile(char board[][3], int direction) {
	//
	//	moveMade = false
	//for i, j
	//find blank
	//if UP
	//swap
	//moveMade = true
	//else if DOWN
	//...
	//else
	//...
	//if moveMade : break
}


bool EightPuzzle::checkForWin(char board1[][3], char board2[][3]) {
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

void EightPuzzle::printBoard(char board1[][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << board1[i][j] << ' ';
		}
		cout << endl;
	}
}