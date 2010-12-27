#ifndef ___GAME___H____
#define ___GAME___H____
//includes
#include <iostream> 
using namespace std;	
#include "deck.h"
#include "Player.h"
#include "hand.h"
#include <deque>
#include <dos.h>

//classes
class UI;
class Game
{
private:
	bool m_endGame;
	deque<Player *> m_players;
	static Deck m_gameDeck;
	int m_lastWinner;
	unsigned int m_numberOfplayers;
	unsigned int m_numberOfRounds;
	const Card * m_comunityCards[Hand::NUM_OF_CARDS_IN_COMUNITY];
	void Game::drawComunityCards();
	Player * getPlayerAt(unsigned int place);
	void newRound();
	void initRound();
	void getDecisions();
	void closeRound();
	void decideWinners(int givenPoints=1);
	void addPlayer(char* userName,bool isHumen=false, int score=0);
	bool deletePlayer();//returns false IFF no more players
	void drawCardsForAllUsers();
	void drawCardForUser(int userPlace, int cardNumber);
	void returnAllCardsToDeck();
	void returnCardForUser(int userPlace, int cardNumber);
	void initGame();
	void destroyGame();
	int getUserPlace(int place){return (m_lastWinner+(place))%m_numberOfplayers;}//get player place in the current round
	const char * returnNameOfWinningPlayer();
	void givePointsToPlayer(int numOfPoints,Player * p);

public:
	Game(){UIs::UI::UI(); initGame();}
	~Game(){destroyGame();}
	void play();
};
#endif
