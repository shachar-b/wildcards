#include "PlayerStatistics.h"



PlayerStatistics::PlayerStatistics(const Deck * deck,int numOfJokers):CurrentDeck(deck)
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
		CardGroups[prob]--; //Assume the player threw a low or a middle card
	}
	else
	{
		CardGroups[getCardType(curr)]--;
	}
}

int PlayerStatistics::getCardType( const Card * card ) const
{
	if (card->getVal()<=Card::Five)
	{
		return LOW;
	} 
	else if (card->getVal()<=Card::Nine)
	{
		return MID;
	}
	else if (card->getVal()<=Card::King)
	{
		return HIGH;
	}
	else
	{
		return PERM;
	}
}