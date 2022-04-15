#include "map.h"
#include <SDL2/SDL_image.h>
#include <fstream>
#define TILE_SIZE 32

const int WIDTH = 50;
const int HEIGHT = 29;

void map::setRect(int x, int y) {
    obj_rect.x = x;
    obj_rect.y = y;
    obj_rect.w = 32;
    obj_rect.h = 32;
}

bool map::loadImage(const char *path, SDL_Renderer *ren) {
    SDL_Texture *newTex = nullptr;
    newTex = IMG_LoadTexture(ren, path);
    if (newTex != nullptr) {
        obj_rect.w = 32;
        obj_rect.h = 32;
    }
    obj_texture = newTex;
    return newTex != nullptr;
}

void map::render(SDL_Renderer *ren) {
    SDL_Rect src;
    src.h = 32;
    src.w = 32;
    src.x = 0;
    src.y = 0;
    SDL_Rect dst = obj_rect;
    SDL_RenderCopy(ren, obj_texture, &src, &dst);
}

void map::free() {
    SDL_DestroyTexture(obj_texture);
    obj_texture = nullptr;
    obj_rect.w = 0;
    obj_rect.h = 0;
}

void GameMap::loadMap(const char *file_name) {
    std::ifstream file;

    file.open(file_name);
    for (int i = 0; i < 29; i++) {
        for (int j = 0; j < 50; j++) {
            int tmp;
            file >> tmp;
            game_map.tile[i][j] = tmp;

        }
    }

    file.close();
}

void GameMap::loadTiles(SDL_Renderer *ren) {
    char name[100];
    for (int i = 0; i < 4; i++) {
        sprintf(name, "my_map/%d.png", i);
        tile_map[i].loadImage(name, ren);
    }
}
void GameMap::drawMap(SDL_Renderer *ren) {
    int x1 = 0, x2 = 1600, y1 = 0, y2 = 900;
    int map_x = 0, map_y = 0;

    // map_x = game_map.start_x / TILE_SIZE;
    // map_y = game_map.start_y / TILE_SIZE;


    // x1 = (game_map.start_x % TILE_SIZE)*-1;
    // x2 = x1 + WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
    // y1 = (game_map.start_y % TILE_SIZE)*-1;
    // y2 = y1 + WIDTH + (y1 == 0 ? 0 : TILE_SIZE);

    for (int i = y1; i < y2; i += 32) {
        map_x = 0;
        for (int j = x1; j < x2; j += 32) {
            int tmp = game_map.tile[map_y][map_x];
            tile_map[tmp].setRect(j, i);
            tile_map[tmp].render(ren);
            map_x++;
        }
        map_y++;
    }

}
