#include "Colliders.h"

Colliders *Colliders::pInstance = nullptr;

Colliders *Colliders::getInstance()
{
	if(!pInstance)
	{
		pInstance = new Colliders();
	}
	return pInstance;
}

Colliders::Colliders()
{
	allColliders.resize(6); //2 paddles, 1 ball for now, 3 walls
}

void Colliders::addCollider(int whichCollider, SDL_Rect *pRectToAdd)
{
	allColliders[whichCollider] = pRectToAdd;
}

SDL_Rect *Colliders::getCollider(int colliderName)
{
	return allColliders[colliderName];
}
