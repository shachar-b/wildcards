#include "gambler.h"

Gambler::Gambler(const char * playerName,bool isComputer/*=true*/,int initMoney/*=500*/): Player(playerName,isComputer,GAMBLING)
{
	m_money=initMoney;//define as initial value
}

void Gambler::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	Player::printPlayerDetails(x,y,showCard);//print details
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
		while (m_currBet<1 || m_currBet>20)
		{
			UIs::UI::displayErrorMessage("Invalid bet! Must be between 1 to 20.");
			cin >> m_currBet;
		}
		UIs::UI::clearErrorMessage();
	}
	else
	{
		m_currBet=min(rand()%20+1,m_money);
	}

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
			UIs::UI::displayMessage("Match bet?");
			char UserDecison=UIs::UI::getUserGameInput();
			while(UserDecison!='y' && UserDecison!='n')//input isn't valid
			{
				UIs::UI::clearInputLine();
				UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use y to match bet and n to fold");
				UserDecison=UIs::UI::getUserGameInput();
			}
			UIs::UI::clearErrorMessage();
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