#pragma one
#include "Entity.h"
#include <iostream>

class render {

public:
    render(const char *window_tile, int w_width, int w_heigh);
    bool isRunning = true;
    
    SDL_Texture *loadTexture(const char *file_name);
    
    void rendering(Entity &tex, SDL_Rect *rect);
     
    void cleanUp();
    void clear();
    void display();

    SDL_Window *getWindow() {
        return window;
    }
    SDL_Renderer *getRender() {
        return renderer;
    }

    void input(Entity &tex);

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

};
