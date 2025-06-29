#include "maze.hpp"

int main ()
{
	// number of blocks tall and wide
	const int gridWidth = 35;
	const int gridHeight = 30;

	// size of each block
	const int blockPixelSize = 40;

	// pixel padding around entire maze
	const int padPixels = 30;

	Maze m1(gridWidth, gridHeight, blockPixelSize, padPixels);

	m1.run();
}
