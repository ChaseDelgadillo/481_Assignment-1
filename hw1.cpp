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
#include "hw1.h"

int main() {
	cout << "Running CPSC-481 Assignment 1\n\tBy Chase Delgadillo & Dennis Wu\n" << endl;
	ifstream infile("in.txt");
	remove("out.txt");
	ofstream outfile("out.txt", ios::app);
	EightPuzzle game;

	// Parse input file for the initial board state and target board state
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

	// ALGORITHM 1: Steepest-descent hill-climbing
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
		game.steepestHillClimb(i);
	}

	// ALGORITHM 2: Best-First Search
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
		game.bestFirstSearch(i);
	}


	infile.close();
	outfile.close();
}
