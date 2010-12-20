
#ifndef ___GAME___H____
#define ___GAME___H____
//includes
#include <iostream> 
using namespace std;	
#include "deck.h"
#include "Player.h"
#include "normalPlayer.h"
#include "gambler.h"
#include <deque>
#include <dos.h>

//classes
class UI;
class Game
{
protected:
	bool m_endGame;
	deque<Player *> m_players;
	static Deck m_gameDeck;
	int m_lastWinner;
	unsigned int m_numberOfplayers;
	unsigned int m_numberOfRounds;
	Player * getPlayerAt(unsigned int place);//////////////////////////////////////////////////////////////////////////
	void newRound();//////////////////////////////////////////////////////////////////////////
	virtual void initRound()=PURE;
	virtual void getDecisions()=PURE;
	virtual void closeRound();//////////////////////////////////////////////////////////////////////////
	virtual void decideWinners(int givenPoints=1)=PURE;
	void addPlayer(char* userName, int score=0,bool isHumen=false);//////////////////////////////////////////////////////////////////////////
	bool deletePlayer();//returns false IFF no more players//////////////////////////////////////////////////////////////////////////
	void drawCardsForAllUsers();
	void drawCardForUser(int userPlace);
	void returnAllCardsToDeck();//////////////////////////////////////////////////////////////////////////
	void returnCardForUser(int userPlace);//////////////////////////////////////////////////////////////////////////
	virtual void initGame()=PURE;
	void destroyGame();//////////////////////////////////////////////////////////////////////////
	int getUserPlace(int place){return (m_lastWinner+(place))%m_numberOfplayers;}//get player place in the current round//////////////////////////////////////////////////////////////////////////
	virtual const char * returnNameOfWinningPlayer()=PURE;
	void givePointsToPlayer(int numOfPoints,Player * p);//////////////////////////////////////////////////////////////////////////

public:
	Game();
	~Game();
	void play();
};
#endif
