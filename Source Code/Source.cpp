#include <SDL.h>
#include <stdio.h>
#include <ostream>
#include <iostream>
#include <cmath>
#include "Processes.h"

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 600;

int main(int argc, char *args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	PongGroup  Game = createRects();
	
	//Our window and our renderer
	SDL_Window * mainWindow = SDL_CreateWindow("| P o  NG |", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * mainRender = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	
	//INITIAL DRAWING
	//Initialize the screen (make it all black)
	SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 0);
	SDL_RenderClear(mainRender);

	//Draw the paddles
	initializeScreen(Game, mainRender);
	
	//update the render
	SDL_RenderPresent(mainRender);

	gameLoop(Game, mainRender);
	std::cout << "EXITED...\n";
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	return 0;
}