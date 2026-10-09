#include "../include/window.h"
#include "../include/image.h"
#include <err.h>
#include <stdio.h>


Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    if (surface->format->BytesPerPixel != 4)
        errx(EXIT_FAILURE, "Unsupported pixel format");

    Uint8 *pixels = (Uint8 *)surface->pixels;

    return *(Uint32 *)(pixels + y * surface->pitch + x * 4);
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    if (surface->format->BytesPerPixel != 4)
        errx(EXIT_FAILURE, "Unsupported pixel format");

    Uint8 *pixels = (Uint8 *)surface->pixels;

    *(Uint32 *)(pixels + y * surface->pitch + x * 4) = pixel;
}

void reverse(SDL_Surface *surface){
    for (int y = 0; y < surface->h; y++){
        for (int x = 0; x < surface->w; x++){

            Uint32 pixel = get_pixel(surface, x, y);

            Uint8 r;
            Uint8 g;
            Uint8 b;

            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            Uint8 rr = 255 - r;
            Uint8 rg = 255 - g;
            Uint8 rb = 255 - b;
            

            Uint32 new_pixel = SDL_MapRGB(
                surface->format,
                rr,
                rg,
                rb
            );

            set_pixel(surface, x, y, new_pixel);
        }
    }

}

SDL_Surface *load_image()
{
        
    SDL_RWops *rw = SDL_RWFromConstMem(img_screemer_bmp, img_screemer_bmp_len);

    SDL_Surface *surface = SDL_LoadBMP_RW(rw, 1);

    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface *converted = SDL_ConvertSurfaceFormat(
        surface,
        SDL_PIXELFORMAT_RGBA32,
        0
    );

    SDL_FreeSurface(surface);

    if (converted == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    return converted;
}

SDL_Texture *load_texture(SDL_Renderer *renderer, int reversed){
	SDL_Surface *surface = load_image();
    if (reversed){
        reverse(surface);
    }
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (texture == NULL){
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	}
	return texture;
}


int main()
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode dm;

    init_window(&window, &renderer, &dm);

    SDL_Texture *texture = load_texture(renderer, 0);
    SDL_Texture *texture2 = load_texture(renderer, 1);
	
	SDL_Rect dst_rect;
	dst_rect.w = dm.w;
	dst_rect.h = dm.h;
	dst_rect.x = 0;
	dst_rect.y = 0;


    SDL_Event event;
    
    int enc=1;
    while (enc){
        while (SDL_PollEvent(&event)){
            if (event.type==SDL_QUIT || event.type==SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN){
                enc=0;
            }
        }
        SDL_Delay(1000 / 24); // ~24 FPS
    }

    for (int i=0; i<30; i++){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture, NULL, &dst_rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(60);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, texture2, NULL, &dst_rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(50);
    }

    

	SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture2);
	terminate(window,renderer);
	return EXIT_SUCCESS;
}
