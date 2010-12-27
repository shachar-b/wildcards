#pragma once
#include "card.h"
#include "UI.h"
using namespace UIs;



class Hand
{


public:
	static const int NUM_OF_CARDS_IN_HAND =3;
	static const int NUM_OF_CARDS_IN_COMUNITY =2;
	Hand();
	~Hand();
	void setCard(const Card * card,int location);
	void setComunityCard(const Card * card,int location);
	const Card * getCard(int location);
	void printHand(int startX,int startY);
	bool operator<(const Hand *otherHand) const;
	bool operator>(const Hand * otherHand) const;
	bool operator==(const Hand * otherHand) const;
	
private:
	const Card * m_playerCards[NUM_OF_CARDS_IN_HAND];
	const Card * m_comunityCards[NUM_OF_CARDS_IN_COMUNITY];
	int HandCmp(const Hand* otherHand) const;
	int checkForFours(const Card * sortedCards[],const Card * others_sortedCards[])const;
	enum handTypes{fourOfValue=1,FiveOfShape,FourOfShape,twoPairs,onePair,fiveStrait,fourStrait,HighestCard};
	
};
