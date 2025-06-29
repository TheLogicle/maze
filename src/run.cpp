#include "maze.hpp"

#include <SDL3/SDL.h>

#include <vector>

#include <iostream>


void Maze::run ()
{

	m_running = true;


	generateMaze();


	while (m_running)
	{

		render();


		SDL_Event event;
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
				case SDL_EVENT_QUIT:
					m_running = false;
					break;
			}

		}

	}

}
