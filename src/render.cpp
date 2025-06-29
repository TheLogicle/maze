#include "maze.hpp"

#include <SDL3/SDL.h>


void Maze::render ()
{

	drawMazeGrid();
	drawBorder();


	SDL_RenderPresent(m_renderer);

}


void Maze::drawBorder ()
{

	float borderLeftX = m_padPixels + 1;
	float borderRightX = m_winWidth - m_padPixels - 1;
	float borderTopY = m_padPixels + 1;
	float borderBottomY = m_winHeight - m_padPixels - 1;
	float borderWidth = borderRightX - borderLeftX;
	float borderHeight = borderBottomY - borderTopY;

	float thickness = 8;

	SDL_FRect borderRects[]
	{
		{
			.x = borderLeftX - thickness,
			.y = borderTopY - thickness,
			.w = borderWidth + 2 * thickness,
			.h = thickness
		},
		{
			.x = borderLeftX - thickness,
			.y = borderBottomY,
			.w = borderWidth + 2 * thickness,
			.h = thickness
		},
		{
			.x = borderLeftX - thickness,
			.y = borderTopY,
			.w = thickness,
			.h = borderHeight
		},
		{
			.x = borderRightX,
			.y = borderTopY,
			.w = thickness,
			.h = borderHeight
		}
	};


	SDL_SetRenderDrawColorFloat(m_renderer, 0.4, 0.4, 0.4, 1);
	SDL_RenderFillRects(m_renderer, borderRects, 4);


}


void Maze::drawMazeGrid ()
{
	SDL_SetRenderDrawColorFloat(m_renderer, 0.5, 0.5, 1, 1);


	for (int row = 0; row < m_gridHeight; ++row)
	{

		auto &curRow = m_grid.at(row);

		for (int col = 0; col < m_gridWidth; ++col)
		{

			SDL_FPoint cornerPts[]
			{
				getBlockCornerPos(BOTTOM_LEFT, col, row),
				getBlockCornerPos(BOTTOM_RIGHT, col, row),
				getBlockCornerPos(TOP_RIGHT, col, row)
			};


			SDL_RenderLines(m_renderer, cornerPts, 3);


			//process to make lines 2 pixels thick
			for (int i = 0; i < 3; ++i)
			{
				cornerPts[i] = cornerPts[i] + SDL_FPoint{.x = 1, .y = 1};
			}


			SDL_RenderLines(m_renderer, cornerPts, 3);

		}

	}


}




