#pragma once
#include "barriers.h"
#include <stdlib.h>
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
SDL_Surface *gDivar = NULL;
SDL_Surface *gDivar2 = NULL;
SDL_Surface *gShahab = SDL_LoadBMP("shahab.bmp");
SDL_Texture *gTexture4 = SDL_CreateTextureFromSurface(gRenderer, gShahab);
SDL_Surface *gCoin = SDL_LoadBMP("coin.bmp");
SDL_Texture *gTexture5 = SDL_CreateTextureFromSurface(gRenderer, gCoin);
SDL_Surface *gGun = SDL_LoadBMP("gun.bmp");
SDL_Texture *gTexture6 = SDL_CreateTextureFromSurface(gRenderer, gGun);
SDL_Surface *gScreenSurface = NULL;

void init()
{
    gWindow = SDL_CreateWindow("MS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            abarrier[i][j].x = 55 * j ;
            abarrier[i][j].y = 70 * i ;
        }
    }
}

void Random()
{
    //shahabsang=1;
    //coin=2;
    //gun=3
    int b[10] = {};
    int q = rand() % 4 + 3;
    b[q] = rand() % 3 + 1;

    for (int j = 3; j < 7; j++)
    {
        abarrier[0][j].value = b[j];
    }
}

void shift(barriers abarrier[10][10])
{
    for (int i = 9; i >= 0; i--)
    {
        for (int j = 3; j < 7; j++)
        {
            abarrier[i + 1][j].value = abarrier[i][j].value;
        }
    }
    Random();
}

void showbarrier(barriers abarrier[10][10])
{
    SDL_Rect shahabRect;
    shahabRect.x;
    shahabRect.y;
    shahabRect.w = 55;
    shahabRect.h = 70;

    SDL_Rect gunRect;
    gunRect.x;
    gunRect.y;
    gunRect.w = 55;
    gunRect.h = 70;

    SDL_Rect coinRect;
    coinRect.x;
    coinRect.y;
    coinRect.w = 55;
    coinRect.h = 70;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if (abarrier[i][j].value == 1)
            {

                SDL_RenderCopy(gRenderer, gTexture4, NULL, &shahabRect);
            }
            else if (abarrier[i][j].value == 2)
            {

                SDL_RenderCopy(gRenderer, gTexture5, NULL, &coinRect);
            }
            else if (abarrier[i][j].value == 3)
            {

                SDL_RenderCopy(gRenderer, gTexture6, NULL, &gunRect);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    bool start = false;
    bool quit = false;
    bool flag;
    init();
    gRocket = SDL_LoadBMP("rocket.bmp");
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, gRocket);
    gDivar = SDL_LoadBMP("left.bmp");
    SDL_Texture *gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gDivar);
    gDivar2 = SDL_LoadBMP("right.bmp");
    SDL_Texture *gTexture3 = SDL_CreateTextureFromSurface(gRenderer, gDivar2);

    SDL_Rect rocketRect;
    rocketRect.x = 240;
    float x = rocketRect.x;
    rocketRect.y = 450;
    rocketRect.w = 75;
    rocketRect.h = 75;

    SDL_Rect divarRect;
    divarRect.x = 0;
    divarRect.y = 0;
    divarRect.w = 550;
    divarRect.h = 750;

    SDL_Rect divar2Rect;
    divar2Rect.x = 0;
    divar2Rect.y = 0;
    divar2Rect.w = 570;
    divar2Rect.h = 750;

    SDL_Event e;
    while (!quit)
    {

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 128, 255);
        SDL_RenderClear(gRenderer);
        SDL_RenderCopy(gRenderer, gTexture, NULL, &rocketRect);
        SDL_RenderCopy(gRenderer, gTexture2, NULL, &divarRect);
        SDL_RenderCopy(gRenderer, gTexture3, NULL, &divar2Rect);

        shift(abarrier);
        showbarrier(abarrier);
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
            }
        }
        if (flag == false && start == true)
        {
            x += 0.05;
            rocketRect.x = x;
        }
        else if (flag == true && start == true)
        {
            x -= 0.05;
            rocketRect.x = x;
        }
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}