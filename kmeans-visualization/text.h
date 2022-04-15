#pragma one
#include <iostream>
#include <SDL2/SDL_ttf.h>
class text {
public:
    void setFont(const char *c, int fontsize);
    void setSur(std::string str, SDL_Color color);
    void setTex(std::string str, SDL_Color &color, SDL_Renderer *ren);
    void blitText(SDL_Renderer *ren, SDL_Rect *dst);
    
    SDL_Surface *getSur() {
        return surf;
    }
    
private:
    SDL_Texture *tex = nullptr;
    SDL_Surface *surf;
    TTF_Font *Arial;
};
