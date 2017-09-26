#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL.h>

#include <vector>
#include <cmath>

#include "constants.h"
#include "globals.h"
#include "functions.h"




enum DIRECTIONS
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


struct Point
{
	int x, y;
	int a, b;

	bool operator==( Point p )
	{
		return ( x == p.x && y == p.y );
	}

	void RotateRight()
	{
		if ( a >= 0 && b >= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = abs( b );
		}
		else if ( a <= 0 && b >= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = -1 * abs( b );
		}
		else if ( a <= 0 && b <= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = -1 * abs( b );
		}
		else if ( a >= 0 && b <= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = abs( b );
		}
	}

	void RotateLeft()
	{
		if ( a >= 0 && b >= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = -1 * abs( b );
		}
		else if ( a <= 0 && b >= 0 )
		{
			Swap( a, b );
			a = abs( a ); b = abs( b );
		}
		else if ( a <= 0 && b <= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = abs( b );
		}
		else if ( a >= 0 && b <= 0 )
		{
			Swap( a, b );
			a = -1 * abs( a ); b = -1 * abs( b );
		}
	}
};

class Tetromino
{
public:

	/// Constructors 
	Tetromino() {};

	Tetromino( int shape, int a, int b );

	/// Rendering
	void Render();

	/// Movement
	void Rotate( DIRECTIONS dir );
	void Move( DIRECTIONS dir );

	/// Collision detection
	bool IsOverlapping( Tetromino t );
	bool IsOutOfBoundsX();
	bool IsOutOfBoundsY();

	/// Get functions
	int GetShape()
	{
		return shape;
	}


	/// Query and Modify Tetromino functions
	int NumPointsInRow( int row );
	void RemovePoint( int index );
	void Copy();
	Tetromino* Fragment();
	bool HasNeighbours( int index );
	bool IsEmpty();


private:

	int shape;
	std::vector<Point> LPoint;
};
















#endif

