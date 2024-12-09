#ifndef WINDOWRENDERING_HEADER
#define WINDOWRENDERING_HEADER

#include <SDL.h>
#include <SDL_image.h>
#include "Colliders.h"

class WindowRendering
{
private:
	// singleton crud
	WindowRendering();
	~WindowRendering();
	static WindowRendering *pInstance;

	//colliders
	Colliders *pColliders = Colliders::getInstance();

	//need walls permanent for collision detection
	SDL_Rect topWall;
	SDL_Rect bottomWall;
	SDL_Rect leftWall;

	//vars
	SDL_Window *gWindow; //main game window
	SDL_Renderer *gRenderer;
	SDL_Texture *gTextureBuffer; 
	int windowHeight;
	int windowWidth;

public:
	static WindowRendering *getInstance();

	void clearBuffer(); // clears buffer to black
	void renderPresent() { SDL_RenderPresent( gRenderer ); } // draw buffer to screen
	void close();

	int getWindowHeight() { return windowHeight; }
	int getWindowWidth() { return windowWidth; }

	void drawWalls(); // draws three walls

	void drawSolidRect(SDL_Rect *shape);
};

#endif
