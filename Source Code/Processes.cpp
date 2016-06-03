#include "Processes.h"
#include <iostream>
#include <ctime>
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 600;

//Returns the rectangles in a PongGroup struct with their positions.

PongGroup createRects()
{


	PongGroup gamePieces;

	srand(time(0));
	//Left Paddle
	gamePieces.Paddle1.h = SCREEN_HEIGHT - 400;
	gamePieces.Paddle1.w = SCREEN_WIDTH / 30;
	gamePieces.Paddle1.x = 30;
	gamePieces.Paddle1.y = SCREEN_HEIGHT - gamePieces.Paddle1.h - 100;

	//Right Paddle
	gamePieces.Paddle2.h = SCREEN_HEIGHT - 400;
	gamePieces.Paddle2.w = SCREEN_WIDTH / 30;
	gamePieces.Paddle2.x = SCREEN_WIDTH - 60;
	gamePieces.Paddle2.y = SCREEN_HEIGHT - gamePieces.Paddle2.h - 100;

	//The Ball
	gamePieces.ball.h = 10;
	gamePieces.ball.w = 10;
	gamePieces.ball.x = (SCREEN_HEIGHT / 2) - 10;
	gamePieces.ball.y = (rand()%300)+100;


	return gamePieces;
}



void initializeScreen(PongGroup Game, SDL_Renderer * mainRender)
{
	SDL_SetRenderDrawColor(mainRender, 255, 255, 255, 0);
	SDL_RenderDrawRect(mainRender, &Game.Paddle1);
	SDL_RenderDrawRect(mainRender, &Game.Paddle2);
	SDL_RenderDrawRect(mainRender, &Game.ball);
	SDL_RenderFillRect(mainRender, &Game.Paddle1);
	SDL_RenderFillRect(mainRender, &Game.Paddle2);
	SDL_RenderFillRect(mainRender, &Game.ball);
}

void redrawGamepieces(PongGroup Game, SDL_Renderer * mainRender)
{
	SDL_SetRenderDrawColor(mainRender, 255, 255, 255, 0);
	SDL_RenderDrawRect(mainRender, &Game.Paddle1);
	SDL_RenderDrawRect(mainRender, &Game.Paddle2);
	SDL_RenderDrawRect(mainRender, &Game.ball);

	SDL_RenderFillRect(mainRender, &Game.Paddle1);
	SDL_RenderFillRect(mainRender, &Game.Paddle2);
	SDL_RenderFillRect(mainRender, &Game.ball);
}

int ballMotionx()
{
	srand(time(0) / rand());
	int x = ((rand() % 30) - 16);
	return x;
}

int ballMotiony()
{
	srand(time(0) * rand());
	int y = ((rand() % 30) - 16);
	return y;
}

void readPosition(int x, int y)
{
	if (x % 10 == 0)
	{
		std::cout << "Ball X: " << x;
		std::cout << '\t' << "Ball Y: " << y << '\n';
	}
}

int updateSpeedx(int x,int y, int speedx, SDL_Rect positions, SDL_Rect positions2)
{
	int backupSpeed = speedx;


	if ((x < positions.x + positions.w) && ((y < positions.y + positions.h) && (y > positions.y)))
	{
		speedx = speedx * (-1);
	}

	if ((x > SCREEN_WIDTH))
	{
		speedx = speedx * (-1);
	}

	if ((x > positions2.x) && (y < positions2.y + positions2.h) && (y > positions2.y))
	{
		speedx = speedx * (-1);

	}
	else
	{
		speedx = speedx;
	}

	


	return speedx;
}

int updateSpeedy(int y, int speedy, SDL_Rect positions)
{
	if (y < 0)
	{
		speedy = speedy * (-1);
	}

	if (y > SCREEN_HEIGHT)
	{
		speedy = speedy * (-1);
	}

	else
	{
		speedy = speedy;
	}

	return speedy;
}

void gameLoop(PongGroup Game, SDL_Renderer  * mainRender)
{
	bool quit(false);

	srand(time(0));
	int ballSpeedx = ballMotionx();
	int ballSpeedy = ballMotiony();


	//The event for key pressess
	SDL_Event e;
	while (!quit)
	{
		{
			SDL_PollEvent(&e);
			
			//Initialize the screen (make it all black)
			SDL_SetRenderDrawColor(mainRender, 0, 0, 0, 0);
			SDL_RenderClear(mainRender);

			if (e.type == SDL_QUIT)
			{
				std::cout << "EXITING PONG...\n";
				SDL_DestroyRenderer(mainRender);
				break;
			}

			if (e.type = SDL_MOUSEMOTION)
			{
				Game.Paddle1.y = e.motion.y;
			}

			
			ballSpeedx = updateSpeedx(Game.ball.x, Game.ball.y, ballSpeedx, Game.Paddle1, Game.Paddle2);
			ballSpeedy = updateSpeedy(Game.ball.y, ballSpeedy, Game.Paddle1);
			

			Game.ball.x = Game.ball.x + ballSpeedx;
			Game.ball.y = Game.ball.y + ballSpeedy;
			
			readPosition(Game.ball.x, Game.ball.y);
			
			if (Game.ball.x % 10 == 0)
			{
				SDL_RenderDrawPoint(mainRender, Game.ball.x, Game.ball.y);
			}

			//Draw the paddles
			redrawGamepieces(Game, mainRender);

			//update the render
			SDL_RenderPresent(mainRender);

			if ((Game.ball.x < 0) || (Game.ball.x > SCREEN_WIDTH))
			{
				int ballSpeedx = ballMotionx();
				int ballSpeedy = ballMotiony();
				Game.ball.x = (SCREEN_HEIGHT / 2) - 10;
				Game.ball.y = (rand() % 300) + 100;
			}
		}
	}

}
