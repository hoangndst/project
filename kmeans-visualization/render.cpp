#include "render.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

render::render(const char *window_tile, int w_width, int w_heigh) {
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(window_tile, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_heigh, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Window failed to init " << SDL_GetError() << endl;
  }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture *render::loadTexture(const char *file_name) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, file_name);
    if (texture == NULL) {
        cout << "Failed to load Texture " << SDL_GetError() << endl;
    }
    return texture;
}

void render::clear() {
    SDL_RenderClear(renderer);
}

void render::cleanUp() {
    SDL_DestroyWindow(window);
}

void render::rendering(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst) {
    //SDL_QueryTexture(tex, NULL, NULL, &dst->w, &dst->h);
    SDL_RenderCopy(renderer, tex, src, dst);
    SDL_DestroyTexture(tex);
}
void render::display() {
    SDL_SetRenderDrawColor(renderer, 0, 43, 54, 0);
    SDL_RenderPresent(renderer);
}


void render::setColor(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}
void render::fillRect(SDL_Rect *rect, int r, int g, int b) {
    setColor(r, g, b);
    SDL_RenderFillRect(renderer, rect);
}

void render::putpixel(SDL_Surface *screen, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    Uint32* pixels = (Uint32*)screen->pixels;
    Uint32* pixel = pixels + y*screen->pitch/4 + x;
    *pixel = SDL_MapRGB(screen->format, r, g, b);
}

