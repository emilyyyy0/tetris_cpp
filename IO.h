/********
 * 
 * File: IO.h
 * 
 * Description: Class for handling input & drawing, it uses SDL2 for the rendering. 
 * 
 * SDL2 is used to create the window, clear it, update the screen and take care of the keyboard input. 
 * 
 */


#ifndef _IO_
#define _IO_

// ---- Includes ----

#include <SDL2/SDL.h> 
#include <SDL2/SDL2_gfxPrimitives.h>

// ----- Enums ------

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors 

// --------------------------------------------------------------------------------
//									 IO
// --------------------------------------------------------------------------------

class IO 
{
    public:

        IO (); 

        void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC); 
        void ClearScreen(); 
        int GetScreenHeight(); 
        int InitGraph(); 
        int Pollkey(); 
        int Getkey(); 
        int IsKeyDown(int pKey); 
        void UpdateScreen(); // the same as PresentScreen() 
        void PresentScreen(); 
}; 

#endif // _IO_
