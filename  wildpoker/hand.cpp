#include "hand.h"


void Hand::setCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		playerCards[location]=card;
	}
	//else
	//	throw "error at setCard";

}

void Hand::setComunityCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_COMUNITY)
	{
		comunityCards[location]=card;
	}
}

const Card * Hand::getCard( int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		return playerCards[location];
	}
	else
		return NULL;//Can throw exception here
}