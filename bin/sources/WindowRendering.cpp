#include "WindowRendering.h"

#include <iostream>


WindowRendering *WindowRendering::pInstance = nullptr;

WindowRendering *WindowRendering::getInstance()
{
	if(!pInstance)
	{
		pInstance = new WindowRendering();
	}
	return pInstance;
}

WindowRendering::WindowRendering()
{
	gWindow = nullptr;
	gRenderer = nullptr;
	gTextureBuffer = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{ // failed to initialize video
		std::cerr << "failed to initialize SDL Video! SDL_Error: " << SDL_GetError() << "\n";
		exit(1); // exit out the game
	} else
	{
		gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP); //create fullscreen window

		if(!gWindow)
		{
			std::cerr << "failed to create window! SDL_Error: " << SDL_GetError() << "\n";
			exit(1); // exit out the game
		} else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //create renderer
			if(!gRenderer)
			{
				std::cerr << "failed to create renderer! SDL_Error: " << SDL_GetError() << "\n";
				exit(1); // exit out the game
			} else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); //draw in white
				
				//initialize png loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) //load png and make sure it actuall was png
				{ 
					std::cerr << "SDL_Image failed to initialize! IMG_Error:" << IMG_GetError() << "\n";
					exit(1); //fail out the program
				} else
				{
					windowHeight = SDL_GetWindowSurface(gWindow)->h;
					windowWidth = SDL_GetWindowSurface(gWindow)->w;
				}

			}
		}
	}

	// make the walls
	topWall.x = 0;
	topWall.y = 0;
	topWall.h = 10;
	topWall.w = windowWidth;

	bottomWall.x = 0;
	bottomWall.y = windowHeight-10;
	bottomWall.h = 10;
	bottomWall.w = windowWidth;

	leftWall.x = 0;
	leftWall.y = 0;
	leftWall.w = 10;
	leftWall.h = windowHeight;

	pColliders->addCollider(TOPWALL_COLLIDER, &topWall);
	pColliders->addCollider(BOTTOMWALL_COLLIDER, &bottomWall);
	pColliders->addCollider(LEFTWALL_COLLIDER, &leftWall);
}

void WindowRendering::clearBuffer()
{
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00); //make the next thing I draw black
	SDL_RenderClear( gRenderer ); //draw all black to screen
}

void WindowRendering::close()
{
	SDL_DestroyTexture(gTextureBuffer);
	gTextureBuffer = nullptr;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = nullptr;
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

void WindowRendering::drawWalls()
{ // draw walls on three sides
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // make the next thing I draw white

	SDL_RenderFillRect(gRenderer, &topWall);
	SDL_RenderFillRect(gRenderer, &bottomWall);
	SDL_RenderFillRect(gRenderer, &leftWall);
}

void WindowRendering::drawSolidRect(SDL_Rect *shape)
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF); // make the next thing I draw white
	SDL_RenderFillRect(gRenderer, shape);
}
