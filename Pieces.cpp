/******************************
 * File: Pieces.cpp
 * Description: All the Tetris pieces with their respective rotations and displacements for the hotspot 
 * 
 * There are 7 different types of pieces: Square, I, L, L-mirrored, N, N-mirrored and T. 
 * Each piece is desfined in a matrix of 5x5 cells. 0 means <<no block>>, 1 means <<normal block>> and 2 means <<pivot block>>. 
 * The pivot block is the rotation point. 
    [c language=»++»]
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 2, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
    [/c]
 * 
 * To do the rotations, we can store each piece rotated too. There are four possible rotations for each piece. 
 * 
 * In order to store all these pieces, we need a 4-dimensional array to store 4 possible rotations. 
 * 
 */

#include "Pieces.h"

// Pieces definition 
// Store the pieces in a 4 dimensional array 
char mPieces[7 /* kind */][4 /*possible rotations*/][5][5] = // store each piece in a 5x5 matrix [5 horizontal][5 vertical]
{
    // Square
    {
        {
            {0,0,0,0,0}, 
            {0,0,0,0,0}, 
            {0,0,2,1,0}, 
            {0,0,1,1,0}, 
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0}, 
            {0,0,0,0,0}, 
            {0,0,2,1,0}, 
            {0,0,1,1,0}, 
            {0,0,0,0,0}
        }, 
        {
            {0,0,0,0,0}, 
            {0,0,0,0,0}, 
            {0,0,2,1,0}, 
            {0,0,1,1,0}, 
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0}, 
            {0,0,0,0,0}, 
            {0,0,2,1,0}, 
            {0,0,1,1,0}, 
            {0,0,0,0,0}
        }
    }, 
    // I
    {
        {
            {0,0,0,0,0}, 
            {0,0,0,0,0}, 
            {0,1,2,1,1}, 
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }, 

    // L
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }, 
    // L Mirrored
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        }
    }, 
    // N 
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }, 
    // N Mirrored
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }, 
    // T
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }, 
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }
}; 

// Each piece must be correctly positioned every time it is created on the top of the screen. 
// It needs to be translated to the correct position 
// We want to shot ONLY one row of blocks in the board and to be centered, upper blocks should be OUTSIDE the board. 
// Each piece is different, therefore each one needs a different translation every time it is created. 
// We will sotre there translation in another array, one translation per rotated piece. 
// Displacement of the piece to the position where it is first drawn in the board when it is created. 
int mPiecesInitialPosition [7 /* kind */][4 /* rotation */][ 2 /* position */] = 
{
    /* Square */
  {
	{-2, -3}, 
    {-2, -3},
    {-2, -3},
    {-2, -3}
   },
/* I */
  {
	{-2, -2}, //horizontal 
    {-2, -3}, // vertical
    {-2, -2}, // horizontal 
    {-2, -3} // vertical 
   },
/* L */
  {
	{-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
   },
/* L mirrored */
  {
	{-2, -3},
    {-2, -2},
    {-2, -3},
    {-2, -3}
   },
/* N */
  {
	{-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
   },
/* N mirrored */
  {
	{-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
   },
/* T */
  {
	{-2, -3},
    {-2, -3},
    {-2, -3},
    {-2, -2}
   },
}; 


/*
=====================================================================================
Return the type of a block (0 = no-block, 1 = normal block, 2 = pivot block)

Parameters:

>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
>> pX: Horizontal position of blocks 
>> pY: Vertical position of blocks 
======================================================================================
*/
int Pieces::GetBlockType(int pPiece, int pRotation, int pX, int pY) 
{
    return mPieces[pPiece][pRotation][pX][pY];
}

/*
=====================================================================================
Returns the horizontal displacement that has to be applied to the piece in order to 
create it in the correct position 

Parameters:

>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================================================================
*/
int Pieces::GetXInitialPosition(int pPiece, int pRotation) {
    return mPiecesInitialPosition[pPiece][pRotation][0];
}


/*
=====================================================================================
Returns the vertical displacement that has to be applied to the piece in order to 
create it in the correct position 

Parameters:

>> pPiece: Piece to draw
>> pRotation: 1 of the 4 possible rotations
======================================================================================
*/
int Pieces::GetYInitialPosition(int pPiece, int pRotation) {
    return mPiecesInitialPosition[pPiece][pRotation][1];
}