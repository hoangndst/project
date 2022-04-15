#include "text.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

void text::setFont(const char *c, int fontsize) {
    Arial = TTF_OpenFont(c, fontsize);
}
void text::setTex(std::string str, SDL_Color &color, SDL_Renderer *ren) {
    surf = TTF_RenderText_Solid(Arial, str.c_str(), color);
    tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(this->surf);
}

void text::blitText(SDL_Renderer *ren, SDL_Rect *dst) {
    SDL_QueryTexture(tex, NULL, NULL, &dst->w, &dst->h);
    SDL_RenderCopy(ren, tex, NULL, dst);
    SDL_DestroyTexture(tex);
}

