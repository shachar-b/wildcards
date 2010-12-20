#include "Poker.h"

Poker::Poker(void):Game()
{
}

Poker::~Poker(void)
{
}

void Poker::initRound()
{
	m_numberOfRounds++;
	char userInput='0';
	drawCardsForAllUsers();//non user cards are upside down

}

void Poker::getDecisions()
{
	Player* currPlayer;
	for (unsigned int i=0; i<m_numberOfplayers; i++)
	{
		currPlayer=getPlayerAt(i);
		if (*(currPlayer->getCard())>Card(Card::VNONE,Card::NONE))//has a card
		{
			currPlayer->makeDecision();
			UIs::UI::printPlayerDecision(i);//this way the user can see his predecessors decisions
			if (currPlayer->getDecision()==Player::THROW)
			{
				returnCardForUser(i);
				drawCardForUser(i);
			}
			Sleep(1500);
		}
	}

}

void Poker::decideWinners( int givenPoints/*=1*/ )
{

}

void Poker::initGame()
{
	m_endGame=false;
	m_numberOfRounds=0;
	int shuffleDepth;
	UIs::UI::plotWelcomeScreen();
	char* userName=NULL;
	int numOfJokers=UI::getMainScreenUserInput(m_numberOfplayers,shuffleDepth,userName);
	m_gameDeck->shuffle(shuffleDepth);
	addPlayer(userName,false);//add a human player
	delete []userName;//a copy is made in player- release the allocation
	char name[6]="comp";
	name[5]='\0';
	for (unsigned int i=1; i<m_numberOfplayers; i++)//define computer players
	{
		name[4]='0'+i;
		addPlayer(name); //Add a computer player
	}
	m_lastWinner=rand()%m_numberOfplayers;//decide who starts(since there is only one human player he starts at a random place and the computer order doesn't count)

}

const char * Poker::returnNameOfWinningPlayer()
{

}