#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h> 
#include "physics.h"
#include <ctime>
#include <iostream>
using namespace std;

int main() 
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(1920,1080,0,&window, &renderer);
    IMG_Init(IMG_INIT_PNG);
    srand((unsigned)time(0));

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    
    SDL_Surface * image = IMG_Load("circle.png"); 
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    
    int ball_count=20;
    Ball balls[ball_count];
    SDL_Rect destination;
    destination.h = 49;
    destination.w = 49;

    for (int i=0;i<ball_count;i++) {
        balls[i].velocity={rand() % 2,rand() % 2};
        balls[i].position={rand() % 1920,rand() % 1080};
        destination.x = balls[i].position.x;
        destination.y = balls[i].position.y;

        SDL_RenderCopy(renderer, texture, NULL, &destination);
    }
    SDL_RenderPresent(renderer);
    
    bool running=true;
    int delay=10;
    while(running){
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym==SDLK_ESCAPE) {
                    running=false;
                }
                else if (e.key.keysym.sym==SDLK_UP) {
                    delay+=5;
                }
                else if (e.key.keysym.sym==SDLK_DOWN) {
                    if (delay!=5){
                        delay-=5;
                    }
                }
            }
            else if(e.type == SDL_QUIT) {
                running=false;
            }
        }
        for (int i=0;i<ball_count;i++) {
            balls[i]=updatePhysics(balls[i],balls,i,ball_count);
            destination.x = balls[i].position.x;
            destination.y = balls[i].position.y;
            SDL_RenderCopy(renderer, texture, NULL, &destination);
        }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(delay);
    }
    return 0;
}
