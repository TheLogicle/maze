#include "maze.hpp"

#include <SDL3/SDL.h>

#include <stdexcept>


// main render function. this is where all partial rendering functions should be called from
void Maze::render ()
{

	SDL_SetRenderDrawColorFloat(m_renderer, Colors::backgroundColor);

	SDL_RenderClear(m_renderer);

	drawMazeGrid();
	drawBorder();


	drawSolution();


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

	// pixel thickness of the border
	const float thickness = 8;

	// these are rectangles that, when all drawn, will create the border
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


// draw the actual maze
void Maze::drawMazeGrid ()
{

	SDL_SetRenderDrawColorFloat(m_renderer, Colors::mazeColor);

	for (int row = 0; row < m_gridHeight; ++row)
	{

		blockRow &curRow = m_grid.at(row);

		for (int col = 0; col < m_gridWidth; ++col)
		{

			block &curBlock = curRow.at(col);

			SDL_FPoint bottomLeft = getBlockCornerPos(BOTTOM_LEFT, col, row);
			SDL_FPoint topRight = getBlockCornerPos(TOP_RIGHT, col, row);

			// pixel thickness of maze walls
			const float thickness = 2;

			// the actual edges of each block to be drawn
			SDL_FRect bottomEdge{.x = bottomLeft.x, .y = bottomLeft.y, .w = m_blockPixelSize + thickness, .h = thickness};
			SDL_FRect rightEdge{.x = topRight.x, .y = topRight.y, .w = thickness, .h = m_blockPixelSize + thickness};


			bool onRightEdge = col == m_gridWidth - 1;
			bool onBottomEdge = row == m_gridHeight - 1;



			// check that there is no pointer between current block and right block
			// if there is no pathway, draw the wall
			if (curBlock.pointsTo != RIGHT &&
					!onRightEdge && m_grid.at(row).at(col + 1).pointsTo != LEFT)
			{
				SDL_RenderFillRect(m_renderer, &rightEdge);
			}

			// check that there is no pointer between current block and below block
			// if there is no pathway, draw the wall
			if (curBlock.pointsTo != DOWN &&
					!onBottomEdge && m_grid.at(row + 1).at(col).pointsTo != UP)
			{
				SDL_RenderFillRect(m_renderer, &bottomEdge);
			}





		}

	}


}


// once the solution is calculated (elsewhere), this function will render it
void Maze::drawSolution ()
{

	SDL_SetRenderDrawColorFloat(m_renderer, Colors::solutionColor);


	for (int row = 0; row < m_gridHeight; ++row)
	{

		for (int col = 0; col < m_gridWidth; ++col)
		{

			block &curBlock = m_grid.at(row).at(col);

			// skip this block if it is not part of the solution path
			if (!curBlock.isSolution)
			{
				continue;
			}


			// thickness of the drawn solution path, as a percentage of the block width
			const float thicknessPercent = 0.2;

			// pixel padding between the edge of the block and the edge of the solution path
			float padPixels = 0.5 * (1 - thicknessPercent) * m_blockPixelSize;
			// actual pixel thickness of the solution path
			float innerSquarePixels = thicknessPercent * m_blockPixelSize;

			// pixel coordinates of the top left and bottom right of the current block
			SDL_FPoint blockTopLeft = Maze::getBlockCornerPos(TOP_LEFT, col, row);
			SDL_FPoint blockBottomRight = Maze::getBlockCornerPos(BOTTOM_RIGHT, col, row);

			SDL_FRect pathRect;

			// prepare the rectangle that needs to be drawn for this block
			switch (curBlock.solutionTo)
			{

				case UP:
					pathRect = SDL_FRect
					{
						.x = blockBottomRight.x - padPixels,
						.y = blockBottomRight.y - padPixels,
						.w = -innerSquarePixels,
						.h = -2 * (innerSquarePixels + padPixels)
					};
					break;

				case RIGHT:
					pathRect = SDL_FRect
					{
						.x = blockTopLeft.x + padPixels,
						.y = blockTopLeft.y + padPixels,
						.w = 2 * (innerSquarePixels + padPixels),
						.h = innerSquarePixels
					};
					break;

				case DOWN:
					pathRect = SDL_FRect
					{
						.x = blockTopLeft.x + padPixels,
						.y = blockTopLeft.y + padPixels,
						.w = innerSquarePixels,
						.h = 2 * (innerSquarePixels + padPixels)
					};
					break;

				case LEFT:
					pathRect = SDL_FRect
					{
						.x = blockBottomRight.x - padPixels,
						.y = blockBottomRight.y - padPixels,
						.w = -2 * (innerSquarePixels + padPixels),
						.h = -innerSquarePixels
					};
					break;

				default:
					throw std::runtime_error("invalid solution direction, thrown from Maze::drawSolution");

			}


			SDL_RenderFillRect(m_renderer, &pathRect);

		}

	}

}



