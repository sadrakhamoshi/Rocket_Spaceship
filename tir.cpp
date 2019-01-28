#include <stdlib.h>
#include "tir.h"
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <time.h>

const int SCREEN_WIDTH = 550;
const int SCREEN_HEIGHT = 700;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface *gRocket = NULL;
SDL_Surface *gScreensurface = NULL;
float xtir = 277.5;
float ytir = 450;
float xendtir = xtir;
float yendtir = ytir;
//const Uint8 *keys = SDL_GetKeyboardState(NULL);
void init()
{
    gWindow = SDL_CreateWindow("MS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

int main()
{
    srand(time(0));
    init();
    //float vtir = 0;
    gRocket = SDL_LoadBMP("rocket.bmp");
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, gRocket);
    int a;
    bool quit;
    bool flag;
    bool start = false;
    bool tir = false;
    bool s = true;
    bool ptr = true;
    SDL_Event e;

    SDL_Rect rocketRect;
    rocketRect.x = 240;
    float x = rocketRect.x;
    rocketRect.y = 450;
    rocketRect.w = 75;
    rocketRect.h = 75;
    c.x=240+75/2;
    c.y=450;

    while (!quit)
    {

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 128, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, &rocketRect);
        if (tir)
        {
            if (c.lahze_shelik) {
                c.x = c.xend + 75/2;
                c.y = c.yend;
                c.lahze_shelik = false;
            }
            filledCircleRGBA(gRenderer, c.x, c.y + c.v, 4, 255, 255, 255, 255);
        }
         if (!tir)
         {
             filledCircleRGBA(gRenderer, c.xend+75/2, c.yend, 4, 255, 255, 255, 255);
         }
        if (s)
        {
            //filledCircleRGBA(gRenderer, rocketRect.x+75/2, rocketRect.y, 4, 255, 255, 255, 255);
            // filledCircleRGBA(gRenderer, xtir, ytir + vtir, 4, 255, 255, 255, 255);
        }
        while (SDL_PollEvent(&e) != 0)
        {

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
            {
                flag = true;
                start = true;
            }
            break;
            case SDLK_RIGHT:
            {
                flag = false;
                start = true;
            }
            break;

            case SDLK_z:
            {
                tir = true;
                c.lahze_shelik = true;
                s = false;
            }
                // break;
                
            }
        }
        if (flag == false && start == true)
        {
            x += 0.5;
            rocketRect.x = x;
            // xendtir = rocketRect.x;
            // xtir = rocketRect.x+rocketRect.w/2;
            c.xend = rocketRect.x;
            c.yend=rocketRect.y;
        }
        else if (flag == true && start == true)
        {
            x -= 0.5;
            rocketRect.x = x;
            //xendtir = rocketRect.x;
            // xtir = rocketRect.x+rocketRect.w/2;
            c.xend= rocketRect.x;
            c.yend =rocketRect.y;
        }
        if (tir)
        {
            c.v -= 5;
            if (c.y +c.v - 4 <= 2)
            {
               // ptr = false;
               tir=false;
                c.x = c.xend+75/2;
                c.y = c.yend;
                c.v = 0;
            }
        }
        
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}
