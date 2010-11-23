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
	Gambler * currPlayer=(Gambler*)m_players[0];
	Gambler * next;
	for(unsigned int i=1;i<m_numberOfplayers; i++)
	{
		next=(Gambler*)m_players[i];
		if(next->getBalance()>currPlayer->getBalance())
		{
			currPlayer=next;
		}
	}
	return currPlayer->getName();
}