
#include "Game.h"
#include "IO.h"
#include <iostream>

using namespace std; 

int main(int argc, char* args[]) 
{
    // ---- Vars ----
    // Class for drawing, uses SDL2 for the rendering. 
    IO mIO; 
    int mScreenHeight = mIO.GetScreenHeight(); 
    
    // cout << mScreenHeight << endl;

    // Pieces 
    Pieces mPieces; 

    // Board
    Board mBoard(&mPieces, mScreenHeight); 

    // Game
    Game mGame (&mBoard, &mPieces, &mIO, mScreenHeight); 

    // Get the actual clock milliseconds (SDL)
    unsigned long mTime1 = SDL_GetTicks(); 

    // ---- Main Loop -----

    while (!mIO.IsKeyDown (SDLK_ESCAPE))
    {
        // ---- Draw -----
        mIO.ClearScreen(); // Clear Screen
        mGame.DrawScene(); // Draw staff

        // Present the rendered frame
        mIO.PresentScreen(); 
        
    }

    // Keep the window open for 5 seconds
    //SDL_Delay(5000);

    return 0; 


}