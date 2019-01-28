#pragma once
#include "tir.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <sstream>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <fstream>
////////////////////////////////////////
const int SCREEN_WIDTH = 550;
const int SCREEN_HEIGHT = 700;
////////////////////////////////////////
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface *gRocket = NULL;
SDL_Surface *gDivar = NULL;
SDL_Surface *gDivar2 = NULL;
SDL_Surface *gShahab = NULL;
SDL_Surface *gShahab2 = NULL;
SDL_Surface *gCoin = NULL;
SDL_Surface *gScreensurface = NULL;
SDL_Surface *gGun = NULL;
SDL_Surface *gSepar = NULL;
SDL_Surface *gGameover = NULL;
SDL_Texture *gTexture10;
TTF_Font *gFont = TTF_OpenFont("game.ttf", 54);
Mix_Music *gSound = NULL;
//float xtir = 277.5;
//float ytir = 450;
//float xendtir = xtir;
//float yendtir = ytir;
int coin = 0;
int coincounter = 0;
int score = 0;
bool quit = false;
bool gun = false;
bool shahab = false;
bool shahab2 = false;
bool ISlaunched = true;
bool cshahab = false;
bool cshahab2 = false;
bool iscollided = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long int file(int point)
{
    long long int BestPoint;
    fstream PointFile;

    PointFile.open("Data.txt");
    PointFile >> BestPoint;
    PointFile.close();

    FILE *fp = fopen("Data.txt", "w");
    fclose(fp);

    PointFile.open("Data.txt");
    if (BestPoint < point)
        BestPoint = point;
    PointFile << BestPoint;

    return BestPoint;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void heigh(int score)
{
    SDL_Color textColor = {255, 255, 255, 255};
    std::stringstream timetext3;
    SDL_Rect hs_rect;
    hs_rect.x = 189;
    hs_rect.y = 150;
    hs_rect.h = 70;
    hs_rect.w = 200;
    timetext3.str("");
    timetext3 << "high score : " << file(score);
    SDL_Surface *surface33 = TTF_RenderText_Blended(gFont, timetext3.str().c_str(), textColor);
    SDL_Texture *gTexture33 = SDL_CreateTextureFromSurface(gRenderer, surface33);
    SDL_RenderCopyEx(gRenderer, gTexture33, NULL, &hs_rect, 0.0, NULL, SDL_FLIP_NONE);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void init()
{
    gWindow = SDL_CreateWindow("MS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScoreRender(SDL_Renderer *gRenderer, int score, TTF_Font *gFont)
{
    SDL_Color textColor = {255, 255, 255, 255};
    std::stringstream timetext;
    SDL_Rect score_rect;
    score_rect.x = 150;
    score_rect.y = 640;
    score_rect.h = 60;
    score_rect.w = 100;
    std::stringstream timetext2;
    SDL_Rect coin_rect;
    coin_rect.x = 290;
    coin_rect.y = 640;
    coin_rect.h = 60;
    coin_rect.w = 100;

    timetext.str("");
    timetext << "score : " << score;
    timetext2.str("");
    timetext2 << "coin : " << coincounter;
    SDL_Surface *surface = TTF_RenderText_Blended(gFont, timetext.str().c_str(), textColor);
    SDL_Texture *gTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_Surface *surface2 = TTF_RenderText_Blended(gFont, timetext2.str().c_str(), textColor);
    SDL_Texture *gTextureCoin = SDL_CreateTextureFromSurface(gRenderer, surface2);
    SDL_Texture *gTexture10 = SDL_CreateTextureFromSurface(gRenderer, gGameover);
    SDL_RenderCopyEx(gRenderer, gTexture, NULL, &score_rect, 0.0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, gTextureCoin, NULL, &coin_rect, 0.0, NULL, SDL_FLIP_NONE);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface2);
    SDL_DestroyTexture(gTexture);
    SDL_DestroyTexture(gTextureCoin);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    const int fps = 90;
    const int framedelay = 1000 / fps;
    Uint32 framestart;
    int frametime;
    srand(time(NULL));
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    gSound = Mix_LoadMUS("147.mp3");
    Mix_PlayMusic(gSound, -1);
    bool start = false;
    bool flag;
    bool tir = false;
    bool s = true;
    bool separ = false;
    int separcount = 0;
    float timer = 3;
    float timershahab = 3;
    float timershahab2 = 3;
    TTF_Init();
    init();
    gFont = TTF_OpenFont("game.ttf", 100);
    SDL_Texture *gTexture;
    gShahab = SDL_LoadBMP("shahab.bmp");
    gSepar = SDL_LoadBMP("shield.bmp");
    SDL_Texture *gTexture7 = SDL_CreateTextureFromSurface(gRenderer, gRocket);
    gCoin = SDL_LoadBMP("coin.bmp");
    gGun = SDL_LoadBMP("gun.bmp");
    gRocket = SDL_LoadBMP("rocket.bmp");
    SDL_Texture *gTexture0 = SDL_CreateTextureFromSurface(gRenderer, gRocket);
    gDivar = SDL_LoadBMP("left.bmp");
    SDL_Texture *gTexture2 = SDL_CreateTextureFromSurface(gRenderer, gDivar);
    gDivar2 = SDL_LoadBMP("right.bmp");
    SDL_Texture *gTexture3 = SDL_CreateTextureFromSurface(gRenderer, gDivar2);
    //////////////////////////////////////////////
    SDL_Rect rocketRect;
    rocketRect.x = 240;
    float x2 = rocketRect.x;
    rocketRect.y = 450;
    rocketRect.w = 75;
    rocketRect.h = 75;
    c.x = 240 + 75 / 2;
    c.y = 450;
    //////////////////////////////////////////////
    SDL_Rect divarRect;
    divarRect.x = 0;
    divarRect.y = 0;
    divarRect.w = 550;
    divarRect.h = 700;
    //////////////////////////////////////////////
    SDL_Rect gameoverRect;
    gameoverRect.x = 0;
    gameoverRect.y = 0;
    gameoverRect.w = 550;
    gameoverRect.h = 700;
    //////////////////////////////////////////////
    SDL_Rect divar2Rect;
    divar2Rect.x = 0;
    divar2Rect.y = 0;
    divar2Rect.w = 550;
    divar2Rect.h = 700;
    //////////////////////////////////////////////
    SDL_Rect tirRect;
    tirRect.x = c.x;
    tirRect.y = c.y;
    tirRect.w = 8;
    tirRect.h = 8;
    //////////////////////////////////////////////
    SDL_Rect shahabRect;
    shahabRect.x = rand() % 80 + 200;
    shahabRect.y = 0;
    shahabRect.w = 55;
    shahabRect.h = 70;
    /////////////////////////////////////////////
    SDL_Rect shahab2Rect;
    shahab2Rect.x = rand() % 80 + 200;
    shahab2Rect.y = 0;
    shahab2Rect.w = 40;
    shahab2Rect.h = 50;
    /////////////////////////////////////////////
    SDL_Rect coinRect;
    coinRect.x = rand() % 80 + 200;
    coinRect.y = 0;
    coinRect.w = 50;
    coinRect.h = 40;
    /////////////////////////////////////////////
    SDL_Rect separRect;
    separRect.x = rand() % 80 + 200;
    separRect.y = 0;
    separRect.w = 50;
    separRect.h = 40;
    /////////////////////////////////////////////
    SDL_Rect gunRect;
    gunRect.x = rand() % 80 + 200;
    gunRect.y = 0;
    gunRect.w = 50;
    gunRect.h = 40;
    ////////////////////////////////////////////////
    SDL_Event e;
    bool turn = false;
    int x;
    while (!quit)
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 128, 255);
        SDL_RenderClear(gRenderer);
        // SDL_Rect gRect = {0, 625, 550, 75};
        // SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        // SDL_RenderFillRect(gRenderer, &gRect);
        SDL_RenderCopy(gRenderer, gTexture0, NULL, &rocketRect);
        SDL_RenderCopy(gRenderer, gTexture2, NULL, &divarRect);
        SDL_RenderCopy(gRenderer, gTexture3, NULL, &divar2Rect);
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (coinRect.y >= 710)
        {
            coinRect.w = 50;
            coinRect.h = 40;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (separRect.y >= 710)
        {
            separRect.w = 50;
            separRect.h = 40;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (gunRect.y >= 710)
        {
            gunRect.w = 50;
            gunRect.h = 40;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (shahab2)
        {
            shahab2Rect.w = 40;
            shahab2Rect.h = 50;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (shahab)
        {
            shahabRect.w = 55;
            shahabRect.h = 70;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (tir)
        {
            if (c.lahze_shelik)
            {
                c.x = rocketRect.x + 75 / 2;
                c.y = rocketRect.y;
                c.lahze_shelik = false;
            }
            filledCircleRGBA(gRenderer, c.x, c.y + c.v, 4, 255, 255, 255, 255);
        }
        if (!tir)
        {
            filledCircleRGBA(gRenderer, rocketRect.x + 75 / 2, rocketRect.y, 4, 255, 255, 255, 255);
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SDL_PollEvent(&e);
        {

            if (e.type == SDL_QUIT)
            {
                quit = true;
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
                break;
                }
            }
            if (flag == false && start == true)
            {
                x2 += 4;
                rocketRect.x = x2;
                if (ISlaunched)
                {
                    c.x = rocketRect.x;
                    c.y = rocketRect.y;
                }
            }
            else if (flag == true && start == true)
            {
                x2 -= 4;
                rocketRect.x = x2;
                if (ISlaunched)
                {
                    c.x = rocketRect.x;
                    c.y = rocketRect.y;
                }
            }
            if (rocketRect.x <= 15 || rocketRect.x >= 437)
            {
                quit = true;
                gGameover = SDL_LoadBMP("Gameover.bmp");
                gTexture10 = SDL_CreateTextureFromSurface(gRenderer, gGameover);
                SDL_RenderCopy(gRenderer, gTexture10, NULL, &gameoverRect);
                heigh(score);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(5000);
            }

            if (tir && gun == true)
            {
                ISlaunched = false;
                c.v -= 5;
                // c.y += c.v;
                if (c.y + c.v - 4 <= 2)
                {

                    tir = false;
                    ISlaunched = true;
                    c.x = rocketRect.x + 75 / 2;
                    c.y = rocketRect.x;
                    c.v = 0;
                }
            }
        }
        tirRect.x = c.x;
        tirRect.y = c.y;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (turn == false)
        {
            x = rand() % 1150;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // cout << x << endl;
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (x >= 1000 && x < 1150) //separ
        {
            turn = true;
            gTexture7 = SDL_CreateTextureFromSurface(gRenderer, gSepar);
            SDL_RenderCopy(gRenderer, gTexture7, NULL, &separRect);
            separRect.y += 5;

            if (separRect.y + 50 >= 800)
            {
                turn = false;
                score++;
                separRect.x = rand() % 120 + 220;
                separRect.y = -100;
            }
            if (SDL_HasIntersection(&rocketRect, &separRect) && !iscollided)
            {
                iscollided = true;
                separ = true;
                separRect.h = 0;
                separRect.w = 0;
                separcount += 1;
                // cout<<separcount<<endl;
            }
            if (iscollided)
                timer -= 0.1;
            if (timer < 0)
            {
                iscollided = false;
                timer = 3;
            }
        }

        if (x > 150 && x <= 450) //shahab koochik
        {
            turn = true;
            gTexture = SDL_CreateTextureFromSurface(gRenderer, gShahab);
            SDL_RenderCopy(gRenderer, gTexture, NULL, &shahab2Rect);
            shahab2Rect.y += 7;

            if (shahab2Rect.y + 50 >= 800)
            {
                shahab2 = true;
                turn = false;
                score++;
                shahab2Rect.x = rand() % 120 + 220;
                shahab2Rect.y = -100;
            }
            if (SDL_HasIntersection(&rocketRect, &shahab2Rect) && !cshahab2)
            {
                cshahab2 = true;
                if (!separ)
                {
                    // cout<<separcount<<endl;
                    quit = true;
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                    SDL_RenderClear(gRenderer);
                    gGameover = SDL_LoadBMP("Gameover.bmp");
                    gTexture10 = SDL_CreateTextureFromSurface(gRenderer, gGameover);
                    SDL_RenderCopy(gRenderer, gTexture10, NULL, &gameoverRect);
                    heigh(score);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(5000);
                }
                else if (separ)
                {
                    //cout<<separcount<<endl;
                    separcount--;
                    if (separcount == 0)
                    {
                        separ = false;
                    }
                    // cout<<separcount<<endl;
                }
            }
            if (cshahab2)
                timershahab2 -= 0.1;
            if (timershahab2 < 0)
            {
                cshahab2 = false;
                timershahab2 = 3;
            }
            if (c.y + c.v - 4 < shahab2Rect.y && c.x + 4 >= shahab2Rect.x && c.x + 4 <= shahab2Rect.x + shahab2Rect.w)
            {

                shahab2Rect.w = 0;
                shahab2Rect.h = 0;
                if (shahab2Rect.y >= 710)
                {
                    shahab2 = true;
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (x > 450 && x <= 900) //shahab bozorg
        {
            turn = true;
            gTexture = SDL_CreateTextureFromSurface(gRenderer, gShahab);
            SDL_RenderCopy(gRenderer, gTexture, NULL, &shahabRect);
            shahabRect.y += 5;

            if (shahabRect.y + 75 >= 800)
            {
                shahab = true;
                score++;
                turn = false;
                shahabRect.x = rand() % 120 + 220;
                shahabRect.y = -100;
            }
            if (SDL_HasIntersection(&rocketRect, &shahabRect) && !cshahab)
            {
                cshahab = true;

                if (!separ)
                {
                    cout << separcount << endl;
                    quit = true;
                    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
                    SDL_RenderClear(gRenderer);
                    gGameover = SDL_LoadBMP("Gameover.bmp");
                    gTexture10 = SDL_CreateTextureFromSurface(gRenderer, gGameover);
                    SDL_RenderCopy(gRenderer, gTexture10, NULL, &gameoverRect);
                    // cout << 50000000 << endl;
                    heigh(score);
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(5000);
                }
                else if (separ)
                {
                    // cout<<separcount<<endl;
                    separcount--;
                    if (separcount == 0)
                    {
                        separ = false;
                    }

                    //  cout<<separcount<<endl;z
                }
            }
            if (cshahab)
                timershahab -= 0.1;
            if (timershahab < 0)
            {
                cshahab = false;
                timershahab = 3;
            }

            if (c.y + c.v - 4 < shahabRect.y && c.x + 4 >= shahabRect.x && c.x + 4 <= shahabRect.x + shahabRect.w)
            {

                shahabRect.w = 0;
                shahabRect.h = 0;
                if (shahabRect.y >= 710)
                {
                    shahab = true;
                }
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (x < 1000 && x > 900) //gun
        {
            turn = true;

            gTexture = SDL_CreateTextureFromSurface(gRenderer, gGun);
            SDL_RenderCopy(gRenderer, gTexture, NULL, &gunRect);
            gunRect.y += 5;

            if (gunRect.y + 40 >= 800)
            {
                turn = false;
                score++;
                gunRect.x = rand() % 120 + 220;
                gunRect.y = -100;
            }
            if (SDL_HasIntersection(&rocketRect, &gunRect))
            {
                gun = true;
                gunRect.h = 0;
                gunRect.w = 0;
            }
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (x <= 150 && x >= 0) //coin
        {
            turn = true;
            gTexture = SDL_CreateTextureFromSurface(gRenderer, gCoin);
            SDL_RenderCopy(gRenderer, gTexture, NULL, &coinRect);
            coinRect.y += 5;

            if (coinRect.y + 40 >= 800)
            {
                turn = false;
                score++;
                coinRect.x = rand() % 120 + 220;
                coinRect.y = -100;
            }
            if (SDL_HasIntersection(&rocketRect, &coinRect))
            {
                coincounter++;
                coinRect.h = 0;
                coinRect.w = 0;
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ScoreRender(gRenderer, score, gFont);

        SDL_RenderPresent(gRenderer);
        framestart = SDL_GetTicks();
        frametime = SDL_GetTicks() - framestart;
        if (framedelay > frametime)
        {
            SDL_Delay(framedelay - frametime);
        }
    }

    return 0;
}