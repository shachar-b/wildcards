//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Monday 06/12/10
//Exercise:  Question:
//File name: PlayerStatistics.h
#ifndef ___PLAYERSTATISTICS___H____
	#define ___PLAYERSTATISTICS___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "card.h"
	#include "deck.h"
	#include <stdlib.h>
	#include <string>
	//defines
	#define NUM_OF_RANKS 4
    #define NUM_OF_SUITS 13
	#define LOW 0
	#define MID 1
	#define HIGH 2
	#define PERM 3
	//consts
	//classes
	class PlayerStatistics
	{
	private:
		const &Deck CurrentDeck;
		int numOfTakes;
		int CardGroups[4];
		
	public:
		PlayerStatistics();
		~PlayerStatistics();
		void updateStatistics(const Card *curr =NULL);
		double getProbityOFHigherCard(const Card *);



	};
	//function declaration
#endif