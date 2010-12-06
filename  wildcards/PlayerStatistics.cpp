#include "PlayerStatistics.h"



PlayerStatistics::PlayerStatistics(const Deck & deck,int numOfJokers):CurrentDeck(deck)
{
	CardGroups[LOW]=16;//2-5
	CardGroups[MID]=16;//6-T
	CardGroups[HIGH]=16;//J-K
	CardGroups[PERM]=4+numOfJokers;//A-$


}
PlayerStatistics::~PlayerStatistics(void)
{
}

void PlayerStatistics::updateStatistics( const Card * curr/*=NULL*/ )
{
	if (curr==NULL)
	{
		int prob=(int)(rand()%2);
		CardGroups[prob]--;
	}
	else
	{
		if (curr->getSuit()<=Card.Five)
		{
			CardGroups[LOW]--;
		} 
		else if (curr->getSuit()<=Card.Ten)
		{
			CardGroups[MID]--;
		}
		else if (curr->getSuit()<=Card.Ten)
		{
			CardGroups[HIGH]--;
		}
		else
		{
			CardGroups[PERM]--;
		}

	}

}