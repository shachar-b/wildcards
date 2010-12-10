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
	#include "UI.h"
	using namespace UIs;

	#include <stdlib.h>
	#include <string>
	//defines
	#define NUM_OF_RANKS 4
    #define NUM_OF_SUITS 13
	#define NUM_OF_GROUPS 53

	//consts
	const double POT_ODDS=1/3;
	//classes
	class PlayerStatistics
	{
	private:
		int m_NumOfCards;
		int m_NumOfJokers;
		int m_CardGroups[NUM_OF_GROUPS];
		void substructFromGroup(int groupNumber);
		void resetStatistics();
		
	public:
		PlayerStatistics(int numOfJokers);
		~PlayerStatistics();
		void updateStatistics(const Card *curr =NULL);
		int getCardType(const Card * card) const;
		int getGroup(const Card * card);
		bool shouldSwitch(const Card * card);
		bool shouldbet( const Card * card,int bet,int cash );
		int howHigh(const Card * card,int cash);
		int getNumberOfGrater(const Card * card);


	};
	//function declaration
#endif