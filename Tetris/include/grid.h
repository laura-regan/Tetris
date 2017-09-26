#ifndef GRID_H
#define GRID_H

#include <vector>
#include <stdlib.h>




#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "tetromino.h"




class Grid
{
public:
	int tetrominoStaticFallSpeed = 10;
	
	int tetrominoDynamicFallSpeed1 = 350;
	int tetrominoDynamicFallSpeed2 = 30;
	int tetrominoDynamicFallSpeed = 350;

	Grid();

	void CreateTetromino( int colour );

	void Render();

	void Physics( int delta );

	void Input( SDL_Event e );

	void RemoveFullRow();

	void FragmentTetrominos();

	void ClearDeadTetrominos();

private:
	std::vector<Tetromino > LTetromino;
	int numTetrominos;

	bool IsFreeToFall( int index );

	bool HasCollided( int index );
};



#endif


