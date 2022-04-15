#include "render.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
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

void render::rendering(Entity &tex, SDL_Rect *rect) {
    SDL_Rect dst;
    dst.h = tex.getcurrentFrame().h;
    dst.w = tex.getcurrentFrame().w;
    dst.x = tex.getX(); // bgX;
    dst.y = tex.getY(); // bgY;
    SDL_RenderCopy(renderer, tex.getTex(), rect, &dst);
}
void render::display() {
    SDL_RenderPresent(renderer);
}
void render::input(Entity &tex) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            cout << "Press Exit" << endl; 
            isRunning = false;
            clear();
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_w) {
                tex.k_up = 1;
            }
            if (event.key.keysym.sym == SDLK_s) {
                tex.k_down = 1;
            }
            if (event.key.keysym.sym == SDLK_a) {
                tex.on_right = 0;
                tex.on_left = 1;
                tex.k_left = 1;
            }
            if (event.key.keysym.sym == SDLK_d) {
                tex.on_right = 1;
                tex.on_left = 0;
                tex.k_right = 1;
            }
            if (event.key.keysym.sym == SDLK_h) {
                tex.hit = 1;
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_w) {
                tex.k_up = 0;
            }
            if (event.key.keysym.sym == SDLK_s) {
                tex.k_down = 0;
            }
            if (event.key.keysym.sym == SDLK_a) {
                tex.k_left = 0;
            }
            if (event.key.keysym.sym == SDLK_d) {
                tex.k_right = 0;

            }
            if (event.key.keysym.sym == SDLK_h) {
                tex.hit = 0;
            }
        }
    }
}
