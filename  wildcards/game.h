#ifndef ___GAME___H____
#define ___GAME___H____
//includes
#include <iostream> 
using namespace std;
#include "Player.h"
#include "UI.h"
#include "deck.h"
#include "gambler.h"
#include <deque>
#include <dos.h>

//classes
class Game
{
private:
	Deck * m_gameDeck;
	int m_lastWinner;
	UI * m_ui;
	int m_numberOfplayers;
	int m_numberOfRounds;
	deque<Player *> m_players;
	Player * getPlayerAt(unsigned int place);
	void newRound();
	void drawCardsForAllUsers();
	void drawCardForUser(int userPlace);
	void returnAllCardsToDeck();
	void returnCardForUser(int userPlace);
	void decideWinners();
	void initGame();
	void destroyGame();
	int getUserPlace(int place){return (m_lastWinner+(place))%m_numberOfplayers;}//get player place in the current round
	const char * returnNameOfWinningPlayer();


public:
	Game();
	~Game();
	void play();
};

#endif