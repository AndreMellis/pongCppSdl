#ifndef COLLIDERS_HEADER
#define COLLIDERS_HEADER

#include <vector>
#include <SDL.h>

enum ColliderList{
		PLAYERONE_PADDLE_COLIDER,
		PLAYERTWO_PADDLE_COLLIDER,
		DOT_COLLIDER,
		TOPWALL_COLLIDER,
		BOTTOMWALL_COLLIDER,
		LEFTWALL_COLLIDER
};

class Colliders
{ // just a place to store all colliders
private:
	static Colliders *pInstance;

	Colliders();
	~Colliders();

	std::vector<SDL_Rect*> allColliders;

public:
	static Colliders *getInstance();

	void addCollider(int whichCollider, SDL_Rect *pRectToAdd);

	SDL_Rect *getCollider(int colliderName); //returns a specific collider
};

#endif
