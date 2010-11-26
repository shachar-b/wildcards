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
// Method:    decideWinners - decide who is the winner of the current round and give him a point(if more then one joker last one is the winner and all jokers get a point) 
// FullName:  normalGame::decideWinners
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void normalGame::decideWinners(int pot/*=1*/)
{
	NormalPlayer * currWinner;
	NormalPlayer * next;
	int numOfJokers=countPlayerJokers();
	if (numOfJokers>0)
		for (unsigned int i=0; i<m_players.size(); i++)//more then one winner
		{
			next=(NormalPlayer*)m_players[i];
			if (*(next->getCard())==Card(Card::VJoker,Card::JOKER))//give a point to all jokers
			{
				next->addToScore(pot/numOfJokers+1);
				m_lastWinner=i;
			} 
		}//last one is considered winner of the round
	else//one winner
	{
		currWinner=(NormalPlayer*)m_players[0];
		m_lastWinner=0;
		for (unsigned int i=1; i<m_players.size(); i++)
		{
			next=(NormalPlayer*)m_players[i];
			if (*(currWinner->getCard())<*(next->getCard()))
			{
				currWinner=next; //otherwise do nothing
				m_lastWinner=i;
			}
		}
		currWinner->addToScore(1);
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