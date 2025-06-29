#include "maze.hpp"

#include <SDL3/SDL.h>


// this is the primary function, which runs the render loop and calls everything else (after the Maze object has been constructed)
void Maze::run ()
{

	m_running = true;


	// whether or not the maze should be regenerated on the next iteration of the infinite loop
	bool regen = true;



	// infinite render loop. right now, not much is going on, but in the future this may be useful for more added features
	while (m_running)
	{

		if (regen)
		{
			generateMaze();
			solveMaze();

			regen = false;
		}

		render();



		// handle events
		// not much to handle, so this handler can remain inline in this function
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
