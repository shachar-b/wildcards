#include "hand.h"
#include <queue>

//************************************
// Method:    cardcmp -compare two cards return 0 for equal 1 for a>b and -1 for b>a
// FullName:  cardcmp
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const void * a- a non null card pointer
// Parameter: const void * b- a non null card pointer
//************************************
int cardcmp(const void * a,const void * b)
{
	const Card first=*(const Card*)a;
	const Card second=*(const Card*)b;
	int result=EQUAL;
	if (first>second)
		result=THIS_IS_BIGGER;
	else if (first<second)
		result=THIS_IS_SMALLER;

	return result;
}

//************************************
// Method:    getStringOfWinningRule- return a printable string for the given winning rule
// FullName:  Hand::getStringOfWinningRule
// Access:    public 
// Returns:   std::string
// Qualifier:
// Parameter: handTypes winningRule- a hand type
//************************************
string Hand::getStringOfWinningRule( handTypes winningRule )
{
	switch (winningRule)
	{
	case FourOfAKind:
		return string("Four Of A Kind!");
	case FiveOfShape:
		return string("straight flush of 5 cards.");
	case FourOfShape:
		return string("straight flush of 4 cards.");
	case twoPairs:
		return string("two pairs.");
	case onePair:
		return string("one pair.");
	case fiveStraight:
		return string("straight of 5 cards.");
	case fourStraight:
		return string("straight of 4 cards.");
	case HighestCard:
		return string("highest sum of cards.");
	}
	return "ERROR!!!"; //Should not reach this line
}

//************************************
// Method:    Hand - make an empty hand
// FullName:  Hand::Hand
// Access:    public 
// Returns:   
// Qualifier:
//************************************
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

//************************************
// Method:    setCard- set the card in the given slot to be the given card
// FullName:  Hand::setCard
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Card * card - a card
// Parameter: int location- a number from 1 to 3
//************************************
void Hand::setCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		m_playerCards[location]=card;
	}//otherwise do nothing
}

//************************************
// Method:    setComunityCard -set one of the community cards to be the given card
// FullName:  Hand::setComunityCard
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Card * card -a card
// Parameter: int location- 1 or 2
//************************************
void Hand::setComunityCard( const Card * card,int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_COMUNITY)
	{
		m_comunityCards[location]=card;
	}
}

//************************************
// Method:    getCard- a getter for user cards
// FullName:  Hand::getCard
// Access:    public 
// Returns:   const Card *
// Qualifier:
// Parameter: int location- 1 to 3
//************************************
const Card * Hand::getCard( int location )
{
	location--;
	if (location>=0 && location<NUM_OF_CARDS_IN_HAND)
	{
		return m_playerCards[location];
	}
	else
		return NULL;
}

//************************************
// Method:    printHand - print all cards in hand and their numbering
// FullName:  Hand::printHand
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int startX - staring x point
// Parameter: int startY - starting y point
//************************************
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

//************************************
// Method:    HandCmp-returns 0 for this==other, negative for this<other and positive for this>other
// FullName:  Hand::HandCmp
// Access:    public 
// Returns:   int
// Qualifier: const
// Parameter: const Hand * otherHand- the hand to compare with
// Parameter: handTypes & winningHandType - to return the winning hand type
//************************************
int Hand::HandCmp(const Hand* otherHand,handTypes &winningHandType ) const
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
	qsort(sortedCards,NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND,sizeof(sortedCards[0]),&cardcmp);
	qsort(others_sortedCards,NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND,sizeof(others_sortedCards[0]),&cardcmp);
	return findWinner(sortedCards,others_sortedCards,winningHandType);	
}

//************************************
// Method:    findWinner- given  two hands sorted arrays and returns the winner and his hand type
// FullName:  Hand::findWinner
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::findWinner( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType ) const
{
	return checkForFours(sortedCards,others_sortedCards,winningHandType);//checks all the rules by given order

}

//************************************
// Method:    checkForFours -this function returns the winner- if no winner is found 
//				check for strait flush of five and returns its outcome
// FullName:  Hand::checkForFours
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::checkForFours( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const
{
	const Card * this_fours=NULL;
	const Card * Others_fours=NULL;
	winningHandType=FourOfAKind;
	for(int i=0; i<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-3; i++)
	{
		if (sortedCards[i]->getVal()==sortedCards[i+3]->getVal())
		{
			this_fours=(sortedCards[i+3]);
		}
		if (others_sortedCards[i]->getVal()==others_sortedCards[i+3]->getVal())
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

//************************************
// Method:    checkForStraightFlushOfFive -  -this function returns the winner- if no winner is found 
//				check for strait flush of four and returns its outcome
// FullName:  Hand::checkForStraightFlushOfFive
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::checkForStraightFlushOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const
{
	winningHandType=FiveOfShape;
	bool this_Straight = true;
	bool other_Straight = true;
	Card::eVal thisExpectedVal = sortedCards[0]->getVal();
	int thisStartSuit = sortedCards[0]->getSuitVal();
	Card::eVal otherExpectedVal = others_sortedCards[0]->getVal();
	int otherStartSuit = others_sortedCards[0]->getSuitVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
	{
		thisExpectedVal=Card::incriment(thisExpectedVal);
		otherExpectedVal=Card::incriment(otherExpectedVal);
		if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisExpectedVal)
			this_Straight = false;
		if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherExpectedVal)
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
		if (thisExpectedVal>otherExpectedVal)
			return THIS_IS_BIGGER;
		else
			return THIS_IS_SMALLER;
		//Cant be of equal values, hence checking either if bigger or smaller.
	}
}

//************************************
// Method:    checkForStraightFlushOfFour -  this function returns the winner- if no winner is found 
//				check for pairs and returns its outcome
// FullName:  Hand::checkForStraightFlushOfFour
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::checkForStraightFlushOfFour( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType )const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=FiveOfShape;
	Card::eVal thisExpectedVal = sortedCards[0]->getVal();
	int thisStartSuit = sortedCards[0]->getSuitVal();
	Card::eVal otherExpectedVal = others_sortedCards[0]->getVal();
	int otherStartSuit = others_sortedCards[0]->getSuitVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1; i++)
	{
		thisExpectedVal=Card::incriment(thisExpectedVal);
		otherExpectedVal=Card::incriment(otherExpectedVal);
		if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisExpectedVal)
			this_Straight = false;
		if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherExpectedVal)
			other_Straight = false;
	}
	if (!this_Straight) //Check again from 2
	{
		thisExpectedVal = sortedCards[1]->getVal();
		thisStartSuit = sortedCards[1]->getSuitVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			thisExpectedVal=Card::incriment(thisExpectedVal);
			if (sortedCards[i]->getSuitVal()!=thisStartSuit || sortedCards[i]->getVal()!=thisExpectedVal)
				this_Straight = false;
		}
	}
	if (!other_Straight) //Check again again from 2
	{
		otherExpectedVal = others_sortedCards[1]->getVal();
		otherStartSuit = others_sortedCards[1]->getSuitVal();
		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			otherExpectedVal=Card::incriment(otherExpectedVal);
			if (others_sortedCards[i]->getSuitVal()!=otherStartSuit || others_sortedCards[i]->getVal()!=otherExpectedVal)
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
		if (thisExpectedVal>otherExpectedVal)
			return THIS_IS_BIGGER;
		else if (thisExpectedVal<otherExpectedVal)
			return THIS_IS_SMALLER;
		else //Here (thisstartVal==otherStartVal)
			if (thisStartSuit>otherStartSuit)
				return THIS_IS_BIGGER;
			else //Here (thisStartSuit<otherStartSuit) since cant be equal
				return THIS_IS_SMALLER;
	}
}

//************************************
// Method:    checkForPairs - this function returns the winner- if no winner is found 
//				uses check strait of five and returns its outcome
// FullName:  Hand::checkForPairs
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & rule - for returning winning hand type
//************************************
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
			if (i+2<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-1)
			{
				if (sortedCards[i+1]->getVal()==sortedCards[i+2]->getVal())//3 of a kind  (cant be 4 otherwise it wont get here)
				{
					i++;//so that the highest card would be taken
				}

			}
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
			if (i+2<NUM_OF_CARDS_IN_HAND+NUM_OF_CARDS_IN_COMUNITY-1)
			{
				if (others_sortedCards[i+1]->getVal()==others_sortedCards[i+2]->getVal())//3 of a kind  (cant be 4 otherwise it wont get here)
				{
					i++;//so that the highest card would be taken
				}
			}
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

//************************************
// Method:    checkForStraightOfFive - this function returns the winner- if no winner is found 
//				uses check strait of four and returns its outcome
// FullName:  Hand::checkForStraightOfFive
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::checkForStraightOfFive( const Card * sortedCards[],const Card * others_sortedCards[] ,handTypes &winningHandType)const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=fiveStraight;
	Card::eVal thisExpectedVal = sortedCards[0]->getVal();
	Card::eVal otherExpectedVal = others_sortedCards[0]->getVal();

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
	{
		thisExpectedVal=Card::incriment(thisExpectedVal);
		otherExpectedVal=Card::incriment(otherExpectedVal);
		if (sortedCards[i]->getVal()!=thisExpectedVal)
			this_Straight = false;
		if (others_sortedCards[i]->getVal()!=otherExpectedVal)
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
		if (thisExpectedVal>otherExpectedVal)
			return THIS_IS_BIGGER;
		else if (thisExpectedVal<otherExpectedVal)
			return THIS_IS_SMALLER;
		else //Here (thisStartVal == otherStartVal)
			if (sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1]>others_sortedCards[NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1]) //Both cards will be of equal value, but > for card checks suit as well.
				return THIS_IS_BIGGER;
			else
				return THIS_IS_SMALLER;
	}
}

//************************************
// Method:    checkForStraightOfFour - this function returns the winner- if no winner is found 
//				uses and returns rule8 outcome
// FullName:  Hand::checkForStraightOfFour
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - for returning winning hand type
//************************************
int Hand::checkForStraightOfFour( const Card * sortedCards[],const Card * others_sortedCards[],handTypes &winningHandType )const
{
	bool this_Straight = true;
	bool other_Straight = true;
	winningHandType=fiveStraight;
	Card::eVal thisExpectedVal = sortedCards[0]->getVal();
	Card::eVal otherExpectedVal = others_sortedCards[0]->getVal();
	int thisStartOfStr8Index = 0;
	int otherStartOfStr8Index = 0;

	for (int i=1; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND-1; i++)
	{
		thisExpectedVal=Card::incriment(thisExpectedVal);
		otherExpectedVal=Card::incriment(otherExpectedVal);
		if (sortedCards[i]->getVal()!=thisExpectedVal)
			this_Straight = false;
		if (others_sortedCards[i]->getVal()!=otherExpectedVal)
			other_Straight = false;
	}
	if (!this_Straight) //Check again from 2
	{
		thisStartOfStr8Index++;
		thisExpectedVal = sortedCards[1]->getVal();

		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			thisExpectedVal=Card::incriment(thisExpectedVal);
			if (sortedCards[i]->getVal()!=thisExpectedVal)
				this_Straight = false;
		}
	}
	if (!other_Straight) //Check again again from 2
	{
		thisStartOfStr8Index++;
		otherExpectedVal = others_sortedCards[1]->getVal();
		otherExpectedVal=Card::incriment(otherExpectedVal);
		for (int i=2; i<NUM_OF_CARDS_IN_COMUNITY+NUM_OF_CARDS_IN_HAND; i++)
		{
			if (others_sortedCards[i]->getVal()!=otherExpectedVal)
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
		if (thisExpectedVal>otherExpectedVal)
			return THIS_IS_BIGGER;
		else if (thisExpectedVal<otherExpectedVal)
			return THIS_IS_SMALLER;
		else //Here (thisStartVal == otherStartVal)
			if (sortedCards[thisStartOfStr8Index+3]>others_sortedCards[otherStartOfStr8Index+3]) //Both cards will be of equal value, but > for card checks suit as well.
				return THIS_IS_BIGGER;
			else
				return THIS_IS_SMALLER;
	}
}

//************************************
// Method:    rule8 - this function returns the winner
// FullName:  Hand::checkForStraightOfFour
// Access:    private 
// Returns:   int
// Qualifier: const
// Parameter: const Card * sortedCards[] - an array representing a hand
// Parameter: const Card * others_sortedCards[]- an array representing a hand
// Parameter: handTypes & winningHandType - whould be set to rule8
//************************************
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