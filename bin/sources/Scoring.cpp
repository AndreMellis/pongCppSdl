#include "Scoring.h"
#include <cstdio>

Scoring *Scoring::pInstance = nullptr;

Scoring::Scoring()
{
	round = 0;
	playerOneScore = 0;
	playerTwoScore = 0;
}

Scoring *Scoring::getInstance()
{
	if(!pInstance)
	{
		pInstance = new Scoring();
	}

	return pInstance;
}

void Scoring::printScore()
{
	printf("Round %d:\nPlayer One: %d\nPlayer Two: %d\n", round, playerOneScore, playerTwoScore);
}

void Scoring::playerOneWins()
{
	playerOneScore++;
	round++;
	printScore();
}

void Scoring::playerTwoWins()
{
	playerTwoScore++;
	round++;
	printScore();
}
