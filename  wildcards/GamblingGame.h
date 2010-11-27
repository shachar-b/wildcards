#ifndef ___GAMBLINGGAME___H____
	#define ___GAMBLINGGAME___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "game.h"
	//defines
	
	//consts
	//classes
	class GamblingGame :public Game
	{
	private:
		unsigned int m_initialDucats;
		unsigned int m_currPool;//the pool of the current round
		void givePoolToWinner();
		Gambler * getGamblerAt(unsigned int place);
		void newRound();
		void bettingPhase();
		void initGame();
		

	protected :
		void initRound();
		void closeRound();
		const char * returnNameOfWinningPlayer();
		void setPlayersInitialBalance();

	public:
		GamblingGame();//initialize upper level only
		
	};
#endif