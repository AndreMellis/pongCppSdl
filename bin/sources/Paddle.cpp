#include "Paddle.h"

Paddle::Paddle()
{
	mPosX = 0;
	mPosY = 0;

	mVelX = 0;
	mVelY = 0;

	paddleShape.x = pWindowRenderer->getWindowWidth() - PADDLE_WIDTH;
	paddleShape.y = mPosY;
	paddleShape.w = PADDLE_WIDTH;
	paddleShape.h = PADDLE_HEIGHT;

	pColliders->addCollider(PLAYERTWO_PADDLE_COLLIDER, &paddleShape);
}

void Paddle::handleEvent(SDL_Event &event)
{
	//if a key was pressed
	if ( event.type==SDL_KEYDOWN && event.key.repeat == 0 )
	{ // we only want to know the first time a key was pressed. ignore retriggers by holding down
		//adjust the velocity
		switch ( event.key.keysym.sym )
		{
			case SDLK_w:
				mVelY -= PADDLE_VEL; // -y to move up
				break;
			case SDLK_s:
				mVelY += PADDLE_VEL; // +y to move down
				break;
		}
	} else if (event.type == SDL_KEYUP && event.key.repeat == 0 )
	{ // we let go of the key
		switch ( event.key.keysym.sym )
		{
			case SDLK_w:
				mVelY += PADDLE_VEL; //stop moving the paddle
				break;
			case SDLK_s:
				mVelY -= PADDLE_VEL; //stop moving the paddle
				break;
		}
	}
}

void Paddle::move()
{
	mPosY += mVelY; //move the paddle up or down
	
	//if the dot went to far up/down
	if ( (mPosY < 0) || (mPosY + PADDLE_HEIGHT > pWindowRenderer->getWindowHeight()) )
	{ //we went off screen
		mPosY -= mVelY; //move backwards
	}
}

void Paddle::render()
{
	paddleShape.x = pWindowRenderer->getWindowWidth() - PADDLE_WIDTH;
	paddleShape.y = mPosY;
	paddleShape.w = PADDLE_WIDTH;
	paddleShape.h = PADDLE_HEIGHT;

	pWindowRenderer->drawSolidRect(&paddleShape);
}

SDL_Rect &Paddle::getCollider()
{
	return paddleShape;
}
