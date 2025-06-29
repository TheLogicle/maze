#include "maze.hpp"

#include <SDL3/SDL.h>
#include <iostream>


Maze::Maze (int gridWidth, int gridHeight, int blockPixelSize, int padPixels)
	: m_padPixels {padPixels},
		m_blockPixelSize {blockPixelSize},

		m_winWidth {gridWidth * blockPixelSize + 2 * padPixels},
		m_winHeight {gridHeight * blockPixelSize + 2 * padPixels},

		m_gridWidth {gridWidth},
		m_gridHeight {gridHeight},

		m_running {false}
{
	
	//prepare the grid with the default "perfect maze"
	m_grid = std::vector<blockRow>(gridHeight - 1, blockRow(gridWidth, block{.pointsTo = Maze::DOWN}));
	m_grid.push_back(blockRow(gridWidth, block{.pointsTo = Maze::RIGHT}));

	for (int row = 0; row < gridHeight; ++row)
	{
		for (int col = 0; col < gridWidth; ++col)
		{
			block &curBlock = m_grid.at(row).at(col);

			curBlock.row = row;
			curBlock.col = col;
		}
	}



	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("Maze", m_winWidth, m_winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);

}



