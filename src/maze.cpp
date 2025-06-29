#include "maze.hpp"

#include <SDL3/SDL.h>


Maze::Maze (int gridWidth, int gridHeight, int blockPixelSize, int padPixels)
	: m_padPixels {padPixels},
		m_blockPixelSize {blockPixelSize},

		m_winWidth {gridWidth * blockPixelSize + 2 * padPixels},
		m_winHeight {gridHeight * blockPixelSize + 2 * padPixels},

		m_gridWidth {gridWidth},
		m_gridHeight {gridHeight},

		m_running {false}
{

	prepareGrid();

	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("Maze", m_winWidth, m_winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);

}


Maze::~Maze ()
{

	SDL_Quit();

}



// prepare the grid with the default "perfect maze"
void Maze::prepareGrid ()
{

	m_grid = std::vector<blockRow>(m_gridHeight - 1, blockRow(m_gridWidth, block{.pointsTo = Maze::DOWN}));
	m_grid.push_back(blockRow(m_gridWidth, block{.pointsTo = Maze::RIGHT}));

	for (int row = 0; row < m_gridHeight; ++row)
	{
		for (int col = 0; col < m_gridWidth; ++col)
		{
			block &curBlock = m_grid.at(row).at(col);

			curBlock.row = row;
			curBlock.col = col;
		}
	}



}
