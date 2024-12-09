#ifndef PADDLE_HEADER
#define PADDLE_HEADER

#include <SDL.h>
#include "WindowRendering.h"
#include "Colliders.h"

class Paddle
{
private:
	WindowRendering *pWindowRenderer = WindowRendering::getInstance();
	Colliders *pColliders = Colliders::getInstance();
	SDL_Rect paddleShape;

	//The X and Y offsets of the paddle
	int mPosX;
	int mPosY;

	//the velocity of the paddle
	int mVelX;
	int mVelY;

	//the dimension of the paddle
	static const int PADDLE_WIDTH = 10;
	static const int PADDLE_HEIGHT = 100;

	//Maximum axis velocity of the paddle
	static const int PADDLE_VEL = 1;
public:

	Paddle(); //constructor

	void handleEvent(SDL_Event &event); // takes key presses and adjusts the paddle's vel

	void move(); //moves the paddle

	void render(); //renders the paddle onscreen

	SDL_Rect &getCollider();
};

#endif
