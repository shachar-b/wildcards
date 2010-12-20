#pragma once
const int NUM_OF_CARDS_IN_HAND =3;
const int NUM_OF_CARDS_IN_COMUNITY =2;

class Hand
{
private:
	const Card * playerCards[NUM_OF_CARDS_IN_HAND];
	const Card * comunityCards[NUM_OF_CARDS_IN_COMUNITY];

public:
	Hand();
	void setCard(const Card * card,int location);
	void setComunityCard(const Card * card,int location);
	const Card * getCard(int location);


};
