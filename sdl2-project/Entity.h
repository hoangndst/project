#pragma one
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {

private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture *tex;
    int mouse_x, mouse_y;
public:
    Entity(float p_x, float p_y, int w, int h, SDL_Texture *p_texture);
    float getX();
    float getY();
    SDL_Texture *getTex();
    SDL_Rect getcurrentFrame();
    int motion = 1;
    void kUp() {
        y = y - motion;
    }
    void kDown() {
        y = y + motion;
    }
    void kRight() {
        x = x + motion;
    }
    void kLeft() {
        x = x - motion;
    }




    bool k_up = 0;
    bool k_down = 0;
    bool k_right = 0;
    bool k_left = 0;
    bool on_right = 1;
    bool on_left = 0;
    bool hit = 0;
};

