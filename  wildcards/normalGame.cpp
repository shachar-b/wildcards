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

//************************************
// Method:    initRound - Expands the base's initRound by plotting the correct game screen
// FullName:  normalGame::initRound
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void normalGame::initRound()
{
	Game::initRound();
	UIs::UI::plotGameScreen(m_numberOfplayers);
}

//************************************
// Method:    closeRound - Expands base's closeRound by calling the correct decideWinners.
// FullName:  normalGame::closeRound
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void normalGame::closeRound()
{
	decideWinners();//if more then one winner picks the last one
	Game::closeRound();
}