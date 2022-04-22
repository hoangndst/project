#include <SDL2/SDL.h>
class map {
public:
    void setRect(int x, int y);
    SDL_Rect getRect() {
        return obj_rect;
    }

    SDL_Texture *getTex() {
        return obj_texture;
    }
    bool loadImage(const char *path, SDL_Renderer *ren);
    void render(SDL_Renderer *ren);
    void free();
private:
    SDL_Texture *obj_texture;
    SDL_Rect obj_rect;

};

struct Map {
    int tile[29][50];
    char *file_name;
};

class GameMap {

public:

    void loadMap(const char *file_name);
    void loadTiles(SDL_Renderer *ren);
    void drawMap(SDL_Renderer *ren);

private:
    Map game_map;
    map tile_map[4];
};
