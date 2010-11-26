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

void GamblingGame::newRound()
{
	initRound();
	//bettingPhase();
	getDecisions();
	closeRound();
	m_currPool=0;//Reset pool for next round
}

GamblingGame::GamblingGame():Game(GAMBLING)
{
	initGame();//call gambling game init
}

void GamblingGame::initGame()
{
	Game::initGame();
	m_initialDucats=UIs::GamblingUI::getInitialDucats();
	Gambler * pG;
	for (unsigned int i=0; i<m_numberOfplayers; i++)//add money to players balance which is 0 by default
	{
		pG=pG=(Gambler *)m_players[i];
		pG->addToBalance(m_initialDucats);
	}

}

void GamblingGame::initRound()
{
	Game::initGame();
	UIs::GamblingUI::plotGameScreen(m_numberOfplayers);

}
/*
void GamblingGame::bettingPhase() //MODIFY THIS
{
	Player* currPlayer;
	for (unsigned int i=0; i<m_numberOfplayers; i++)
	{
		currPlayer=getPlayerAt(i);
		currPlayer->makeBet();
		printPlayerBets(i);//this way the user can see his predecessors decisions
		if (currPlayer->getBet()==Gambler::FOLD)
		{
			returnCardForUser(i);
			//Do something to signify folding
		}
		else //here Player decides to PLAY
		{
			//Withdraw money from player to pot
			//Continue stuff...
		}
		Sleep(1500);
	}
}
*/