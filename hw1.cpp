#include "hw1.h"

int main() {
	cout << "Running CPSC-481 Assigment 1\n\tBy Chase Delgadillo & Dennis Wu\n" << endl;
	ifstream infile("in.txt");
	remove("out.txt");
	ofstream outfile("out.txt", ios::app);
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
	
	// HEADER
	outfile << "========================================" << endl;
	outfile << "========================================" << endl;
	outfile << "CPSC-481 Assignment 1\nBy Chase Delgadillo & Dennis Wu" << endl;

	for (int i = 1; i <= 3; i++) {
		outfile << "========================================" << endl;
		outfile << "========================================" << endl;
		outfile << "Algorithm: Steepest-descent hill-climbing" << endl;
		outfile << "Heuristic function: ";
		switch (i) {
		case 1:
			outfile << "countingTilesOutOfPlace()" << endl;
			break;
		case 2:
			outfile << "distanceTilesOutOfPlace()" << endl;
			break;
		case 3:
			outfile << "countingTileSwapsWithBlank()" << endl;
			break;
		default:
			outfile << "Invalid heuristic" << endl;
		}
		outfile << "----------------------------------------" << endl;
		outfile << "Initial board state: " << endl;
		game.printBoard(game.initBoard);
		outfile << "--------------------" << endl;
		game.steepestHillClimb(i);
	}

	for (int i = 1; i <= 3; i++) {
		outfile << "========================================" << endl;
		outfile << "========================================" << endl;
		outfile << "Algorithm: Best-First Search" << endl;
		outfile << "Heuristic function: ";
		switch (i) {
		case 1:
			outfile << "countingTilesOutOfPlace()" << endl;
			break;
		case 2:
			outfile << "distanceTilesOutOfPlace()" << endl;
			break;
		case 3:
			outfile << "countingTileSwapsWithBlank()" << endl;
			break;
		default:
			outfile << "Invalid heuristic" << endl;
		}
		outfile << "----------------------------------------" << endl;
		outfile << "Initial board state: " << endl;
		game.bestFirstSearch(i);
	}


	infile.close();
	outfile.close();
}