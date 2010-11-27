#include "gambler.h"

Gambler::Gambler(const char * playerName,bool isComputer/*=true*/,int initMoney/*=1*/): Player(playerName,isComputer,GAMBLING)
{
	m_money=initMoney;//define as initial value
}

void Gambler::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	Player::printPlayerDetails(x,y,showCard);//print details
	UIs::UI::gotoxy(x,y+5);
	cout<<"               ";
	UIs::UI::gotoxy(x,y+5);
	cout<<"balance: "<<m_money;
}

bool Gambler::makeDecision() //Incorporate extra decisions that gambler needs to make
{
	return Player::makeDecision();
}

void Gambler::makeBet()
{
	if (this->isHumanPlayer())
	{
		UIs::UI::displayMessage("Place your bet: (between 1 to 20)");
		cin >> m_currBet;
		while (m_currBet<1 || m_currBet>20 || m_currBet > m_money)
		{
			if (m_currBet > m_money)
				UIs::UI::displayErrorMessage("Invalid bet! You don't have enough money.");
			else
				UIs::UI::displayErrorMessage("Invalid bet! Must be between 1 to 20.");
			cin >> m_currBet;
		}
		UIs::GamblingUI::clearConsole();
		cin.ignore(cin.rdbuf()->in_avail());//flush
	}
	else //Computer player
	{
		int randBet=rand()%20+1;
		m_currBet=min(randBet,m_money);
	}
	this->withdrawFromBalance(m_currBet);
}

void Gambler::playOrFold( int betToMatch )
{
	if (m_money<betToMatch)
	{
		m_currBet=FOLD;
	}
	else //Has enough money
	{
		if (this->isHumanPlayer())
		{
			UIs::UI::displayMessage("Match bet? y/n");
			char UserDecison=UIs::UI::getUserGameInput();
			while(UserDecison!='y' && UserDecison!='n')//input isn't valid
			{
				UIs::UI::clearInputLine();
				UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use y to match bet and n to fold");
				UserDecison=UIs::UI::getUserGameInput();
			}
			UIs::UI::clearConsole();
			if (UserDecison=='y')
			{
				m_currBet=betToMatch;
			} 
			else
			{
				m_currBet=FOLD;
			}
		}
		else //Computer controlled player
		{
			if (rand()%2) //Random decision by computer
			{
				m_currBet=betToMatch;
			}
			else
			{
				m_currBet=FOLD;
			}

		}
	}

}