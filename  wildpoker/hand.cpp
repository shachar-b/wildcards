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

bool Hand::operator<( const Hand& otherHand ) const
{
	return false;

}

bool Hand::operator>( const Hand& otherHand ) const
{
	return false;
}

bool Hand::operator==( const Hand& otherHand ) const
{
	return !(*this>otherHand) && !(*this<otherHand);
}

int cardcmp(const void * a,const void * b){return (const Card *)a==(const Card *)b;}
void Hand::populate()
{
	const Card * sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND];
	int i=0;
	int start=0;
	int end=0;
	for(int  i=0; i<NUM_OF_CARDS_IN_HAND; i++)
	{
		sortedCards[i]=m_playerCards[i];
	}
	for(int  i=0; i<NUM_OF_CARDS_IN_COMUNITY; i++)
	{
		sortedCards[i+NUM_OF_CARDS_IN_HAND]=m_comunityCards[i];
	}
	qsort(sortedCards,NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND,sizeof(Card *),&cardcmp);
	end=3;
	while(end<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND)
	{
		if (sortedCards[start]->getVal()==sortedCards[end]->getVal())
		{
			highest[0][0]++;
			
		}
		start++;
		end++;
	}


}