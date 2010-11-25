#include "GamblingGame.h"


void GamblingGame::givePoolToWinner()
{
	getGamblerAt(m_lastWinner)->addToBalance(m_currPool);

}

Gambler * GamblingGame::getGamblerAt( unsigned int place )
{
	return (Gambler *)getPlayerAt(place);

}
//************************************
// Method:    returnNameOfWinningPlayer - returns the name of the player with the highest score(or the last one if more then one)
// FullName:  normalGame::returnNameOfWinningPlayer
// Access:    private 
// Returns:   const char * - the name of the player with the highest score
// Qualifier:
//************************************
const char * GamblingGame::returnNameOfWinningPlayer()
{
	Gambler * currPlayer;
	for(unsigned int i=0;i<m_numberOfplayers; i++)
	{
		currPlayer=(Gambler*)m_players[i];
		if(currPlayer->getBalance()>0)
		{
			return currPlayer->getName();
		}
	}
	return NULL; //Will not happen as at least one player will have more than 0 money.
}
/*
void GamblingGame::decideWinners()
{
	NormalPlayer * currWinner;
	NormalPlayer * next;
	int numOfJokers=0;
	for (unsigned int i=0; i<m_players.size(); i++)//more then one winner
	{
		next=(Gambler*)m_players[i];
		if (next->getCard()==Card(Card::VJoker,Card::JOKER)//give a point to all jokers
		{
			numOfJokers++;
			next->addToScore(1);
			m_lastWinner=i;
		} 
	}//last one is considered winner of the round
	if (numOfJokers==0)//one winner
	{
		currWinner=(Gambler*)m_players[0];
		m_lastWinner=0;
		for (unsigned int i=1; i<m_players.size(); i++)
		{
			next=(Gambler*)m_players[i];
			if (*(currWinner->getCard())<*(next->getCard()))
			{
				currWinner=next; //otherwise do nothing
				m_lastWinner=i;
			}
		}
		currWinner->addToScore(1);
	}
}
*/