#include "Tools.h"

void convert1DTo2DBoard(char state[10], char(&board)[3][3]) {
	int temprow = -1;
	int tempcol = 0;

	for (int i = 0; i < 9; i++) {
		tempcol = i % 3;
		if (tempcol == 0) {
			temprow++;
		}

		//cout << "[" << temprow << "][" << tempcol << "]" << endl;
		board[temprow][tempcol] = state[i];
	}
}

void convert2DTo1DBoard(char board[3][3], char(&state)[10]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state[((i * 3) + j)] = board[i][j];
		}
	}
}


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

void printBoard(char board1[][3]) {
	ofstream outfile("out.txt", ios::app);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			outfile << board1[i][j] << ' ';
		}
		outfile << endl;
	}
}