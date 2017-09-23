#ifndef CONSTANTS_H
#define CONSTANTS_H

const int FPS = 60;
const double SPF = 1 / FPS;

const int RATIO_H = 4;
const int RATIO_W = 4;
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 600;//SCREEN_WIDTH * RATIO_H / RATIO_W;

static const int GRID_WIDTH = 10;
static const int GRID_HEIGHT = 15;
static const int GRID_BUFFER = 4;

static enum COLOUR
{
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	PURPLE,
	WHITE,
	NONE,
	NUMBER_COLOURS
};

static enum SHAPE
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};


#endif