#include "PlayerStatistics.h" 



PlayerStatistics::PlayerStatistics(int numOfJokers)
{
	m_NumOfJokers=numOfJokers;
	resetStatistics();
	
}
void PlayerStatistics::resetStatistics()
{
	for (int i=0; i<NUM_OF_GROUPS-1;i++)
	{
		m_CardGroups[i]=1;
	}
	m_CardGroups[NUM_OF_GROUPS-1]=m_NumOfJokers;
	m_NumOfCards=13*4+m_NumOfJokers;

}
PlayerStatistics::~PlayerStatistics(void)
{
}

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


bool PlayerStatistics::shouldSwitch( const Card * card )
{
	int NumOfGrater=getNumberOfGrater(card);
	int resHelper;
	resHelper=rand()%m_NumOfCards;
	return (resHelper<NumOfGrater)? true : false;
}

bool PlayerStatistics::shouldbet( const Card * card,int bet,int cash )
{
	if (bet>cash)
	{
		return false;
	} 
	else
	{//////////////////////////////////////////////////////////////////////////change!!!
		double betOrFold=0;
		betOrFold+=((double)getGroup(card))/NUM_OF_GROUPS;//card hight so its less likely to remove
		betOrFold+=(double)(getNumberOfGrater(card))/m_NumOfCards;//likelihood a switch would work
		betOrFold-=((double)bet)/(cash);// half the percentage of the bet from player money (less profitable) 
		if (betOrFold<0.5)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

}

//************************************
// Method:    howHigh - Selects a bet for the player, chosen by the strength of his hand, but also randomly.
//						A player will bet a random number (so it wont always be obvious he has a strong hand)
//						from 1 to a number determined by multiplying the max bet (20) by the complement to
//						the chance of getting a better card. Thus the stronger the hand the player has - he can bet higher.
// FullName:  PlayerStatistics::howHigh
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: const Card * card
// Parameter: int cash
//************************************
int PlayerStatistics::howHigh( const Card * card,int cash )
{
	double oddsToGetBetterCard = (double)getNumberOfGrater(card)/m_NumOfCards;
	double maxBetExact = 19*(1-oddsToGetBetterCard);
	int maxBetRounded = int(maxBetExact)+1;
	int calculatedBet = rand()%(maxBetRounded)+1;

	return min(calculatedBet,cash);
}


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
