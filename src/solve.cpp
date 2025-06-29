#include "maze.hpp"

#include <stdexcept>

// once the maze is generated, this algorithm will solve it
// not fully optimized, but it's such a light load that it doesn't matter
void Maze::solveMaze ()
{

	const int startX = 0;
	const int startY = 0;

	const int endX = m_gridWidth - 1;
	const int endY = m_gridHeight - 1;


	// calculate each block's neighbors (a.k.a. adjacent blocks without a wall in between)
	calcNeighbors();


	// set the seed at the end block, so the algorithm can "grow" from there until it reaches the start block
	m_grid.at(endY).at(endX).solutionDist = 0;


	// --- search phase
	// records path distance of each block from the end block
	bool searchComplete = false;
	while (!searchComplete)
	{

		for (int row = 0; row < m_gridHeight; ++row)
		{
			for (int col = 0; col < m_gridWidth; ++col)
			{



				block &curBlock = m_grid.at(row).at(col);

				// skip if the block already has a recorded distance
				if (curBlock.solutionDist != -1) continue;


				// the neighbor with the least recorded distance will be stored here
				// the total number of blocks is an impossible distance, so I set that as the initial value
				int leastNeighboringDist = m_gridHeight * m_gridWidth;

				for (int i = 0; i < curBlock.neighbors.size(); ++i)
				{

					block* neighbor = curBlock.neighbors.at(i);

					if (neighbor->solutionDist != -1 && neighbor->solutionDist < leastNeighboringDist)
					{
						leastNeighboringDist = neighbor->solutionDist;
					}

				}

				// if there was a neighbor with a recorded distance, record self's distance as one more than that
				if (leastNeighboringDist < m_gridHeight * m_gridWidth)
				{

					curBlock.solutionDist = leastNeighboringDist + 1;

					// search is complete once it reaches the start block
					// this means that a full path can now be calculated
					if (col == startX && row == startY)
					{
						searchComplete = true;
						break;
					}

				}



			}
			if (searchComplete) break;
		}


	}




	// --- path phase
	// use the recorded distances to calculate a path from start to end

	int headX = startX;
	int headY = startY;

	bool pathComplete = false;
	while (!pathComplete)
	{

		block &headBlock = m_grid.at(headY).at(headX);

		for (int i = 0; i < headBlock.neighbors.size(); ++i)
		{

			block* neighbor = headBlock.neighbors.at(i);

			// if there is a neighbor that has a lower distance than the head, direct the path to that neighbor
			if (neighbor->solutionDist != -1 && neighbor->solutionDist < headBlock.solutionDist)
			{

				headBlock.isSolution = true;

				if (neighbor->row == headBlock.row + 1) headBlock.solutionTo = DOWN;
				else if (neighbor->row == headBlock.row - 1) headBlock.solutionTo = UP;
				else if (neighbor->col == headBlock.col + 1) headBlock.solutionTo = RIGHT;
				else if (neighbor->col == headBlock.col - 1) headBlock.solutionTo = LEFT;
				else throw std::runtime_error("invalid neighbor");

				headX = neighbor->col;
				headY = neighbor->row;

			}



			// once the head reaches the end block, the full solution path is complete
			if (neighbor->solutionDist == 0)
			{
				pathComplete = true;
				break;
			}


		}

	}

}




// calculate each block's neighbors (a.k.a. adjacent blocks without a wall in between)
void Maze::calcNeighbors ()
{

	for (int row = 0; row < m_gridHeight; ++row)
	{

		for (int col = 0; col < m_gridWidth; ++col)
		{

			block &curBlock = m_grid.at(row).at(col);

			block* other;

			// check which block that the current one points to, and add both to each other's neighbor list
			// no need to check for blocks pointing out of the border, because that is impossible
			switch (curBlock.pointsTo)
			{

				case UP:
					other = &m_grid.at(row - 1).at(col);
					other->neighbors.push_back(&curBlock);
					break;

				case RIGHT:
					other = &m_grid.at(row).at(col + 1);
					other->neighbors.push_back(&curBlock);
					break;

				case DOWN:
					other = &m_grid.at(row + 1).at(col);
					other->neighbors.push_back(&curBlock);
					break;

				case LEFT:
					other = &m_grid.at(row).at(col - 1);
					other->neighbors.push_back(&curBlock);
					break;

			}

			curBlock.neighbors.push_back(other);

		}

	}

}
