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

	game.printBoard(game.initBoard);
	cout << endl;
	game.printBoard(game.targetBoard);

	cout << endl;
	int hOneCount = game.countingTileSwapsWithBlank();

	cout << hOneCount << endl;

	cout << "Win: " << game.checkForWin(game.initBoard, game.targetBoard) << endl;

	infile.close();
}