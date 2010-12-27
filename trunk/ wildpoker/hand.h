#pragma once
#include "card.h"
#include "UI.h"
using namespace UIs;

#define EQUAL 0
#define THIS_IS_BIGGER 1
#define THIS_IS_SMALLER -1

//Globals
int cardcmp(const void * a,const void * b);

class Hand
{
public:
	enum handTypes{none,FourOfAKind,FiveOfShape,FourOfShape,twoPairs,onePair,fiveStraight,fourStraight,HighestCard};
	static const int NUM_OF_CARDS_IN_HAND =3;
	static const int NUM_OF_CARDS_IN_COMUNITY =2;
	Hand();
	~Hand();
	void setCard(const Card * card,int location);
	void setComunityCard(const Card * card,int location);
	const Card * getCard(int location);
	void printHand(int startX,int startY);
	int HandCmp(const Hand* otherHand,handTypes &winningHandType) const;
	static string getStringOfWinningRule(handTypes winningRule);
	
private:
	const Card * m_playerCards[NUM_OF_CARDS_IN_HAND];
	const Card * m_comunityCards[NUM_OF_CARDS_IN_COMUNITY];	
	int findWinner(const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType)const;
	int checkForFours(const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType)const;
	int checkForPairs(const Card * sortedCards[],const Card * others_sortedCards[],handTypes & rule)const;
	int rule8(const Card * sortedCards[],const Card * others_sortedCards[],handTypes & rule)const;
	int checkForStraightFlushOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const;
	int checkForStraightFlushOfFour( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const;
	int checkForStraightOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const;
	int checkForStraightOfFour( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType )const;	
};