#include "../include/window.h"
#include <stdio.h>

void init_window(SDL_Window **window, SDL_Renderer **renderer, SDL_DisplayMode *dm)
{
        if (SDL_Init(SDL_INIT_VIDEO)<0){
                fprintf(stderr, "ERREUR DE SDL");
                return;
        }
        SDL_GetCurrentDisplayMode(0, dm);

        *window = SDL_CreateWindow(
            "Projection",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            dm->w,
            dm->h,
            SDL_WINDOW_FULLSCREEN_DESKTOP
        );
        if (*window==NULL){
                fprintf(stderr, "ERREUR DE CREATION DE LA FENETRE");
                return;
        }
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
        if (*window==NULL){
                fprintf(stderr, "ERREUR DANS LA CREATION DU RENDERER");
                SDL_DestroyWindow(*window);
                SDL_Quit();
                return;
        }
}

void terminate(SDL_Window *window, SDL_Renderer *renderer)
{
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

