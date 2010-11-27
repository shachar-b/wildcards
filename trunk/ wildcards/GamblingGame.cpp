#include "GamblingGame.h"


void GamblingGame::bettingPhase() //MODIFY THIS
{
	Gambler* roundLeader=getGamblerAt(0);
	roundLeader->makeBet();//only first player makes a bet -> all others can match or fold
	m_currPool+=roundLeader->getCurrBet();
	UIs::GamblingUI::printUserDetails(1,roundLeader->isHumanPlayer());
	UIs::GamblingUI::printPlayerBet(0);//this way the user can see his predecessors decisions

	for (unsigned int i=1; i<m_numberOfplayers; i++)
	{
		Gambler* currPlayer=getGamblerAt(i);
		currPlayer->playOrFold(roundLeader->getCurrBet());
		UIs::GamblingUI::printPlayerBet(i);//this way the user can see his predecessors decisions
		if (currPlayer->getCurrBet()==Gambler::FOLD)
		{
			returnCardForUser(i);
			currPlayer->setCard(&(UIs::UI::BLANK_CARD));
		}
		else //here Player decides to PLAY
		{
			currPlayer->withdrawFromBalance(currPlayer->getCurrBet());
			m_currPool+=currPlayer->getCurrBet();
			UIs::GamblingUI::printUserDetails(i+1,currPlayer->isHumanPlayer());
		}
		Sleep(1500);
	}
}

GamblingGame::GamblingGame():Game(GAMBLING)
{
	setPlayersInitialBalance();
	m_currPool=0;
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
	m_currPool=0;
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
	bettingPhase();
	getDecisions();
	closeRound();
	m_currPool=0;//Reset pool for next round
}

void GamblingGame::initRound()
{
	Game::initRound();
	UIs::GamblingUI::plotGameScreen(m_numberOfplayers);
}

void GamblingGame::closeRound()
{
	decideWinners(m_currPool);//if more then one winner picks the last one
	Game::closeRound();
	int numOfPlayersWithoutMoney=0;
	for (unsigned int i=1; i<m_numberOfplayers; i++)//make sure game isnt over (no need to chack first player for getGamblerAt(0) returns last winner)
	{
		if (getGamblerAt(i)->isBroke())
		{
			numOfPlayersWithoutMoney++;
		}
	}
	m_endGame=(m_numberOfplayers-1)==numOfPlayersWithoutMoney; // are all players borke(but the first one)


}