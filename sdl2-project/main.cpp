#include <iostream>
#include "map.h"
#include "render.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;
int lastFrame, frameCount;
int main(int argc, char *argv[]) {

    render window("v1.0", 1600 , 900);
    GameMap gmap;


    SDL_Texture *knight = window.loadTexture("characters/knight_done_final.png");
    Entity knightD(0, 0, 70, 70, knight);
    gmap.loadMap("my_map/map.dat");
    gmap.loadTiles(window.getRender());

    // Stay right
    SDL_Rect sRight[3];
    sRight[0].x = 0;
    sRight[0].y = 0;
    sRight[0].w = 32;
    sRight[0].h = 32;
    
    sRight[1].x = 32;
    sRight[1].y = 0;
    sRight[1].w = 32;
    sRight[1].h = 32;
    
    sRight[2].x = 64;
    sRight[2].y = 0;
    sRight[2].w = 32;
    sRight[2].h = 32;
    
    // Stay left
    SDL_Rect sLeft[3]; 
    sLeft[0].x = 96;
    sLeft[0].y = 64;
    sLeft[0].w = 32;
    sLeft[0].h = 32;
    
    sLeft[1].x = 64;
    sLeft[1].y = 64;
    sLeft[1].w = 32;
    sLeft[1].h = 32;
    
    sLeft[2].x = 32;
    sLeft[2].y = 64;
    sLeft[2].w = 32;
    sLeft[2].h = 32;
    
    // moveRight
    SDL_Rect mRight[4]; 
    mRight[0].x = 0;
    mRight[0].y = 32;
    mRight[0].w = 32;
    mRight[0].h = 32;
    
    mRight[1].x = 32;
    mRight[1].y = 32;
    mRight[1].w = 32;
    mRight[1].h = 32;
    
    mRight[2].x = 64;
    mRight[2].y = 32;
    mRight[2].w = 32;
    mRight[2].h = 32;
    
    mRight[3].x = 96;
    mRight[3].y = 32;
    mRight[3].w = 32;
    mRight[3].h = 32;
    
    // moveLeft
    SDL_Rect mLeft[4]; 
    mLeft[0].x = 96;
    mLeft[0].y = 96;
    mLeft[0].w = 32;
    mLeft[0].h = 32;
    
    mLeft[1].x = 64;
    mLeft[1].y = 96;
    mLeft[1].w = 32;
    mLeft[1].h = 32;
    
    mLeft[2].x = 32;
    mLeft[2].y = 96;
    mLeft[2].w = 32;
    mLeft[2].h = 32;
    
    mLeft[3].x = 0;
    mLeft[3].y = 96;
    mLeft[3].w = 32;
    mLeft[3].h = 32;

    // hitRight
    SDL_Rect hRight[1]; 
    hRight[0].x = 96;
    hRight[0].y = 0;
    hRight[0].w = 32;
    hRight[0].h = 32;

    // hitLeft
    SDL_Rect hLeft[1]; 
    hLeft[0].x = 0;
    hLeft[0].y = 64;
    hLeft[0].w = 32;
    hLeft[0].h = 32;
    /* end character draw */
    

    int frame = 0;
    int count = 0;
    
    while(window.isRunning) {
        
        lastFrame = SDL_GetTicks();
        static int lastTime;
        if (lastFrame >= (lastTime+1000)) {
            lastTime = lastFrame;
            frameCount = 0;
            count++;
        }
        
        window.input(knightD);
        int motion = 100;
        SDL_Rect *knight_sRight = &sRight[frame/motion];
        SDL_Rect *knight_sLeft = &sLeft[frame/motion];
        SDL_Rect *knight_mRight = &mRight[frame/motion];
        SDL_Rect *knight_mLeft = &mLeft[frame/motion];
        
        gmap.drawMap(window.getRender());

        if (knightD.hit == 1) {
            if (knightD.on_right == 1) {
             
                
                gmap.drawMap(window.getRender());
                frame = 0;
                SDL_Rect *knight_hRight = &hRight[0];
                window.rendering(knightD, knight_hRight) ;
                
                window.display();
                window.clear();
            }
            if (knightD.on_left == 1) {
             
                
                gmap.drawMap(window.getRender());
                frame = 0;
                SDL_Rect *knight_hLeft = &hLeft[0];
                window.rendering(knightD, knight_hLeft) ;
                
                window.display();
                window.clear();
            }
        }

        if (knightD.k_up == 1) {
            if (knightD.on_right == 1) {
             
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_mRight) ;
                knightD.kUp();
                frame++;
                if (frame/motion >= 4) {
                frame = 0;
                }
                window.display();
                window.clear();
            }
            if (knightD.on_left == 1) {
                 
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_mLeft) ;
                knightD.kUp();
                frame++;
                if (frame/motion >= 4) {
                frame = 0;
                }
                window.display();
                window.clear();
            }
        }
        if (knightD.k_down == 1) {
            if (knightD.on_right == 1) {
             
                
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_mRight) ;
                knightD.kDown();
                frame++;
                if (frame/motion >= 4) {
                frame = 0;
                }
                window.display();
                window.clear();
            }
            if (knightD.on_left == 1) {
             
                
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_mLeft) ;
                knightD.kDown();
                frame++;
                if (frame/motion >= 4) {
                frame = 0;
                }
                window.display();
                window.clear();
            }
        }  
        if (knightD.k_left == 1) {
         
            
            gmap.drawMap(window.getRender());
            window.rendering(knightD, knight_mLeft) ;
            knightD.kLeft();
            frame++;
            if (frame/motion >= 4) {
                frame = 0;
            }
            window.display();
            window.clear();
      
        }  
        if (knightD.k_right == 1) {
         
            
            gmap.drawMap(window.getRender());
            window.rendering(knightD, knight_mRight) ;
            knightD.kRight();
            frame++;
            if (frame/motion >= 4) {
                frame = 0;
            }
            window.display();
            window.clear();
      
        }  
        if (knightD.k_up == 0 && knightD.k_down == 0 && knightD.k_left == 0 && knightD.k_right == 0 && knightD.hit == 0) {
            
            if (knightD.on_right == 1) {
             
                
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_sRight) ;
                frame++;
                if (frame/motion >= 3) {
                    frame = 0;
                }
                window.display();
                window.clear();
            }
            if (knightD.on_left == 1) {
             
                
                gmap.drawMap(window.getRender());
                window.rendering(knightD, knight_sLeft) ;
                frame++;
                if (frame/motion >= 3) {
                frame = 0;
                }
                window.display();
                window.clear();
            }

        
        }
    }
    //window.display();
    if (count > 3) window.isRunning = false;
    window.cleanUp();

}
