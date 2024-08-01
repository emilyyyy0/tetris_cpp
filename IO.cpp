/*****************************************************************************************
/* File: IO.cpp
/* Desc: Class for handling input & drawing, it uses SDL2 for the rendering. Change the methods 
/* of this class in order to use a different renderer
/*       
/*
/* gametuto.com - Javier López López (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share — to copy, distribute and transmit the work
/*	to Remix — to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

// ------ Includes -----

#include "IO.h"

static SDL_Window* mWindow = nullptr;
static SDL_Renderer* mRenderer = nullptr;
static SDL_Color mColors [COLOR_MAX] = {
    {0, 0, 0, 255},       // BLACK
    {255, 0, 0, 255},     // RED
    {0, 255, 0, 255},     // GREEN
    {0, 0, 255, 255},     // BLUE
    {0, 255, 255, 255},   // CYAN
    {255, 0, 255, 255},   // MAGENTA
    {255, 255, 0, 255},   // YELLOW
    {255, 255, 255, 255}  // WHITE
};

IO::IO() 
{
    InitGraph();
}

void IO::ClearScreen() 
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}

void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    SDL_Rect rect = {pX1, pY1, pX2 - pX1, pY2 - pY1};
    SDL_SetRenderDrawColor(mRenderer, mColors[pC].r, mColors[pC].g, mColors[pC].b, mColors[pC].a);
    SDL_RenderFillRect(mRenderer, &rect);
}

int IO::GetScreenHeight()
{
    int h;
    SDL_GetRendererOutputSize(mRenderer, nullptr, &h);
    return h;
}

void IO::UpdateScreen()
{
    SDL_RenderPresent(mRenderer);
}

int IO::Pollkey()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) {
            case SDL_KEYDOWN:
                return event.key.keysym.sym;
            case SDL_QUIT:
                exit(3);
        }
    }
    return -1;
}

int IO::Getkey()
{
    SDL_Event event;
    while (true)
    {
      SDL_WaitEvent(&event);
      if (event.type == SDL_KEYDOWN)
          break;
      if (event.type == SDL_QUIT)
          exit(3);
    };
    return event.key.keysym.sym;
}

int IO::IsKeyDown(int pKey)
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_GetScancodeFromKey(pKey)];
}

int IO::InitGraph()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);

    mWindow = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                               640, 480, SDL_WINDOW_SHOWN);
    if (mWindow == nullptr) {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
        return 2;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr) {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        return 3;
    }

    return 0;
}