#include "hw1.h"

int main() {
	ifstream infile("in.txt");
	EightPuzzle game;

	if (infile.is_open()) {
		char c;
		int i = 0;
		int j = 0;

		while (infile.get(c)) {
			if (c == '\n') {
				i++;
				j = 0;
				//cout << i << endl;
			}
			else if (c == ' ') {
				j++;
				//cout << j << ' ';
			}
			else {
				if (i < 4)
					game.initBoard[i][j] = c;
				else
					game.targetBoard[i - 4][j] = c;
				//cout << c;
			}
		}
	}


	for (int i = 1; i <= 3; i++) {
		cout << "========================================" << endl;
		cout << "========================================" << endl;
		cout << "Algorithm: Steepest-descent hill-climbing" << endl;
		cout << "Heuristic function: ";
		switch (i) {
		case 1:
			cout << "countingTilesOutOfPlace()" << endl;
			break;
		case 2:
			cout << "distanceTilesOutOfPlace()" << endl;
			break;
		case 3:
			cout << "countingTileSwapsWithBlank()" << endl;
			break;
		default:
			cout << "Invalid heuristic" << endl;
		}
		cout << "----------------------------------------" << endl;
		cout << "Initial board state: " << endl;
		game.printBoard(game.initBoard);
		cout << "--------------------" << endl;
		game.steepestHillClimb(i);
	}

	for (int i = 1; i <= 3; i++) {
		cout << "========================================" << endl;
		cout << "========================================" << endl;
		cout << "Algorithm: Best-First Search" << endl;
		cout << "Heuristic function: ";
		switch (i) {
		case 1:
			cout << "countingTilesOutOfPlace()" << endl;
			break;
		case 2:
			cout << "distanceTilesOutOfPlace()" << endl;
			break;
		case 3:
			cout << "countingTileSwapsWithBlank()" << endl;
			break;
		default:
			cout << "Invalid heuristic" << endl;
		}
		cout << "----------------------------------------" << endl;
		cout << "Initial board state: " << endl;
		game.bestFirstSearch(i);
	}


	infile.close();
}