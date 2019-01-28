#include <stdlib.h>
#include "barriers.h"
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <time.h>

const int SCREEN_WIDTH = 555;
const int SCREEN_HEIGHT = 705;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface *gShahab = NULL;
SDL_Surface *gScreensurface = NULL;
SDL_Texture *gTexture;
TTF_Font *gFont = TTF_OpenFont("game.ttf", 54);

void init()
{
    gWindow = SDL_CreateWindow("MS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void heighscore(SDL_Renderer *gRenderer, int score, TTF_Font *gFont, )
{
    SDL_Color textColor = {255, 255, 255, 255};
    int heighscore=0;
    SDL_Rect hscore_rect;
    hscore_rect.x = 150;
    hscore_rect.y = 640;
    hscore_rect.h = 60;
    hscore_rect.w = 100;

    SDL_Color textColor = {255, 255, 255, 255};
    std::stringstream timetext;
    timetext << "heighscore :";
    SDL_RWops *file = SDL_RWFromFile("heighscore.bin", "r+b");
    if (heighscore < score){
        SDL_RWwrite(file, &heighscore, sizeof(heighscore), 1);
        SDL_RWclose(file);
    }
    SDL_RWread(file, &heighscore, sizeof(heighscore), 1);
    SDL_RWclose(file);
    SDL_Surface *surface = TTF_RenderText_Solid(gFont, timetext.str().c_str(), textColor);
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_RenderCopyEx(gRenderer, gTexture, NULL, &hscore_rect, 0.0, NULL, SDL_FLIP_NONE);
    
}

int main()
{
    srand(time(0));
    init();
    TTF_Init();

    bool quit;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 66, 545, 128, 255);
        SDL_RenderClear(gRenderer);

        SDL_RenderPresent(gRenderer);
        SDL_Delay(50);
    }

    return 0;
}
