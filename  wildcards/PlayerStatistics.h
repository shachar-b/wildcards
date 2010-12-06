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

	//consts
	//classes
	class PlayerStatistics
	{
	private:
		int NumOfCards;
		int NumOfJokers;
		int CardGroups[7];
		void substructFromGroup(int groupNumber);
		void resetStatistics();
		
	public:
		PlayerStatistics(int numOfJokers);
		~PlayerStatistics();
		void updateStatistics(const Card *curr =NULL);
		double getProbabilityOFHigherCard(const Card * card);
		int getCardType(const Card * card) const;
		int getGroup(const Card * card);



	};
	//function declaration
#endif