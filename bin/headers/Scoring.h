#ifndef SCORING_HEADER
#define SCORING_HEADER

class Scoring
{
private:
	static Scoring *pInstance;

	int playerOneScore;
	int playerTwoScore;
	int round;

	Scoring();
	~Scoring();
	
	void printScore();
public:
	static Scoring *getInstance();
	void playerOneWins(); //increase player One score
	void playerTwoWins(); // increase player Two score
};

#endif
