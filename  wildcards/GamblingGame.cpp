#include "GamblingGame.h"


void GamblingGame::bettingPhase() //MODIFY THIS
{
	Gambler* roundLeader=getGamblerAt(0);
	roundLeader->makeBet();//only first player makes a bet -> all other can match or fold
	UIs::GamblingUI::printPlayerBet(0);//this way the user can see his predecessors decisions

	for (unsigned int i=1; i<m_numberOfplayers; i++)
	{
		Gambler* currPlayer=getGamblerAt(i);
		//currPlayer->playOrFold(roundLeader->getCurrBet());
		UIs::GamblingUI::printPlayerBet(i);//this way the user can see his predecessors decisions
		if (currPlayer->getCurrBet()==Gambler::FOLD)
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

GamblingGame::GamblingGame():Game(GAMBLING)
{
	setPlayersInitialBalance();
}

void GamblingGame::setPlayersInitialBalance()
{
	m_initialDucats=UIs::GamblingUI::getInitialDucats();
	Gambler * pG;
	for (unsigned int i=0; i<m_numberOfplayers; i++)//add money to players balance which is 0 by default
	{
		pG=pG=(Gambler *)m_players[i];
		pG->addToBalance(m_initialDucats);
	}

}



void GamblingGame::initGame()
{
	Game::initGame();
	setPlayersInitialBalance();

	

}

void GamblingGame::givePoolToWinner()
{
	getGamblerAt(m_lastWinner)->addToBalance(m_currPool);

}

Gambler * GamblingGame::getGamblerAt( unsigned int place )
{
	return (Gambler *)getPlayerAt(place);

}
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

void GamblingGame::initRound()
{
	Game::initRound();
	UIs::GamblingUI::plotGameScreen(m_numberOfplayers);

}
