#include "maze.hpp"


// origin shift algorithm
void Maze::generateMaze ()
{

	int headX = 0;
	int headY = 0;

	// seems like a good enough number of iterations
	int iters = m_gridWidth * m_gridHeight * 500;

	for (int i = 0; i < iters; ++i)
	{
		// pick a random direction
		direction headDir = (direction) SDL_rand(4);


		// skip if cannot advance in that direction
		if (
			headDir == UP && headY == 0 ||
			headDir == LEFT && headX == 0 ||
			headDir == DOWN && headY == m_gridHeight - 1 ||
			headDir == RIGHT && headX == m_gridWidth - 1
		)
		{
			continue;
		}


		// this is the current "origin" block
		block &headBlock = m_grid.at(headY).at(headX);

		// set new origin pointer
		headBlock.pointsTo = headDir;

		// change which block is now the origin
		switch (headDir)
		{
			case UP:
				--headY;
				break;
			case DOWN:
				++headY;
				break;
			case LEFT:
				--headX;
				break;
			case RIGHT:
				++headX;
				break;
		}


	}



}
