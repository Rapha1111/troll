#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280

void init_window(SDL_Window **window, SDL_Renderer **renderer, SDL_DisplayMode *dm);
void terminate(SDL_Window *window, SDL_Renderer *renderer);

#endif /* ! WINDOW_H */