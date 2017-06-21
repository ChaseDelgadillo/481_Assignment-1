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
#include "EightPuzzle.h"

EightPuzzle::EightPuzzle(){
}


EightPuzzle::~EightPuzzle() {
}

// ALGORITHM 1: Steepest-descent hill-climbing
//		This function uses Steepest-descent hill-climbing
//		to calculate best path using given heuristic
// PARAMETERS:	heuristic - integer value that represents
//							the desired heuristic (1-3)
// OUTPUT:		void
void EightPuzzle::steepestHillClimb(int heuristic) {
	ofstream outfile("out.txt", ios::app);
	bool victory = checkForWin(initBoard, targetBoard);
	string thePath[100];
	int steps = 0;
	int lastMove = -1;
	int nextMove = -1;

	// Setup Temp Board to check with
	char tempBoard[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempBoard[i][j] = initBoard[i][j];
		}
	}

	char initState[10] = { 0 };
	convert2DTo1DBoard(initBoard, initState);

	thePath[0] = initState;

	// WHILE (not solved && steps < max desired)
	while (!victory && steps < 100) {
		steps++;

		// heuristic values of directions
		//					N    S    E    W
		int dirheur[4] = { 100, 100, 100, 100 };

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!(tempBoard[i][j] >= '1' && tempBoard[i][j] <= '8')) {
					// Check swap NORTH
					if (i > 0 && lastMove != SOUTH) {
						dirheur[NORTH] = checkChildHeuristic(tempBoard, NORTH, heuristic);
					}

					// Check swap SOUTH
					if (i < 2 && lastMove != NORTH) {
						dirheur[SOUTH] = checkChildHeuristic(tempBoard, SOUTH, heuristic);
					}

					// Check swap EAST
					if (j < 2 && lastMove != WEST) {
						dirheur[EAST] = checkChildHeuristic(tempBoard, EAST, heuristic);
					}

					// Check swap WEST
					if (j > 0 && lastMove != EAST) {
						dirheur[WEST] = checkChildHeuristic(tempBoard, WEST, heuristic);
					}
				}
			}
		}

		int bestHeur = 100;
		for (int i = 0; i < (sizeof(dirheur) / sizeof(dirheur[0])); i++) {
			if (dirheur[i] < bestHeur) {
				//cout << "UPDATE HEURISTIC BEST: " << dirheur[i] << "\tDIR: " << i << endl;
				bestHeur = dirheur[i];
				nextMove = i;
			}
		}

		// Move tile based on best move (lowest heuristic value)
		moveTile(tempBoard, nextMove);

		// Add new move to path
		char tempState[10] = { 0 };
		convert2DTo1DBoard(tempBoard, tempState);

		if (steps < 100)
			thePath[steps] = tempState;

		lastMove = nextMove;
		victory = checkForWin(tempBoard, targetBoard);
	}

	// Print steps and path if viable
	if (steps < 100) {
		outfile << "Number of steps: " << steps << endl;

		for (int i = 0; i <= steps; i += 5) {
			if (!thePath[i + 4].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << "\t" << thePath[i + 3].substr(0, 3) << "\t" << thePath[i + 4].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << "\t" << thePath[i + 3].substr(3, 3) << "\t" << thePath[i + 4].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << "\t" << thePath[i + 3].substr(6, 3) << "\t" << thePath[i + 4].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 3].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << "\t" << thePath[i + 3].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << "\t" << thePath[i + 3].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << "\t" << thePath[i + 3].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 2].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 1].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << endl;
				outfile << endl;
			}
			else {
				outfile << thePath[i].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << endl;
				outfile << endl;
			}
		}
	}
	else {
		outfile << "Unable to find a solution." << endl;
	}
}


// TOOL: Evaluate Child Board
//			This function evaluates given board
//			towards given direction using the 
//			desired heuristic.
// PARAMETERS:	board - char[][] of desired board to check
//				direction - integer of desired direction 
//							to check (0-3)
//				heuristic - integer value that represents
//							the desired heuristic (1-3)
// OUTPUT:		int - heuristic value
int EightPuzzle::checkChildHeuristic(char board[][3], int direction, int heuristic) {
	int value = 100;

	// Setup Temp Board to check with
	char tempBoard[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tempBoard[i][j] = board[i][j];
		}
	}

	// Swap board to desired direction state
	moveTile(tempBoard, direction);

	// Check heuristic value of board by given heuristic
	switch (heuristic) {
	case 1:
		value = countingTilesOutOfPlace(tempBoard, targetBoard);
		break;
	case 2:
		value = distanceTilesOutOfPlace(tempBoard, targetBoard);
		break;
	case 3:
		value = countingTileSwapsWithBlank(tempBoard, targetBoard);
		break;
	default:
		cout << "No heuristic given" << endl;
	}

	// Test child board state
	//printBoard(tempBoard);

	//	return heuristic value
	//cout << "CHILD DIRECTION: " << direction << "\tVALUE: " << value << endl;
	return value;
}


// TOOL: Move Tile
//			This function swaps blank tile on board in 
//			given direction.
// PARAMETERS:	board - char[][] of desired board to move in
//				direction - integer of desired direction
//							to check (0-3)
// OUTPUT:		void
void EightPuzzle::moveTile(char(&board)[3][3], int direction) {
	bool moveMade = false;
	char placeholderTile = ' ';

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (moveMade) {
				break;
			}
			// Blank Tile Found for moving
			if (!(board[i][j] >= '1' && board[i][j] <= '8')) {
				// Move based off selected direction
				if (direction == NORTH) {
					// swap with tile [row-1][]
					// hold blank
					placeholderTile = board[i][j];
					// set blank = tile in correct direction
					board[i][j] = board[i - 1][j];
					// set tile in correct direction = blank(placeholder)
					board[i - 1][j] = placeholderTile;

					moveMade = true;
				}
				if (direction == SOUTH) {
					// swap with tile[row+1][]
					// hold blank
					placeholderTile = board[i][j];
					// set blank = tile in correct direction
					board[i][j] = board[i + 1][j];
					// set tile in correct direction = blank(placeholder)
					board[i + 1][j] = placeholderTile;

					moveMade = true;
				}
				if (direction == EAST) {
					// swap with tile[][col+1]
					// hold blank
					placeholderTile = board[i][j];
					// set blank = tile in correct direction
					board[i][j] = board[i][j + 1];
					// set tile in correct direction = blank(placeholder)
					board[i][j + 1] = placeholderTile;

					moveMade = true;
				}
				if (direction == WEST) {
					// swap with tile[][col-1]
					// hold blank
					placeholderTile = board[i][j];
					// set blank = tile in correct direction
					board[i][j] = board[i][j - 1];
					// set tile in correct direction = blank(placeholder)
					board[i][j - 1] = placeholderTile;

					moveMade = true;
				}
			}
		}
	}
}

// ALGORITHM 2: Best-First Search
//				This function uses Best-First Search to
//				calculate best path using given heuristic.
// PARAMETERS:	heuristic - integer value that represents
//							the desired heuristic (1-3).
// OUTPUT:		void
void EightPuzzle::bestFirstSearch(int heuristic) {
	ofstream outfile("out.txt", ios::app);
	int steps = 0;
	string thePath[100];

	// Convert initial state to 1d array
	char initialState[10] = { 0 };
	convert2DTo1DBoard(initBoard, initialState);

	// Convert goal state to 1d array
	char targetState[10] = { 0 };
	convert2DTo1DBoard(targetBoard, targetState);

	// Open :: key-value map
	pair<string, int> openPair;
	map<string, int> open;
	map<string, int>::iterator it = open.begin();

	// Closed :: vector of strings
	vector<string> closed;

	// Get initial state value
	int initialValue = 100;
	switch (heuristic) {
	case 1:
		initialValue = countingTilesOutOfPlace(initBoard, targetBoard);
		break;
	case 2:
		initialValue = distanceTilesOutOfPlace(initBoard, targetBoard);
		break;
	case 3:
		initialValue = countingTileSwapsWithBlank(initBoard, targetBoard);
		break;
	default:
		cout << "No heuristic given" << endl;
	}

	// Add start to open
	openPair.first = initialState;
	openPair.second = initialValue;
	open.insert(openPair);

	bool victory = checkForWin(initBoard, targetBoard);
	int newStepMin = 0;

	// Best-First Search loop
	while (!open.empty() && steps < 100) {
		steps++;

		string lowestKey = "";
		int lowestValue = 100;
		for (it = open.begin(); it != open.end(); it++) {
			if ((*it).second < lowestValue) {
				lowestKey = (*it).first;
				lowestValue = (*it).second;
			}
		}

		// Remove lowest key
		it = open.find(lowestKey);
		open.erase(it);

		// New Parent State 2D
		char newParentState[3][3];

		// New Parent State String to Char Array
		char newPSCArr[10] = { 0 };
		for (int i = 0; i < 9; i++) {
			newPSCArr[i] = lowestKey[i];
		}

		// Convert Char Array to 2D
		convert1DTo2DBoard(newPSCArr, newParentState);

		// Add state to path
		if (steps < 100)
			thePath[steps] = newPSCArr;

		// Check for victory state
		if (checkForWin(newParentState, targetBoard)) {
			break;
		}
		else {
			bool childOpenFlag = false;
			bool childClosedFlag = false;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					// Find blank tile
					if (!(newParentState[i][j] >= '1' && newParentState[i][j] <= '8')) {
						char tempChildBoard[3][3];
						char tempChildState[10] = { 0 };

						// Check swap NORTH
						if (i > 0) {
							for (int x = 0; x < 3; x++) {
								for (int y = 0; y < 3; y++) {
									tempChildBoard[x][y] = newParentState[x][y];
								}
							}

							moveTile(tempChildBoard, NORTH);

							childOpenFlag = false;
							childClosedFlag = false;

							// Convert 2d to 1d
							convert2DTo1DBoard(tempChildBoard, tempChildState);

							// Search Open Map
							if (open.find(tempChildState) == open.end()) {
								// not found
								childOpenFlag = false;
							}
							else {
								// found
								childOpenFlag = true;
							}

							// Search Closed Vector
							if (std::find(closed.begin(), closed.end(), tempChildState) != closed.end()) {
								// found
								childClosedFlag = true;
							}
							else {
								// not found
								childClosedFlag = false;
							}

							// Act based on if child is in open or closed
							if (!childOpenFlag && !childClosedFlag) {
								// Assign child heuristic value
								int childValue = 100;
								switch (heuristic) {
								case 1:
									childValue = countingTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 2:
									childValue = distanceTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 3:
									childValue = countingTileSwapsWithBlank(tempChildBoard, targetBoard);
									break;
								default:
									cout << "No heuristic given" << endl;
								}

								// Add child to open
								openPair.first = tempChildState;
								openPair.second = childValue;
								open.insert(openPair);

							}
							if (childOpenFlag) {
								// If child reached by shorter path
								//		update to new low path value
								if (steps < newStepMin) {
									newStepMin = steps;
								}
							}
						}

						// Check swap SOUTH
						if (i < 2) {
							for (int x = 0; x < 3; x++) {
								for (int y = 0; y < 3; y++) {
									tempChildBoard[x][y] = newParentState[x][y];
								}
							}

							moveTile(tempChildBoard, SOUTH);

							childOpenFlag = false;
							childClosedFlag = false;

							// Convert 2d to 1d
							convert2DTo1DBoard(tempChildBoard, tempChildState);

							// Search Open Map
							if (open.find(tempChildState) == open.end()) {
								// not found
								childOpenFlag = false;
							}
							else {
								// found
								childOpenFlag = true;
							}

							// Search Closed Vector
							if (std::find(closed.begin(), closed.end(), tempChildState) != closed.end()) {
								// found
								childClosedFlag = true;
							}
							else {
								// not found
								childClosedFlag = false;
							}

							// Act based on if child is in open or closed
							if (!childOpenFlag && !childClosedFlag) {
								// Assign child heuristic value
								int childValue = 100;
								switch (heuristic) {
								case 1:
									childValue = countingTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 2:
									childValue = distanceTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 3:
									childValue = countingTileSwapsWithBlank(tempChildBoard, targetBoard);
									break;
								default:
									cout << "No heuristic given" << endl;
								}
								// Add child to open
								openPair.first = tempChildState;
								openPair.second = childValue;
								open.insert(openPair);

							}
							if (childOpenFlag) {
								// If child reached by shorter path
								//		update to new low path value
								if (steps < newStepMin) {
									newStepMin = steps;
								}
							}
						}

						// Check swap EAST
						if (j < 2) {
							for (int x = 0; x < 3; x++) {
								for (int y = 0; y < 3; y++) {
									tempChildBoard[x][y] = newParentState[x][y];
								}
							}

							moveTile(tempChildBoard, EAST);

							childOpenFlag = false;
							childClosedFlag = false;

							// Convert 2d to 1d
							convert2DTo1DBoard(tempChildBoard, tempChildState);

							// Search Open Map
							if (open.find(tempChildState) == open.end()) {
								// not found
								childOpenFlag = false;
							}
							else {
								// found
								childOpenFlag = true;
							}

							// Search Closed Vector
							if (std::find(closed.begin(), closed.end(), tempChildState) != closed.end()) {
								// found
								childClosedFlag = true;
							}
							else {
								// not found
								childClosedFlag = false;
							}

							// Act based on if child is in open or closed
							if (!childOpenFlag && !childClosedFlag) {
								// Assign child heuristic value
								int childValue = 100;
								switch (heuristic) {
								case 1:
									childValue = countingTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 2:
									childValue = distanceTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 3:
									childValue = countingTileSwapsWithBlank(tempChildBoard, targetBoard);
									break;
								default:
									cout << "No heuristic given" << endl;
								}
								// Add child to open
								openPair.first = tempChildState;
								openPair.second = childValue;
								open.insert(openPair);

							}
							if (childOpenFlag) {
								// If child reached by shorter path
								//		update to new low path value
								if (steps < newStepMin) {
									newStepMin = steps;
								}
							}
						}

						// Check swap WEST
						if (j > 0) {
							for (int x = 0; x < 3; x++) {
								for (int y = 0; y < 3; y++) {
									tempChildBoard[x][y] = newParentState[x][y];
								}
							}

							moveTile(tempChildBoard, WEST);

							childOpenFlag = false;
							childClosedFlag = false;

							// Convert 2d to 1d
							convert2DTo1DBoard(tempChildBoard, tempChildState);

							// Search Open Map
							if (open.find(tempChildState) == open.end()) {
								// not found
								childOpenFlag = false;
							}
							else {
								// found
								childOpenFlag = true;
							}

							// Search Closed Vector
							if (std::find(closed.begin(), closed.end(), tempChildState) != closed.end()) {
								// found
								childClosedFlag = true;
							}
							else {
								// not found
								childClosedFlag = false;
							}

							// Act based on if child is in open or closed
							if (!childOpenFlag && !childClosedFlag) {
								// Assign child heuristic value
								int childValue = 100;
								switch (heuristic) {
								case 1:
									childValue = countingTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 2:
									childValue = distanceTilesOutOfPlace(tempChildBoard, targetBoard);
									break;
								case 3:
									childValue = countingTileSwapsWithBlank(tempChildBoard, targetBoard);
									break;
								default:
									cout << "No heuristic given" << endl;
								}
								// Add child to open
								openPair.first = tempChildState;
								openPair.second = childValue;
								open.insert(openPair);

							}
							if (childOpenFlag) {
								// If child reached by shorter path
								//		update to new low path value
								if (steps < newStepMin) {
									newStepMin = steps;
								}
							}
						}
					}
				}
			}
		}
		// Put parent in closed
		closed.push_back(newPSCArr);
	}

	// Print steps and path if viable
	if (steps < 100) {
		outfile << "Number of steps: " << steps - 1 << endl;

		for (int i = 1; i <= steps; i += 5) {
			if (!thePath[i + 4].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << "\t" << thePath[i + 3].substr(0, 3) << "\t" << thePath[i + 4].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << "\t" << thePath[i + 3].substr(3, 3) << "\t" << thePath[i + 4].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << "\t" << thePath[i + 3].substr(6, 3) << "\t" << thePath[i + 4].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 3].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << "\t" << thePath[i + 3].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << "\t" << thePath[i + 3].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << "\t" << thePath[i + 3].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 2].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << "\t" << thePath[i + 2].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << "\t" << thePath[i + 2].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << "\t" << thePath[i + 2].substr(6, 3) << endl;
				outfile << endl;
			}
			else if (!thePath[i + 1].empty()) {
				outfile << thePath[i].substr(0, 3) << "\t" << thePath[i + 1].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << "\t" << thePath[i + 1].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << "\t" << thePath[i + 1].substr(6, 3) << endl;
				outfile << endl;
			}
			else {
				outfile << thePath[i].substr(0, 3) << endl;
				outfile << thePath[i].substr(3, 3) << endl;
				outfile << thePath[i].substr(6, 3) << endl;
				outfile << endl;
			}
		}
	}
	else {
		outfile << "Unable to find a solution." << endl;
	}
}