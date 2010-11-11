#ifndef ___GAME___H____
#define ___GAME___H____
//includes
#include <iostream> 
using namespace std;
#include "Player.h"
#include "UI.h"
#include "deck.h"
#include <deque>
#include <dos.h>

//classes
class Game
{
private:
	Deck * gameDeck;
	int lastWinner;
	UI * ui;
	int numberOfplayers;
	int numberOfRounds;
	deque<Player *> players;
	Player * getPlayerAt(unsigned int place);
	void newRound();
	void drawCardsForAllUsers();
	void drawCardForUser(int userPlace);
	void returnAllCardsToDeck();
	void returnCardForUser(int userPlace);
	void decideWinners();
	void initGame();
	void destroyGame();
	int getUserPlace(int place){return (lastWinner+(place))%numberOfplayers;}//get player place in the current round
	const char * returnNameOfWinningPlayer();


public:
	Game();
	~Game();
	void play();
};

#endif