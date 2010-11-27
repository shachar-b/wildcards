#include "GamblingGame.h"

//************************************
// Method:    bettingPhase - Manages the gambling bit of the gambling game:
//							takes bets and asks players to complete the bet or fold.
// FullName:  GamblingGame::bettingPhase
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void GamblingGame::bettingPhase()
{
	Gambler* roundLeader=getGamblerAt(0);
	roundLeader->makeBet();//only first player makes a bet -> all others can match or fold
	m_currPool+=roundLeader->getCurrBet();
	UIs::GamblingUI::printCurrPot(m_currPool);
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
			UIs::GamblingUI::printCurrPot(m_currPool);
			UIs::GamblingUI::printUserDetails(i+1,currPlayer->isHumanPlayer());
		}
		Sleep(1500);
	}
}

//************************************
// Method:    GamblingGame - Gambling game constructor:
//								Game constructor is auto' called and then sets up the extra work.
// FullName:  GamblingGame::GamblingGame
// Access:    public 
// Returns:   
// Qualifier: :Game(GAMBLING)
//************************************
GamblingGame::GamblingGame():Game(GAMBLING)
{
	setPlayersInitialBalance();
	m_currPool=0;
}

//************************************
// Method:    setPlayersInitialBalance - balance is 0 by default,
//										adds currency to the players according to the requested amount.
// FullName:  GamblingGame::setPlayersInitialBalance
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
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

//************************************
// Method:    initGame - overwrite the base Game initializer.
// FullName:  GamblingGame::initGame
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void GamblingGame::initGame()
{
	Game::initGame();
	setPlayersInitialBalance();
	m_currPool=0;
}

//************************************
// Method:    givePoolToWinner - Awards the round winner with the money won.
// FullName:  GamblingGame::givePoolToWinner
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void GamblingGame::givePoolToWinner()
{
	getGamblerAt(m_lastWinner)->addToBalance(m_currPool);

}

//************************************
// Method:    getGamblerAt - returns a pointer to a gambler by casting from the players' deque.
// FullName:  GamblingGame::getGamblerAt
// Access:    private 
// Returns:   Gambler *
// Qualifier:
// Parameter: unsigned int place
//************************************
Gambler * GamblingGame::getGamblerAt( unsigned int place )
{
	return (Gambler *)getPlayerAt(place);

}

//************************************
// Method:    returnNameOfWinningPlayer - overwrite from base Game:
										//returns the name of the only player left with money.
// FullName:  GamblingGame::returnNameOfWinningPlayer
// Access:    protected 
// Returns:   const char *
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

//************************************
// Method:    newRound - Overwrites from base Game - added bettingPhase()
// FullName:  GamblingGame::newRound
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void GamblingGame::newRound()
{
	initRound();
	bettingPhase();
	getDecisions();
	closeRound();
	m_currPool=0;//Reset pool for next round
}

//************************************
// Method:    initRound - Expands base's initRound by plotting the correct game screen.
// FullName:  GamblingGame::initRound
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void GamblingGame::initRound()
{
	Game::initRound();
	UIs::GamblingUI::plotGameScreen(m_numberOfplayers);
}

//************************************
// Method:    closeRound - Expands base's closeRound by calling the correct decideWinners
							//and incorporating a check to see if only one man is left standing.
// FullName:  GamblingGame::closeRound
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
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