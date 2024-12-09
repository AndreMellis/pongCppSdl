#include "Dot.h"
#include <cstdlib>
#include <cstdio>
#include <vector>

Dot::Dot()
{
	mPosX = pWindowRenderer->getWindowWidth() / 2; //start in the middle
	mPosY = pWindowRenderer->getWindowHeight() / 2; //start in the middle
	mVelY = 0;

	if( (1 + (rand()%10)) % 2 ) //generate a random number 1-10. mod by 2 and see if it's a 0 or 1
	{ // we will start going left
		mVelX = 0 - DOT_VEL;
	} else 
	{
		mVelX = DOT_VEL;
	}

	dotShape.x = mPosX;
	dotShape.y = mPosY;
	dotShape.w = DOT_SIZE;
	dotShape.h = DOT_SIZE;

	pColliders->addCollider(DOT_COLLIDER, &dotShape); //add the location of the actual dot's shape to the collider list so that it's constantly refrencing the actual dot
}

void Dot::resetDot()
{
	mPosX = pWindowRenderer->getWindowWidth() / 2; //start in the middle
	mPosY = pWindowRenderer->getWindowHeight() / 2; //start in the middle
	mVelY = 0;
	
	if( (1 + (rand()%10)) % 2 ) //50:50 0 or 1 generation
	{ // we will start going left
		mVelX = 0 - DOT_VEL;
	} else 
	{
		mVelX = DOT_VEL;
	}
}

bool Dot::collidedWithRightPaddle()
{
	SDL_Rect *pRightPaddle = pColliders->getCollider(PLAYERTWO_PADDLE_COLLIDER);
	if (
		((mPosX + DOT_SIZE ) > pRightPaddle->x) //x axis align
		&&
		( (mPosY + DOT_SIZE) >= pRightPaddle->y) // dot is lower than paddle y
		&&
		( mPosY <= (pRightPaddle->y + pRightPaddle->h) ) // dot is higher than paddle y+h
	)
	{
		return 1;
	} else
	{
		return 0;
	}
}

bool Dot::collidedSide()
{
	SDL_Rect *pLeftWall = pColliders->getCollider(LEFTWALL_COLLIDER);

	if (mPosX < (pLeftWall->x + pLeftWall->w))
	{
		//we collided with the left wall
		return 1;
	} else 
	{
		return 0;
	}

}

bool Dot::collidedTop()
{
	if (mPosY < 0 || mPosY+DOT_SIZE > pWindowRenderer->getWindowHeight())
	{
		return 1;
	} else
	{
		return 0;
	}
}

void Dot::move()
{
	mPosX += mVelX;
	mPosY += mVelY;

	if (mPosX+DOT_SIZE > pWindowRenderer->getWindowWidth())
	{ // player Two on right side needs a point
		pScoreBoard->playerOneWins();
		resetDot();
		return; //break out early
	} else if (mPosX<0)
	{
		pScoreBoard->playerTwoWins();
		resetDot();
		return; //break out early
	}

	if (collidedWithRightPaddle())
	{ // I will check if the middle of the dot is in the upper portion of the paddle
		int middleOfDot = (dotShape.h + dotShape.y) / 2; //pixel that the middle of the dot is on
		int bottomOfDot = dotShape.h + dotShape.y;

		SDL_Rect *pRightPaddle = pColliders->getCollider(PLAYERTWO_PADDLE_COLLIDER);
		int topOfPaddle = (int)( pRightPaddle->y + ( pRightPaddle->h / 2 ) );
		int bottomOfPaddle = (int)( pRightPaddle->y + ( pRightPaddle->h * 0.66) );

		if(bottomOfDot > pRightPaddle->y && bottomOfDot < topOfPaddle)
		{ // bounce the dot up
			mVelY = DOT_VEL * -1;
			mVelX = DOT_VEL * -1;
		} else if ( bottomOfDot > bottomOfPaddle && bottomOfDot < ( pRightPaddle->y + pRightPaddle->h ) )
		{ //bounce down
			mVelY = DOT_VEL;
			mVelX = DOT_VEL * -1;
		} else
		{ // go straight
			mVelY = 0;
			mVelX = DOT_VEL * -1;
		}
	} else if (collidedTop())
	{
		mPosY -= mVelY; //back up
		mVelY = mVelY * -1; //flip the direction it's going
		mPosY += mVelY; // keep moving
	} else if (collidedSide())
	{
		mPosX -= mVelX; //back up
		mVelX = mVelX * -1; //flip the direction it's going
		mPosX += mVelX; // keep moving
	}
}

void Dot::render()
{
	dotShape.x = mPosX;
	dotShape.y = mPosY;
	dotShape.w = DOT_SIZE;
	dotShape.h = DOT_SIZE;

	pWindowRenderer->drawSolidRect(&dotShape);
}

SDL_Rect &Dot::getCollider()
{
	return dotShape;
}
