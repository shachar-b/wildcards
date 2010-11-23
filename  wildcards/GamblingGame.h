//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Tuesday 23/11/10
//Exercise:  Question:
//File name: GamblingGame.h
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
		unsigned int m_currPool;//the pool of the current round
		void givePoolToWinner();
		Gambler * getGamblerAt(unsigned int place);

	protected :
		const char * returnNameOfWinningPlayer();

	public:
		GamblingGame():Game(GAMBLING){};
		~GamblingGame();
	};

	//function declaration
#endif