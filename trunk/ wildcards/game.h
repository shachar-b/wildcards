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
		deque<Player *> m_players;
		GameTypes m_gameType;
		Deck * m_gameDeck;
		int m_lastWinner;
		bool m_endGame;
		unsigned int m_numberOfplayers;
		unsigned int m_numberOfRounds;
		Player * getPlayerAt(unsigned int place);
		virtual void newRound();
		virtual void initRound();
		void getDecisions();
		virtual void closeRound();
		void decideWinners(int givenPoints=1);
		void addPlayer(char* userName, bool isComputer=true, int balance=0);
		bool deletePlayer();//returns false IFF no more players
		void drawCardsForAllUsers();
		void drawCardForUser(int userPlace);
		void returnAllCardsToDeck();
		void returnCardForUser(int userPlace);
		virtual void initGame();
		void destroyGame();
		int getUserPlace(int place){return (m_lastWinner+(place))%m_numberOfplayers;}//get player place in the current round
		virtual const char * returnNameOfWinningPlayer()=0;
		int countPlayerJokers() const;
		void givePointsToPlayer(int numOfPoints,Player * p);

	public:
		GameTypes getGameType() const {return m_gameType;}
		Game(GameTypes type=NORMAL);
		~Game();
		void play();
	};
#endif