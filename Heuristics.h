#pragma once
#include <math.h> 
#include <stdlib.h>
#include "Tools.h"

// Heuristic One: Count number of tiles out of place
int countingTilesOutOfPlace(char board[][3], char targetBoard[][3]);

// Heuristic Two: Measure distance of tiles out of place to correct position
int distanceTilesOutOfPlace(char board[][3], char targetBoard[][3]);

// Heuristic Three: Count number of swaps between blank space and tile that 
//					belongs in blank space's current index
int countingTileSwapsWithBlank(char board[][3], char targetBoard[][3]);
