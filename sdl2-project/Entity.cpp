#include "Entity.h"
using namespace std;
Entity::Entity(float p_x, float p_y, int w, int h, SDL_Texture *texture) :x(p_x), y(p_y), tex(texture) {
    currentFrame.x = x;
    currentFrame.y = y;
    currentFrame.h = h;
    currentFrame.w = w;
}

float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

SDL_Texture *Entity::getTex() {
    return tex;
}

SDL_Rect Entity::getcurrentFrame() {
    return currentFrame;
}


// animations

