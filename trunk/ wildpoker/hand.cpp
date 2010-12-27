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



int Hand::HandCmp(const Hand* otherHand,handTypes &winningHandType ) const//returns 0 for this==other, negative for this<other and positive for this>other
{
	const Card * sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND];
	const Card * others_sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND];
	winningHandType=none;
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
	return findWinner(sortedCards,others_sortedCards,winningHandType);	
}

int Hand::findWinner( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType ) const
{
	return checkForFours(sortedCards,others_sortedCards,winningHandType);//checks all the rules by given order

}
int Hand::checkForFours( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const//dosent work- EDIT THIS
{
	const Card * this_fours=NULL;
	const Card * Others_fours=NULL;
	winningHandType=fourOfValue;
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
		return checkForStraightFlushOfFive(sortedCards,others_sortedCards,winningHandType);
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

int Hand::checkForStraightFlushOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const
{
	winningHandType=FiveOfShape;
	bool this_Straight = true;
	bool other_Straight = true;
	int thisStartVal = sortedCards[0]->getVal();
	int thisStartSuit = sortedCards[0]->getSuitVal();
	int otherStartVal = others_sortedCards[0]->getVal();
	int otherStartSuit = others_sortedCards[0]->getSuitVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
	{
		if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisStartVal+i)
			this_Straight = false;
		if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherStartVal+i)
			other_Straight = false;
	}

	if (!this_Straight && !other_Straight)
	{
		return checkForStraightFlushOfFour(sortedCards,others_sortedCards,winningHandType);
	}
	else if (this_Straight && !other_Straight)
	{
		return THIS_IS_BIGGER;
	}
	else if (!this_Straight && other_Straight)
	{
		return THIS_IS_SMALLER;
	}
	else //at this point we have : (this_Straight && other_Straight)
	{
		if (thisStartVal>otherStartVal)
			return THIS_IS_BIGGER;
		else
			return THIS_IS_SMALLER;
		//Cant be of equal values, hence checking either if bigger or smaller.
	}
}

int Hand::checkForStraightFlushOfFour( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType )const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=FiveOfShape;
	int thisStartVal = sortedCards[0]->getVal();
	int thisStartSuit = sortedCards[0]->getSuitVal();
	int otherStartVal = others_sortedCards[0]->getVal();
	int otherStartSuit = others_sortedCards[0]->getSuitVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1; i++)
	{
		if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisStartVal+i)
			this_Straight = false;
		if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherStartVal+i)
			other_Straight = false;
	}
	if (!this_Straight) //Check again from 2
	{
		thisStartVal = sortedCards[1]->getVal();
		thisStartSuit = sortedCards[1]->getSuitVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisStartVal+i)
				this_Straight = false;
		}
	}
	if (!other_Straight) //Check again again from 2
	{
		otherStartVal = others_sortedCards[1]->getVal();
		otherStartSuit = others_sortedCards[1]->getSuitVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherStartVal+i)
				other_Straight = false;
		}
	}

	if (!this_Straight && !other_Straight)
	{
		return checkForPairs(sortedCards,others_sortedCards,winningHandType);
	}
	else if (this_Straight && !other_Straight)
	{
		return THIS_IS_BIGGER;
	}
	else if (!this_Straight && other_Straight)
	{
		return THIS_IS_SMALLER;
	}
	else //at this point we have : (this_Straight && other_Straight)
	{
		if (thisStartVal>otherStartVal)
			return THIS_IS_BIGGER;
		else if (thisStartVal<otherStartVal)
			return THIS_IS_SMALLER;
		else //Here (thisstartVal==otherStartVal)
			if (thisStartSuit>otherStartSuit)
				return THIS_IS_BIGGER;
			else //Here (thisStartSuit<otherStartSuit) since cant be equal
				return THIS_IS_SMALLER;
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
			return checkForStraightOfFive(sortedCards,others_sortedCards,rule);
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

///Careful from here!

int Hand::checkForStraightOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=fiveStrait;
	int thisStartVal = sortedCards[0]->getVal();
	int otherStartVal = others_sortedCards[0]->getVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
	{
		if (sortedCards[i]->getVal()!=thisStartVal+i)
			this_Straight = false;
		if (others_sortedCards[i]->getVal()!=otherStartVal+i)
			other_Straight = false;
	}

	if (!this_Straight && !other_Straight)
	{
		return checkForStraightOfFour(sortedCards,others_sortedCards,winningHandType);
	}
	else if (this_Straight && !other_Straight)
	{
		return THIS_IS_BIGGER;
	}
	else if (!this_Straight && other_Straight)
	{
		return THIS_IS_SMALLER;
	}
	else //at this point we have : (this_Straight && other_Straight)
	{
		if (thisStartVal>otherStartVal)
			return THIS_IS_BIGGER;
		else if (thisStartVal<otherStartVal)
			return THIS_IS_SMALLER;
		else //Here (thisStartVal == otherStartVal)
			if (sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1]>others_sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1]) //Both cards will be of equal value, but > for card checks suit as well.
				return THIS_IS_BIGGER;
			else
				return THIS_IS_SMALLER;
	}
}

int Hand::checkForStraightOfFour( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType )const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=fiveStrait;
	int thisStartVal = sortedCards[0]->getVal();
	int otherStartVal = others_sortedCards[0]->getVal();
	int thisStartOfStr8Index = 0;
	int otherStartOfStr8Index = 0;

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1; i++)
	{
		if (sortedCards[i]->getVal()!=thisStartVal+i)
			this_Straight = false;
		if (others_sortedCards[i]->getVal()!=otherStartVal+i)
			other_Straight = false;
	}
	if (!this_Straight) //Check again from 2
	{
		thisStartOfStr8Index++;
		thisStartVal = sortedCards[1]->getVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			if (sortedCards[i]->getVal()!=thisStartVal+i)
				this_Straight = false;
		}
	}
	if (!other_Straight) //Check again again from 2
	{
		thisStartOfStr8Index++;
		otherStartVal = others_sortedCards[1]->getVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			if (others_sortedCards[i]->getVal()!=otherStartVal+i)
				other_Straight = false;
		}
	}

	if (!this_Straight && !other_Straight)
	{
		return rule8(sortedCards,others_sortedCards,winningHandType);
	}
	else if (this_Straight && !other_Straight)
	{
		return THIS_IS_BIGGER;
	}
	else if (!this_Straight && other_Straight)
	{
		return THIS_IS_SMALLER;
	}
	else //at this point we have : (this_Straight && other_Straight)
	{
		if (thisStartVal>otherStartVal)
			return THIS_IS_BIGGER;
		else if (thisStartVal<otherStartVal)
			return THIS_IS_SMALLER;
		else //Here (thisStartVal == otherStartVal)
			if (sortedCards[thisStartOfStr8Index+3]>others_sortedCards[otherStartOfStr8Index+3]) //Both cards will be of equal value, but > for card checks suit as well.
				return THIS_IS_BIGGER;
			else
				return THIS_IS_SMALLER;
	}
}
int Hand::rule8( const Card * sortedCards[],const Card * others_sortedCards[],handTypes & rule ) const
{
	rule=HighestCard;
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
