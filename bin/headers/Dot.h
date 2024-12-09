#ifndef DOT_HEADER
#define DOT_HEADER

#include "WindowRendering.h"
#include "Scoring.h"
#include "Colliders.h"


class Dot
{
private:
	WindowRendering *pWindowRenderer = WindowRendering::getInstance();
	Scoring *pScoreBoard = Scoring::getInstance();
	Colliders *pColliders = Colliders::getInstance();

	SDL_Rect dotShape; //the shape of the dot, but will also serve as the collider

	int mPosX; // x offset from middle of screen
	int mPosY; // y offset from middle of screen

	int mVelX; // current x Velocity
	int mVelY; // current y velocity

	static const int DOT_SIZE = 10;
	static const int DOT_VEL = 1;

	bool collidedSide(); //return true if we collided with a side wall
	bool collidedTop(); //return true if we collided with a side wall
	bool collidedWithRightPaddle(); //returns true if x and y of dot collide with x/y of paddle

	void resetDot(); //drop dot in middle of screen and send it in a random dir
public:
	Dot();

	void move();
	void render();

	SDL_Rect &getCollider();
};

#endif
