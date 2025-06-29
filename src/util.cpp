#include "maze.hpp"

#include <stdexcept>


SDL_FPoint operator + (SDL_FPoint pt1, SDL_FPoint pt2)
{
	return SDL_FPoint
	{
		.x = pt1.x + pt2.x,
		.y = pt1.y + pt2.y
	};
}



SDL_FPoint Maze::getBlockCornerPos (blockCorner corner, int blockX, int blockY)
{

	SDL_FPoint topLeft
	{
		.x = (float) m_padPixels + blockX * m_blockPixelSize,
		.y = (float) m_padPixels + blockY * m_blockPixelSize
	};


	switch (corner)
	{

		case TOP_LEFT:
			return topLeft;

		case TOP_RIGHT:
			return topLeft + SDL_FPoint{.x = (float) m_blockPixelSize, .y = 0};

		case BOTTOM_LEFT:
			return topLeft + SDL_FPoint{.x = 0, .y = (float) m_blockPixelSize};

		case BOTTOM_RIGHT:
			return topLeft + SDL_FPoint{.x = (float) m_blockPixelSize, .y = (float) m_blockPixelSize};

		default:
			throw std::runtime_error("invalid enum option in Maze::getblockCornerPos");

	};

}

