
// ----- Includes -----

#include "Board.h"

/*
==================
Init
==================
*/
Board::Board (Pieces *pPieces, int pScreenHeight)
{
    // Get the screen height
    mScreenHeight = pScreenHeight; 

    // Get the pointer to the pieces class; 
    mPieces = pPieces; 

    // Init the board blocks with free positions
    InitBoard(); 
}

// Board [column][row]

/*
======================================									
Init the board blocks with free positions
====================================== 
*/
void Board::InitBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = POS_FREE; 
        }
    }
}

/* 
======================================									
Store a piece in the board by filling the blocks

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
>> pPiece:	Piece to draw
>> pRotation:	1 of the 4 possible rotations
====================================== 
*/
void Board::StorePiece (int pX, int pY, int pPiece, int pRotation) 
{
    // Store each block of the piece into the board 
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
        //i1 for the board and i2 for the piece matrix 
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
            // Store only the blocks of the piece that are not holes
            if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) {
                mBoard[i1][j1] = POS_FILLED; 
            }
        }
    }
}

/* 
======================================									
Check if the game is over becase a piece have achived the upper position

Returns true or false
====================================== 
*/
bool Board::IsGameOver()
{
    // If the first line has blocks, then, game over 
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) return true; 
    }
    return false; 
}

/* 
======================================									
Delete a line of the board by moving all above lines down
DeleteLine starts from the line that has to be removed, and then, iterating through the board in a nested loop, moves all the blcoks of the upper
lines one row down. 

Parameters:

>> pY:		Vertical position in blocks of the line to delete
====================================== 
*/
void Board::DeleteLine(int pY)
{
    // Moves all the upper lines one row down 
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
}



/* 
======================================									
Delete all the lines that should be removed

First check which lines whould be removed (the ones that have their horizontal blocks filled). 
Then use the DeleteLine method in order to erase that line and move all the upper lines one row down 
====================================== 
*/

void Board::DeletePossibleLines ()
{
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int i = 0; 
        while (i < BOARD_WIDTH) {
            if (mBoard[i][j] != POS_FILLED) break; 
            i++; 
        }

        if (i == BOARD_WIDTH) DeleteLine(j); 
    }
}

/* 
======================================									
Returns 1 (true) if the this block of the board is empty, 0 if it is filled

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
====================================== 
*/
bool Board::IsFreeBlock (int pX, int pY) 
{
    if (mBoard[pX][pY] == POS_FREE) return true; else return false; 
}

/*
In order to draw blcoks onto the screen, we need to specify the position in pixels. 
Need GetXPosInPixels and GetYPosInPixels methods in order to obtain the horizontal and vertical 
positions in pixels of a given block. 
*/

/* 
======================================									
Returns the horizontal position (in pixels) of the block given like parameter

Parameters:

>> pPos:	Horizontal position of the block in the board

BOARD_POSITION = Center of the board from the left of the screen, e.g., 320 pixels.
BLOCK_SIZE = 16 pixels
BOARD_WIDTH = 10 blocks

BLOCK_SIZE * (BOARD_WIDTH / 2): Half width of board in pixels, 16 * (10 / 2) = 16 * 5 = 80

BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)): Calculates the leftmost pixel position of the board, aligning it within the screen by centering it based on BOARD_POSITION
E.g. 320 - 80 = 240 pixels

(( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE)): Combines the starting pixel position of the board with the block position in pixels.
E.g. pPos = 3, 240 + (3 * 16) = 288 pixels

====================================== 
*/

int Board::GetXPosInPixels(int pPos) 
{
    return (( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}


/* 
======================================									
Returns the vertical position (in pixels) of the block given like parameter

Parameters:

>> pPos:	Horizontal position of the block in the board

BLOCK_SIZE * BOARD_HEIGHT = total height of the board in pixels 
mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT): Top position of the board 

====================================== 
*/

int Board::GetYPosInPixels(int pPos) 
{
    return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}



//IsPossibleMovement
/*
This method will be used in the main loop to check if the movement of a piece is possible or not. 
The method compares all the blcoks of a piece with the blocks already stored in the board and with the board limits
This comparison is made by iterating through the piece matrix and comparing with the appropriate 5x5 area in the board. 
If there is a collision, that means the movement is not possible, so it returns false. 
If there is no collision, the movement is possible and it returns true. 
*/
/* 
======================================									
Check if the piece can be stored at this position without any collision
Returns true if the movement is  possible, false if it not possible

Parameters:

>> pX:		Horizontal position in blocks
>> pY:		Vertical position in blocks
>> pPiece:	Piece to draw
>> pRotation:	1 of the 4 possible rotations
====================================== 
*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) 
{
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appriprate area in the board
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++){
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
        {
            // Check if the piece is outside the limits of the board 
            if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1) {
                if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) {
                    return 0; 
                }
            }

            // Check if the piece have collisioned with a block already stored int he map 
            if (j1 >= 0) {
                if ((mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0) && 
                        (!IsFreeBlock(i1, j1))) {
                            return false; 
                        }
            }

        }
    }
    // No collision
    return true;
}