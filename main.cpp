#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <cmath>
#include "physics.h"

int main() 
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(1920,1080,0,&window, &renderer);
    IMG_Init(IMG_INIT_PNG);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    
    SDL_Surface * image = IMG_Load("circle.png"); 
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    Ball balls[5];
    SDL_Rect destination;
    destination.h = 49;
    destination.w = 49;

    for (Ball ball : balls) {
        ball.x = 10;
        destination.x = ball.x;
        destination.y = ball.y;

        SDL_RenderCopy(renderer, texture, NULL, &destination);
    }


    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    return 0;
}
