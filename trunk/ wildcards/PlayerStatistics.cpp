#include "PlayerStatistics.h"



PlayerStatistics::PlayerStatistics(int numOfJokers)
{
	m_NumOfJokers=numOfJokers;
	resetStatistics();
	
}
void PlayerStatistics::resetStatistics()
{
	for (int i=0; i<6;i++)
	{
		m_CardGroups[i]=8;
	}
	m_CardGroups[6]=4+m_NumOfJokers;
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
	else if (groupNumber<6)
	{
		substructFromGroup(groupNumber+1);//could only happen when a card was tossed by user(in this or a previous round) thus this cant happen for last group
	}

}

int PlayerStatistics::getGroup( const Card * card )
{
	return (card->getVal()-1)/2;
}

double PlayerStatistics::getProbabilityOFHigherCard( const Card * card )
{
	int currGroup=getGroup(card);
	double res=0;
	for (int i=currGroup+1; i<7 i++)
	{
		res+=m_CardGroups[i];
	}
	return res/m_NumOfCards;

}
