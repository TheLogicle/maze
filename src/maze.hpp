#ifndef MAZE_HPP
#define MAZE_HPP

#include <SDL3/SDL.h>

#include <vector>

//custom operator overload to make it easier to manipulate float points
SDL_FPoint operator + (SDL_FPoint pt1, SDL_FPoint pt2);

//custom overload to make it easier to set the color
bool SDL_SetRenderDrawColorFloat (SDL_Renderer* renderer, SDL_FColor color);


struct block;

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
		void solveMaze ();

		enum direction
		{
			UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3
		};


		SDL_FPoint getBlockCornerPos (blockCorner corner, int blockX, int blockY);


	private:
		void calcNeighbors ();

	//internal rendering functions
	private:
		void drawBorder ();
		void drawMazeGrid ();
		void drawSolution ();

	
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


struct block
{

	int row, col;

	Maze::direction pointsTo = Maze::DOWN;

	std::vector<block*> neighbors;

	bool isSolution = false;
	Maze::direction solutionTo = Maze::DOWN;

	int solutionDist = -1;

};



class Colors
{

	public:
		static const SDL_FColor backgroundColor;
		static const SDL_FColor borderColor;
		static const SDL_FColor mazeColor;
		static const SDL_FColor solutionColor;

};


#endif
