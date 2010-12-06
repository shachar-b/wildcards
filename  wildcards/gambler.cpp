#include "gambler.h"


//************************************
// Method:    Gambler - initializes a new gambler
// FullName:  Gambler::Gambler
// Access:    public 
// Returns:   
// Qualifier: : Player(playerName,isComputer,GAMBLING)- make lower level know this is a gambling game
// Parameter: const char * playerName-the name of the current player (to be copied)
// Parameter: bool isComputer - true iff the player is non human
// Parameter: int initMoney - the initial amount of money for a player
// Parameter: int numOfJokers - the amount Jokers in this game
//************************************
Gambler::Gambler( const char * playerName,bool isComputer/*=true*/,int initMoney/*=1*/,int numOfJokers/*=2*/ ): Player(playerName,isComputer,numOfJokers,GAMBLING)
{
	m_money=initMoney;
}
//************************************
// Method:    printPlayerDetails- prints the current players name balance and decision
// FullName:  Gambler::printPlayerDetails
// Access:    public 
// Returns:   void
// Qualifier: const
// Parameter: int x - the x  axis value of the cards whereabouts on the screen
// Parameter: int y - the y axis value of the cards whereabouts on the screen
// Parameter: bool showCard -if false a blank card is displayed otherwise the player card is to be displayed
//************************************
void Gambler::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	Player::printPlayerDetails(x,y,showCard);//print details
	UIs::UI::gotoxy(x,y+5);
	cout<<"               ";
	UIs::UI::gotoxy(x,y+5);
	cout<<"balance: "<<m_money;
}

//************************************
// Method:    makeBet - make a bet for the current player
// FullName:  Gambler::makeBet 
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
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
		int randBet=rand()%20+1;//the bet is 1 to 20
		m_currBet=min(randBet,m_money);//player cant bet on more then what he got
	}
	this->withdrawFromBalance(m_currBet);//take the bet from his balance
}

//************************************
// Method:    playOrFold - decides whether the player stays or folds from current round
// FullName:  Gambler::playOrFold
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int betToMatch - a bet given by the first user
//************************************
void Gambler::playOrFold( int betToMatch )
{
	if (m_money<betToMatch)//no money
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
			
			if (m_statistics->shouldbet(m_card,betToMatch,m_money))
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