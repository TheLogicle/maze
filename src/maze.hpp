#ifndef MAZE_HPP
#define MAZE_HPP

#include <SDL3/SDL.h>

#include <vector>


SDL_FPoint operator + (SDL_FPoint pt1, SDL_FPoint pt2);


struct block
{

	bool rightOpen = true;
	bool downOpen = true;

};

enum blockCorner
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};


class Maze
{
	public:
		Maze (int gridWidth, int gridHeight, int blockPixelSize, int padPixels);

		void run ();
		void render ();

		void generateMaze ();



		SDL_FPoint getBlockCornerPos (blockCorner corner, int blockX, int blockY);

	//internal rendering functions
	private:
		void drawBorder ();
		void drawMazeGrid ();

	
	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;

		int m_padPixels;
		int m_blockPixelSize;

		int m_winWidth;
		int m_winHeight;

		int m_gridWidth;
		int m_gridHeight;

		bool m_running;

		typedef std::vector<block> blockRow;
		std::vector<blockRow> m_grid; 

};


#endif
