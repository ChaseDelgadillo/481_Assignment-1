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