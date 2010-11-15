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
	bool m_isHuman;
	char * m_name;
	int m_score;
	Card * m_card;
	bool m_decision;


public:
	static const bool KEEP=true;
	static const bool THROW=false;  
	Player(const char * playerName,bool iscomputer=true);
	~Player(){if (m_name)	{delete m_name;}}
	bool makeDecision(UI * ui);
	virtual void printPlayerDetails(int x,int y,bool showCard=true) const;
	//setter and getters
	int getScore(){return m_score;}
	void addToScore(int num){m_score+=num;}
	Card * getCard(){return m_card;}
	void setCard(Card * newCard){m_card=newCard;}
	const char * getName(){return m_name;}
	bool isHumanPlayer(){return m_isHuman;}
	bool getDecision(){return m_decision;}
};

#endif