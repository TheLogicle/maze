#include "maze.hpp"

#include <SDL3/SDL.h>


const SDL_FColor Colors::backgroundColor = SDL_FColor{.r = 0.02, .g = 0.05, .b = 0.08, .a = 1};
const SDL_FColor Colors::borderColor = SDL_FColor{.r = 0.4, .g = 0.4, .b = 0.4, .a = 1};
const SDL_FColor Colors::mazeColor = SDL_FColor{.r = 0.3, .g = 0.5, .b = 1, .a = 1};
const SDL_FColor Colors::solutionColor = SDL_FColor{.r = 0.1, .g = 0.8, .b = 0.1, .a = 1};
