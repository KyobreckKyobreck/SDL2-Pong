#include <SDL.h>
#include <stdio.h>
#include <ostream>
#include <cmath>
#pragma once

//A struct to hold the rectangles (paddle1, paddle2, ball)
struct PongGroup
{
	SDL_Rect Paddle1;
	SDL_Rect Paddle2;
	SDL_Rect ball;
};

//Returns the rectangles in a PongGroup struct with their positions.
PongGroup createRects();

//Set up the screen with the rects
void initializeScreen(PongGroup Game, SDL_Renderer * mainRender);

//redraw the screen
void redrawGamepieces(PongGroup Game, SDL_Renderer * mainRender);

//The function that calls all these other ones and don't quit
void gameLoop(PongGroup Game, SDL_Renderer  * mainRender);

//Randomly generate a y speed for our ball
int ballMotiony();

//Randomly generate an x speed for our ball
int ballMotionx();

//Read out the position of our ball
void readPosition(int x, int y);

void updateSpeed(int x, int y);