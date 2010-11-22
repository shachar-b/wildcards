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
	#include <dos.h>	//defines
	//consts
	//classes

	class UI;
	class Game
	{
	protected:
		deque<Player *> m_players;
		GameTypes m_gameType;
		Deck * m_gameDeck;
		int m_lastWinner;
		UI * m_ui;
		unsigned int m_numberOfplayers;
		unsigned int m_numberOfRounds;
		virtual Player * getPlayerAt(unsigned int place)=0;
		virtual void newRound();
		void initRound();
		void getDecisoins();
		void closeRound();
		virtual void decideWinners()=0;
		void addPlayer(char* userName, bool isComputer=true, int balance=0);
		bool deletePlayer();//returns false IFF no more players
		void drawCardsForAllUsers();
		void drawCardForUser(int userPlace);
		void returnAllCardsToDeck();
		void returnCardForUser(int userPlace);
		void initGame();
		void destroyGame();
		int getUserPlace(int place){return (m_lastWinner+(place))%m_numberOfplayers;}//get player place in the current round
		virtual const char * returnNameOfWinningPlayer()=0;


	public:
		GameTypes getGameType() const {return m_gameType;}
		Game(GameTypes type=NORMAL);
		~Game();
		void play();
	};
	//function declaration
#endif