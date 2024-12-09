#include "WindowRendering.h"
#include "Paddle.h"
#include "Dot.h"
#include <SDL.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>

int main(int argc, char *args[])
{
	srand(time(0));

	WindowRendering *pWindowRenderer = WindowRendering::getInstance();
	SDL_Event event;
	Paddle paddle;
	Dot dot;

	// write initial black screen
	pWindowRenderer->clearBuffer();
	pWindowRenderer->drawWalls();
	pWindowRenderer->renderPresent();

	// hang around until I hit escape
	bool quit = 0;
	while(!quit)
	{
		while (SDL_PollEvent ( &event ) != 0)
		{ // an event happened
			if (event.type == SDL_QUIT)
			{
				quit = 1;
				pWindowRenderer->close();
			} 

			paddle.handleEvent(event); //the paddle can handle it's own events
		}

		paddle.move(); //move the paddle
		dot.move();

		//rerender
		pWindowRenderer->clearBuffer();
		pWindowRenderer->drawWalls();
		paddle.render();
		dot.render();
		pWindowRenderer->renderPresent();
	}

	return 1;
}
