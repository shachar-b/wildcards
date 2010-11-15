#ifndef ___PLAYER___H____
#define ___PLAYER___H____
//includes
#include <iostream> 
using namespace std;
#include <stdlib.h>
#include <time.h>
#include "UI.h"

//classes
class Player
{
private:
	bool isHuman;
	char * name;
	int score;
	Card * card;
	bool decision;


public:
	static const bool KEEP=true;
	static const bool THROW=false;  
	Player(const char * playerName,bool iscomputer=true);
	~Player(){if (name)	{delete name;}}
	bool makeDecision(UI * ui);
	void printPlayerDetails(int x,int y,bool showCard=true) const;
	//setter and getters
	int getScore(){return score;}
	void addToScore(int num){score+=num;}
	Card * getCard(){return card;}
	void setCard(Card * newCard){card=newCard;}
	const char * getName(){return name;}
	bool isHumanPlayer(){return isHuman;}
	bool getDecision(){return decision;}
};

#endif