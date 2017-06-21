#pragma once
#include <iostream>
#include <fstream>
using namespace std;

// Convert 1D to 2D array
void convert1DTo2DBoard(char state[10], char(&board)[3][3]);

// Convert 2D to 1D array
void convert2DTo1DBoard(char board[3][3], char(&state)[10]);

// Check for Win
bool checkForWin(char board1[][3], char board2[][3]);

// Print the initial board state
void printBoard(char board1[][3]);