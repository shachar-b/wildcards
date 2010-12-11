#include "PlayerStatistics.h" 


//************************************
// Method:    PlayerStatistics - a  constructor for a user statistics object
// FullName:  PlayerStatistics::PlayerStatistics
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: int numOfJokers - the number of jokers in the current game
//************************************
PlayerStatistics::PlayerStatistics(int numOfJokers)
{
	m_NumOfJokers=numOfJokers;
	resetStatistics();
	
}

//************************************
// Method:    resetStatistics - restarts statistics (for a new deck)
// FullName:  PlayerStatistics::resetStatistics
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void PlayerStatistics::resetStatistics()
{
	for (int i=0; i<NUM_OF_GROUPS-1;i++)
	{
		m_CardGroups[i]=1;
	}
	m_CardGroups[NUM_OF_GROUPS-1]=m_NumOfJokers;
	m_NumOfCards=13*4+m_NumOfJokers;
}



//************************************
// Method:    updateStatistics
// FullName:  PlayerStatistics::updateStatistics
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Card * curr
//************************************
void PlayerStatistics::updateStatistics( const Card * curr/*=NULL*/ )
{
	m_NumOfCards--;
	if (m_NumOfCards==0)
	{
		resetStatistics();//deck is done
	}
	else
	{
		if (curr==NULL)
		{
			substructFromGroup(0);
		}
		else
		{
			substructFromGroup(getGroup(curr));
		}
	}
}

//************************************
// Method:    substructFromGroup - this function removes a card from statistics, if the card was already removed
//				the next card is removed(as part as our game strategy if a card is tossed we assume a low card was tossed) 
//				note that if the last group is empty and a card is being subtracted it would be ignored)
// FullName:  PlayerStatistics::substructFromGroup
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int groupNumber- the number of group to remove the card from
//************************************
void PlayerStatistics::substructFromGroup( int groupNumber )
{
	if (m_CardGroups[groupNumber]>0)
	{
		m_CardGroups[groupNumber]--;
	}
	else if (groupNumber<NUM_OF_GROUPS-1)
	{
		substructFromGroup(groupNumber+1);//could only happen when a card was tossed by user(in this or a previous round) thus this cant happen for last group
	}
}

//************************************
// Method:    getGroup-returns the group number of a card
// FullName:  PlayerStatistics::getGroup
// Access:    public 
// Returns:   int - the group number for the given card
// Qualifier:
// Parameter: const Card * card- a non null non blank card
//************************************
int PlayerStatistics::getGroup( const Card * card )
{
	if (card->getVal()==Card::VJoker)
	{
		return NUM_OF_GROUPS-1;
	}
	else
	{
		return 4*(card->getVal()-1)+(card->getSuitVal())-1 ;
	}
}

//************************************
// Method:    shouldSwitch - decide if a user should switch his card based on the estimated cards in the deck and the current card
// FullName:  PlayerStatistics::shouldSwitch
// Access:    public 
// Returns:   bool- returns true if a switch is likely to produce a better card false otherwise
// Qualifier:
// Parameter: const Card * card - a non null non blank card
//************************************
bool PlayerStatistics::shouldSwitch( const Card * card )
{
	int NumOfGrater=getNumberOfGrater(card);
	int resHelper;
	resHelper=rand()%m_NumOfCards;
	return (resHelper<NumOfGrater)? true : false;
}

//************************************
// Method:    shouldbet - Tells a player to either call a bet, to fold. if player dosent have enough money he folds.
// FullName:  PlayerStatistics::shouldbet
// Access:    public 
// Returns:   bool - true if likely to win false otherwise
// Qualifier:
// Parameter: const Card * card - a non null non blank card
// Parameter: int bet - a number from 1 to 20
// Parameter: int cash- a positive number or 0
//************************************
bool PlayerStatistics::shouldbet( const Card * card,int bet,int cash )
{
	if (bet>cash)
	{
		return false;
	} 
	else
	{
		double chanceToWinWithCurrCard=((double)getGroup(card))/NUM_OF_GROUPS;
		double chanceToGetBetterCard=((double)getNumberOfGrater(card))/m_NumOfCards;

		//Definition: Pot odds - pot odds are the ratio of the current size of the pot to the cost of a contemplated call.
		//To calculate the pot odds of a bet we divide the bet by the current pot + the bet to be called.
		//i.e. - if there are already 20 coins in the pot and the player has to complete 10 to enter the bet,
		//we say that his pot odds are 10/(20+10) or approx. 33 percent.
		//In our game, pot odds range from 0.5 to 0.25 depending on how many players are in the game and have
		//made their move. We want our computer players to be not too wild and not too cautious - so they will always play
		//by pot odds of 1/3.

		if (shouldSwitch(card)) //Try to predict if the player will change the card
		{
			if (chanceToGetBetterCard>=POT_ODDS)
				return true;
			else
				return false;
		}
		else //Player will likely stay with current card
		{
			if (chanceToWinWithCurrCard>=POT_ODDS)
				return true;
			else
				return false;
		}
	}
}

//************************************
// Method:    howHigh - Selects a bet for the player, chosen by the strength of his hand, but also randomly.
//						A player will bet a random number (so it wont always be obvious he has a strong hand)
//						from 1 to a number determined by multiplying the bet upper limit by the complement to
//						the chance of either getting a better card, or winning with the current one.
//						Thus the stronger the hand the player has - he can bet higher.
// FullName:  PlayerStatistics::howHigh
// Access:    public 
// Returns:   int - a number from 1 to 20
// Qualifier:
// Parameter: const Card * card - a non null non blank card
// Parameter: int cash - a positive number or 0
//************************************
int PlayerStatistics::howHigh( const Card * card,int cash )
{
	double chanceToWinWithCurrCard=((double)getGroup(card))/NUM_OF_GROUPS;
	double chanceToGetBetterCard=((double)getNumberOfGrater(card))/m_NumOfCards;
	double maxBetExact;

	if (shouldSwitch(card))//Try to predict if the player will change the card
	{
		maxBetExact=19*(chanceToGetBetterCard);//(0-19)
	}
	else
	{
		maxBetExact=19*(chanceToWinWithCurrCard);//(0-19)
	}
	int maxBetRounded = int(maxBetExact)+1;//(1-20)
	int calculatedBet = rand()%(maxBetRounded)+1;

	return min(calculatedBet,cash);
}

//************************************
// Method:    getNumberOfGrater 
// FullName:  PlayerStatistics::getNumberOfGrater
// Access:    public 
// Returns:   int - the number of cards grater then current deck which are estimated to be in the deck 
// Qualifier:
// Parameter: const Card * card -  a non null non blank card
//************************************
int PlayerStatistics::getNumberOfGrater( const Card * card )
{
	int currGroup=getGroup(card);
	int NumOfGrater=0;
	for (int i=currGroup+1; i<NUM_OF_GROUPS; i++)
	{
		NumOfGrater+=m_CardGroups[i];
	}
	return NumOfGrater;
}