#ifndef CONSTANTS_H
#define CONSTANTS_H

/// Frames-per-Second and Seconds-per-Frame
const int FPS = 60;
const double SPF = 1 / FPS;

/// Window Aspect Ratio
const int RATIO_H = 10;
const int RATIO_W = 16;

/// Window Dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = SCREEN_WIDTH * RATIO_H / RATIO_W;

static const int GRID_WIDTH = 10;
static const int GRID_HEIGHT = 20;

static const int SIDE_BORDER = SCREEN_WIDTH * 0.2;
static const int TOP_BORDER = (( SCREEN_WIDTH - SIDE_BORDER * 2 ) * GRID_HEIGHT / GRID_WIDTH) / 2;

static const int GRID_WIDTH_PIXELS = SCREEN_WIDTH - SIDE_BORDER * 2;
static const int GRID_HEIGHT_PIXELS = SCREEN_HEIGHT - TOP_BORDER * 2;

static const int BLOCK_WIDTH = GRID_HEIGHT_PIXELS / GRID_WIDTH;

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
	BLACK,
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