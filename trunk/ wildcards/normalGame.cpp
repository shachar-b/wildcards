#include "normalGame.h"



//************************************
// Method:    getNormalPlayerAt - returns a pointer the place player in the current game order or null if no such place
// FullName:  normalGame::getPlayerAt
// Access:    private 
// Returns:   NormalPlayer *-a pointer the place player in the current game order NULL if no such place
// Qualifier:
// Parameter: unsigned int place- a number from 0 to the number of players -1
//************************************
NormalPlayer * normalGame::getNormalPlayerAt( unsigned int place )
{
	if (place>(m_players.size()-1))//no such place
	{
		return NULL;
	}
	else
	{
		return (NormalPlayer*)m_players[getUserPlace(place)];;
	}
}


//************************************
// Method:    returnNameOfWinningPlayer - returns the name of the player with the highest score(or the last one if more then one)
// FullName:  normalGame::returnNameOfWinningPlayer
// Access:    private 
// Returns:   const char * - the name of the player with the highest score
// Qualifier:
//************************************
const char * normalGame::returnNameOfWinningPlayer()
{
	NormalPlayer * currPlayer=(NormalPlayer*)m_players[0];
	NormalPlayer * next;
	for(unsigned int i=1;i<m_numberOfplayers; i++)
	{
		next=(NormalPlayer*)m_players[i];
		if(next->getScore()>currPlayer->getScore())
		{
			currPlayer=next;
		}
	}
	return currPlayer->getName();
}

void normalGame::initRound()
{
	Game::initRound();
	UIs::NormalUI::plotGameScreen(m_numberOfplayers);

}