#include "maze.hpp"

#include <stdexcept>

void Maze::solveMaze ()
{

	const int startX = 0;
	const int startY = 0;

	const int endX = m_gridWidth - 1;
	const int endY = m_gridHeight - 1;


	calcNeighbors();


	m_grid.at(endY).at(endX).solutionDist = 0;


	bool searchComplete = false;
	while (!searchComplete)
	{

		for (int row = 0; row < m_gridHeight; ++row)
		{
			for (int col = 0; col < m_gridWidth; ++col)
			{



				block &curBlock = m_grid.at(row).at(col);

				if (curBlock.solutionDist != -1) continue;


				int leastNeighboringDist = m_gridHeight * m_gridWidth;

				for (int i = 0; i < curBlock.neighbors.size(); ++i)
				{

					block* neighbor = curBlock.neighbors.at(i);

					if (neighbor->solutionDist != -1 && neighbor->solutionDist < leastNeighboringDist)
					{
						leastNeighboringDist = neighbor->solutionDist;
					}

				}

				if (leastNeighboringDist < m_gridHeight * m_gridWidth)
				{

					curBlock.solutionDist = leastNeighboringDist + 1;

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




	int headX = startX;
	int headY = startY;

	bool pathComplete = false;
	while (!pathComplete)
	{

		block &headBlock = m_grid.at(headY).at(headX);

		for (int i = 0; i < headBlock.neighbors.size(); ++i)
		{

			block* neighbor = headBlock.neighbors.at(i);

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



			if (neighbor->solutionDist == 0)
			{
				pathComplete = true;
				break;
			}


		}

	}

}




void Maze::calcNeighbors ()
{

	for (int row = 0; row < m_gridHeight; ++row)
	{

		for (int col = 0; col < m_gridWidth; ++col)
		{

			block &curBlock = m_grid.at(row).at(col);

			block* other;

			//no need to check for blocks pointing out of the border, because that is impossible
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
