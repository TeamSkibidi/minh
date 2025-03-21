#include "GameLogic.h"
#include "GridGame.h"

void random_pos(vector<vector<int>>& boardgame)
{
	// save the empty cells 
	vector<int> empty_cells;
	for (int i = 0; i < boardgame.size(); i++) {
		for (int j = 0; j < boardgame.size(); j++) {
			if (boardgame[i][j] == 0) {
				empty_cells.push_back(i);
				empty_cells.push_back(j);
			}
		}
	}
	// if has not empty cells, return 
	int empty_count = (empty_cells.size() / 2);
	if (empty_count == 0) return;
	// get number of cells want to random
	int num_cell = (empty_count > 1 && rand() % 2 == 0) ? 2 : 1;

	for (int i = 0; i < num_cell; i++) {
		int idx = rand() % empty_count;
		int x = empty_cells[idx * 2];
		int y = empty_cells[idx * 2 + 1];
		boardgame[x][y] = (rand() % 10 < 3) ? 4 : 2;
		// swap position x, y just been used for 2 last element 
		int lastIndex = empty_cells.size() - 2;
		empty_cells[idx * 2] = empty_cells[lastIndex];
		empty_cells[idx * 2 + 1] = empty_cells[lastIndex + 1];
		// remove 2 last element after swap
		empty_cells.pop_back();
		empty_cells.pop_back();
		empty_count--; // reduce the number of empty cells by 1
	}

}

void goup(GridGame& grid) {
	// browse each colums
	for (int j = 0; j < grid.getBoardGame().size(); j++) {
		TitleQueue queue;
		// take elements in colums j has value different 0 into queue (from top to bottom)
		for (int i = 0; i < grid.getBoardGame().size(); i++) {
			if (grid.getBoardGame()[i][j] != 0) {
				queue.push(grid.getBoardGame()[i][j]);
			}
		}

		int idx = 0;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			// peek continue value and merge if it the same
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				grid.setScore(grid.getScore() + value);
				queue.pop(); // remove element just peek
			}
			grid.getBoardGame()[idx++][j] = value;
		}
		// fill 0 into rest celss of colums
		while (idx < grid.getBoardGame().size()) grid.getBoardGame()[idx++][j] = 0;
	}

}

void godown(GridGame& grid) {
	// browse each colums
	for (int j = 0; j < grid.getBoardGame().size(); j++) {
		TitleQueue queue;
		// take elements in colums j has value different 0 into queue (from bottom to top)
		for (int i = grid.getBoardGame().size() - 1; i >= 0; i--) {
			if (grid.getBoardGame()[i][j] != 0) {
				queue.push(grid.getBoardGame()[i][j]);
			}
		}

		int idx = grid.getBoardGame().size() - 1;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				grid.setScore(grid.getScore() + value);
				queue.pop();
			}
			grid.getBoardGame()[idx--][j] = value;
		}
		// fill 0 into rest cells of colums
		while (idx >= 0) grid.getBoardGame()[idx--][j] = 0;

	}
}

void turnleft(GridGame& grid) {
	// browse each row
	for (int i = 0; i < grid.getBoardGame().size(); i++) {
		TitleQueue queue;
		// take element in row i has value different 0 into queue (from left to right)
		for (int j = 0; j < grid.getBoardGame().size(); j++) {
			if (grid.getBoardGame()[i][j] != 0) {
				queue.push(grid.getBoardGame()[i][j]);
			}
		}
		int idx = 0;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue not empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				grid.setScore(grid.getScore() + value);
				queue.pop(); // remove element just peek
			}
			grid.getBoardGame()[i][idx++] = value;
		}
		// fill value 0 into rest cells
		while (idx < grid.getBoardGame().size()) grid.getBoardGame()[i][idx++] = 0;

	}
}

void turnright(GridGame& grid) {
	// browse each row
	for (int i = 0; i < grid.getBoardGame().size(); i++) {
		TitleQueue queue;
		// take element in row i has value different 0 into queue (from right to left)
		for (int j = grid.getBoardGame().size() - 1; j >= 0; j--) {
			if (grid.getBoardGame()[i][j] != 0) {
				queue.push(grid.getBoardGame()[i][j]);
			}
		}

		int idx = grid.getBoardGame().size() - 1;
		// take each element in order of priority and merge if consecutive elements the same
		while (!queue.checkempty()) { // if queue empty then run
			int value = queue.pop();
			if (!queue.checkempty() && queue.peek() == value) {
				value *= 2;
				grid.setScore(grid.getScore() + value);
				queue.pop(); // remove element just peek
			}
			grid.getBoardGame()[i][idx--] = value;
		}
		// fill value 0 into rest cells 
		while (idx >= 0) grid.getBoardGame()[i][idx--] = 0;
	}
}
