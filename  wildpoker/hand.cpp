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
		if (sortedCards[i]->getVal()==sortedCards[i+3]->getVal())
		{
			this_fours=(sortedCards[i+3]);
		}
		if (others_sortedCards[i]->getVal()==sortedCards[i+3]->getVal())
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

int Hand::checkForPairs( const Card * sortedCards[],const Card * others_sortedCards[],handTypes & rule ) const
{
	int This_numberOfPairs=0;
	int This_sumOfPairs=0;
	const Card * this_higest=NULL;
	int Other_numberOfPairs=0;
	int Other_sumOfPairs=0;
	const Card * Other_higest=NULL;
	for(int i=0; i<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-1; i++) 
	{
		if (sortedCards[i]->getVal()==sortedCards[i+1]->getVal())
		{
			This_numberOfPairs++;
			This_sumOfPairs+=sortedCards[i]->getVal()*2;
			if (this_higest==NULL || sortedCards[i+1]>this_higest )
			{
				this_higest=sortedCards[i+1];
			}
			i++;// jump 2 to avoid 3 of a kind to be mistaken for 2 pairs
		}
	}
	for(int i=0; i<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-1; i++) 
	{
		if (others_sortedCards[i]->getVal()==others_sortedCards[i+1]->getVal())
		{
			Other_numberOfPairs++;
			Other_sumOfPairs+=others_sortedCards[i]->getVal()*2;
			if (Other_higest==NULL || others_sortedCards[i+1]>Other_higest )
			{
				Other_higest=others_sortedCards[i+1];
			}
			i++;// jump 2 to avoid 3 of a kind to be mistaken for 2 pairs
		}
	}
	if (This_numberOfPairs==Other_numberOfPairs)
	{
		if (This_numberOfPairs==0)
		{
			rule=none;
			return EQUAL;
		}
		else //two or one
		{
			rule=(This_numberOfPairs==2)? twoPairs:onePair;
			if (This_sumOfPairs>Other_sumOfPairs)
			{
				return THIS_IS_BIGGER;
			}
			else if (This_sumOfPairs<Other_sumOfPairs)
			{
				return  THIS_IS_SMALLER;
			}
			else
			{
				return this_higest>Other_higest? THIS_IS_BIGGER:THIS_IS_SMALLER;
			}
		}
	} 
	else
	{
		rule=(max(This_numberOfPairs,Other_numberOfPairs)==2)?twoPairs:onePair;
		if (This_numberOfPairs>Other_numberOfPairs)
		{
			return THIS_IS_BIGGER;
		}
		else
		{
			return THIS_IS_SMALLER;
		}
	}
}

int Hand::rule8( const Card * sortedCards[],const Card * others_sortedCards[],handTypes & rule ) const
{
	int This_sumOfCards=0;
	const Card * this_higest=NULL;
	int Other_sumOfCards=0;
	const Card * Other_higest=NULL;
	
	for(int i=0; i<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY; i++) 
	{
		This_sumOfCards+=sortedCards[i]->getVal();
		Other_sumOfCards+=others_sortedCards[i]->getVal();
	}
	this_higest=sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1];
	Other_higest=others_sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1];
	if (This_sumOfCards>Other_sumOfCards)
	{
		return THIS_IS_BIGGER;
	}
	else if (This_sumOfCards<Other_sumOfCards)
	{
		return  THIS_IS_SMALLER;
	}
	else
	{
		return this_higest>Other_higest? THIS_IS_BIGGER:THIS_IS_SMALLER;
	}
}

