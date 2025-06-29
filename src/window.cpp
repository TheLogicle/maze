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

		m_running {false},

		m_grid (std::vector<blockRow>(gridHeight, blockRow(gridWidth)))
{



	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow("Maze", m_winWidth, m_winHeight, 0);

	m_renderer = SDL_CreateRenderer(m_window, 0);

}



