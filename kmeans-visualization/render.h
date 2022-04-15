#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#pragma one
#include <iostream>
#include <SDL2/SDL_ttf.h>

class render {

public:
    render(const char *window_tile, int w_width, int w_heigh);
    
    bool isRunning = true;
    bool menuisRunning = true;
    bool kmeansisRunning = false;
    bool imgcompressisRunning = false;

    SDL_Texture *loadTexture(const char *file_name);
    void rendering(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst);
    void setColor(int r, int g, int b);
    void fillRect(SDL_Rect *rect, int r, int g, int b);
    void putpixel(SDL_Surface* screen, int x, int y, uint8_t r, uint8_t g, uint8_t b);

    void cleanUp();
    void clear();
    void display();
    SDL_Window *getWindow() {
        return window;
    }
    SDL_Renderer *getRender() {
        return renderer;
    }


private:
    SDL_Window *window;
    SDL_Renderer *renderer;

};





