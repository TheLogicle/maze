#include "maze.hpp"

#include <SDL3/SDL.h>

void Maze::run ()
{

	m_running = true;


	bool regen = true;

	while (m_running)
	{

		if (regen)
		{
			generateMaze();
			solveMaze();

			regen = false;
		}

		render();


		SDL_Event event;
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{

				case SDL_EVENT_QUIT:
					m_running = false;
					break;

				case SDL_EVENT_KEY_DOWN:
					if (event.key.key == SDLK_A)
					{
						prepareGrid();
						regen = true;
					}
					break;

			}

		}

	}

}
