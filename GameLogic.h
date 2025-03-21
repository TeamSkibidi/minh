#pragma once
#include "GridGame.h"
#include "TitleQueue.h"

void random_pos(vector<vector<int>>& boardgame);

void goup(GridGame& grid);  // function move up
void godown(GridGame& grid);  // function move down
void turnleft(GridGame& grid);  // function move left
void turnright(GridGame& grid);  // function move right