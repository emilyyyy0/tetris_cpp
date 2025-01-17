/********
 * 
 * File: Main.cpp
 * 
 * Description: Tetris Tutorial adapted from https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/
 * 
 * The main loop of the game. In each frame we draw everything. 
 * Before each movement, we first check out if it is possible, we also measure the time in order to move the piece down 
 * every n milliseconds. 
 * When the piece falls down one block, we check out if the movement is possible, if not, we store the piece in the board. 
 * We also check out if there are blocks in the upper row, if so, the game is over. 
 * 
 * 
 */



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


        // ---- Input ----- 
        int mKey = mIO.Pollkey();  

        switch (mKey)
        {
            case (SDLK_RIGHT):
            {
                if (mBoard.IsPossibleMovement (mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                    mGame.mPosX++; 
                    break; 
            }

            case (SDLK_LEFT):
            {
                if (mBoard.IsPossibleMovement (mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;	
				break;
            }

            case (SDLK_DOWN):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;	
				break;
			}

            case (SDLK_x):
			{
				// Check collision from up to down
				while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }
	
				mBoard.StorePiece (mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines ();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_z):
			{
				if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
					mGame.mRotation = (mGame.mRotation + 1) % 4;

				break;
			}

        }




        

        // ---- Vertical Movement ---- 
        unsigned long mTime2 = SDL_GetTicks(); 

        if ((mTime2 - mTime1) > WAIT_TIME)
        {
            if (mBoard.IsPossibleMovement (mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
            {
                mGame.mPosY++; 
            }
            else 
            {
                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation); 

                mBoard.DeletePossibleLines(); 

                if (mBoard.IsGameOver())
                {
                    mIO.Getkey(); 
                    exit(0); 
                }
                mGame.CreateNewPiece(); 
            }
            mTime1 = SDL_GetTicks(); 
        }
        
    }

    return 0; 

}