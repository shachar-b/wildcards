#include "hand.h"

Hand::Hand()
{
	
	for (int i=0; i<NUM_OF_CARDS_IN_HAND; i++)
	{
		m_playerCards[i]=&UI::BLANK_CARD;
	}
	for (int i=0; i<NUM_OF_CARDS_IN_COMUNITY; i++)
	{
		m_comunityCards[i]=&UI::BLANK_CARD;
	}
}

Hand::~Hand()
{

}
void Hand::setCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		m_playerCards[location]=card;
	}
	//else
	//	throw "error at setCard";

}

void Hand::setComunityCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_COMUNITY)
	{
		m_comunityCards[location]=card;
	}
}

const Card * Hand::getCard( int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		return m_playerCards[location];
	}
	else
		return NULL;//Can throw exception here
}

void Hand::printHand( int startX,int startY )
{
	UIs::UI::gotoxy(startX,startY);
	cout<<"1     2     3";
	for(int i=0; i<NUM_OF_CARDS_IN_HAND; i++)
	{
		if (m_playerCards[i]!=NULL && !(m_playerCards[i]->isBlank()))
		{
			m_playerCards[i]->printcard(startX+(5*i)-1,startY+1);
		}
		else
		{
			UIs::UI::BLANK_CARD.printcard(startX+(5*i)-1,startY+1);
		}
		
	}

}


