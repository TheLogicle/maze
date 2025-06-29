#include "maze.hpp"

#include <SDL3/SDL.h>


void Maze::render ()
{

	SDL_SetRenderDrawColorFloat(m_renderer, Colors::backgroundColor);

	SDL_RenderClear(m_renderer);

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


	SDL_SetRenderDrawColorFloat(m_renderer, Colors::borderColor);
	SDL_RenderFillRects(m_renderer, borderRects, 4);


}


void Maze::drawMazeGrid ()
{

	SDL_SetRenderDrawColorFloat(m_renderer, Colors::mazeColor);

	for (int row = 0; row < m_gridHeight; ++row)
	{

		auto &curRow = m_grid.at(row);

		for (int col = 0; col < m_gridWidth; ++col)
		{

			block &curBlock = curRow.at(col);

			SDL_FPoint bottomLeft = getBlockCornerPos(BOTTOM_LEFT, col, row);
			SDL_FPoint topRight = getBlockCornerPos(TOP_RIGHT, col, row);

			float thickness = 2;

			SDL_FRect bottomEdge{.x = bottomLeft.x, .y = bottomLeft.y, .w = m_blockPixelSize + thickness, .h = thickness};
			SDL_FRect rightEdge{.x = topRight.x, .y = topRight.y, .w = thickness, .h = m_blockPixelSize + thickness};


			bool onRightEdge = col == m_gridWidth - 1;
			bool onBottomEdge = row == m_gridHeight - 1;



			//check that there is no pointer between current block and right block
			if (curBlock.pointsTo != RIGHT &&
					!onRightEdge && m_grid.at(row).at(col + 1).pointsTo != LEFT)
			{
				SDL_RenderFillRect(m_renderer, &rightEdge);
			}

			//check that there is no pointer between current block and below block
			if (curBlock.pointsTo != DOWN &&
					!onBottomEdge && m_grid.at(row + 1).at(col).pointsTo != UP)
			{
				SDL_RenderFillRect(m_renderer, &bottomEdge);
			}





		}

	}


}




