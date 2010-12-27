#include "hand.h"
#include <queue>

int cardcmp(const void * a,const void * b){return (const Card *)a==(const Card *)b;}

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

bool Hand::operator<( const Hand* otherHand ) const
{
	return HandCmp(otherHand)<0;

}

bool Hand::operator>( const Hand * otherHand ) const
{
	return HandCmp(otherHand)>0;
}
bool Hand::operator==( const Hand * otherHand ) const
{
	return HandCmp(otherHand)==0;
}


int Hand::HandCmp(const Hand* otherHand ) const//returns 0 for this==other, negative for this<other and positive for this>other
{
	const Card * sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND];
	const Card * others_sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND];
	int res;
	//sort cards in hands to new arrays
	for(int  i=0; i<NUM_OF_CARDS_IN_HAND; i++)
	{
		sortedCards[i]=m_playerCards[i];
		others_sortedCards[i]=otherHand->m_playerCards[i];
	}
	for(int  i=0; i<NUM_OF_CARDS_IN_COMUNITY; i++)
	{
		sortedCards[i+NUM_OF_CARDS_IN_HAND]=m_comunityCards[i];
		others_sortedCards[i+NUM_OF_CARDS_IN_HAND]=otherHand->m_comunityCards[i];
	}
	qsort(sortedCards,NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND,sizeof(Card *),&cardcmp);
	qsort(others_sortedCards,NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND,sizeof(Card *),&cardcmp);
	res=checkForFours(sortedCards,others_sortedCards);
	if (res!=0)
	{
		return res;
	}
	else
	{

	}
	//otherwise check for next otherwise....

	return res;
	
}
#define EQUAL 0
#define THIS_IS_BIGGER 1
#define THIS_IS_SMALLER -1

int Hand::checkForFours( const Card * sortedCards[],const Card * others_sortedCards[] )const//dosent work- EDIT THIS
{
	const Card * this_fours=NULL;
	const Card * Others_fours=NULL;
	for(int i=0; i<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-3; i++)
	{
		if (sortedCards[i]==sortedCards[i+3])
		{
			this_fours=(sortedCards[i+3]);
		}
		if (others_sortedCards[i]==sortedCards[i+3])
		{
			Others_fours=(others_sortedCards[i+3]);
		}
	}
	if ((this_fours==NULL) && (Others_fours==NULL))
	{
		return EQUAL;
	}
	else if ((this_fours==NULL) && !(Others_fours==NULL))
	{
		return THIS_IS_BIGGER;
	} 
	else if(!(this_fours==NULL) && (Others_fours==NULL))
	{
		return THIS_IS_SMALLER;
	}
	else
	{
		return this_fours->getVal()-Others_fours->getVal();//the max number of fours is 1 per player
	}
}



