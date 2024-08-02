
#include "IO.h"

static SDL_Window *mWindow; 
static SDL_Renderer *mRenderer; 

static SDL_Color mColors[COLOR_MAX] = {
    {0, 0, 0, 255},       // Black
    {255, 0, 0, 255},     // Red
    {0, 255, 0, 255},     // Green
    {0, 0, 255, 255},     // Blue
    {0, 255, 255, 255},   // Cyan
    {255, 0, 255, 255},   // Magenta
    {255, 255, 0, 255},   // Yellow
    {255, 255, 255, 255}  // White
};

/* 
======================================									
Init
====================================== 
*/
IO::IO() 
{
	InitGraph ();
}

/* 
======================================									
Clear the screen to black
====================================== 
*/
void IO::ClearScreen() 
{
    // Set draw color to black using the first color in mColors array 
    SDL_SetRenderDrawColor(mRenderer, 
                            mColors[BLACK].r, 
                            mColors[BLACK].g, 
                            mColors[BLACK].b, 
                            mColors[BLACK].a); 
    
    // Clear the entire screen to the set color 
    SDL_RenderClear(mRenderer); 
}

/* 
======================================									
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
====================================== 
*/
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC) 
{
    // Set the draw color 
    SDL_SetRenderDrawColor(mRenderer, 
                            mColors[pC].r, 
                            mColors[pC].g, 
                            mColors[pC].b, 
                            mColors[pC].a); 
    
    // Create a rectangle 
    SDL_Rect rect; 
    rect.x = pX1; 
    rect.y = pY1; 
    rect.w = pX2 - pX1 + 1; 
    rect.h = pY2 - pY1 + 1; 

    // Draw filled rectangle
    SDL_RenderFillRect(mRenderer, &rect); 
}




/* 
======================================									
Return the screen height
====================================== 
*/
int IO::GetScreenHeight()
{
	int height; 
    SDL_GetWindowSize(mWindow, NULL, &height); 
    return height; 
}


/* 
======================================									
Update screen
====================================== 
*/
void IO::UpdateScreen()
{
    SDL_RenderPresent(mRenderer); 
}


/* 
======================================									
Keyboard Input
====================================== 
*/
int IO::Pollkey()
{
	SDL_Event event;
	while ( SDL_PollEvent(&event) ) 
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


/* 
======================================									
Keyboard Input
====================================== 
*/
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


/* 
======================================									
Keyboard Input

Returns 1 for a pressed key and 0 for a released key 
====================================== 
*/
int IO::IsKeyDown(int pKey)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL); 
    SDL_PumpEvents(); 
    return state[SDL_GetScancodeFromKey(pKey)]; 
}




/* 
======================================									
SDL Graphical Initialization
====================================== 
*/
int IO::InitGraph() 
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialise SDL: %s\n", SDL_GetError()); 
        return 1; 
    }
    atexit(SDL_Quit); 

    // Create window 
    mWindow = SDL_CreateWindow("Tetris", 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                640, 480, 
                                SDL_WINDOW_SHOWN); 
    
    if (mWindow == NULL) {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError()); 
        return 2; 
    }

    // Create renderer 
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  
    if (mRenderer == NULL) {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError()); 
        return 3; 
    }

    return 0; 
}


/* 
======================================									
Present the rendered frame 
====================================== 
*/
void IO::PresentScreen() 
{
    SDL_RenderPresent(mRenderer);
}