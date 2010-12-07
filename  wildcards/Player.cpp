#define _CRT_SECURE_NO_WARNINGS //To suppress warning on strcpy
#include "Player.h"



//************************************
// Method:    Player - constructor for player
// FullName:  Player::Player
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: const char * playerName -a name to be given to the player
// Parameter: bool iscomputer- a boolean representing if the player is a computer (optional -true by default value)
// Parameter: int numOfJokers- the number of joker in the game(for statistics usge)
// Parameter: GameTypes type- players type(NORMAL by default) 
//************************************
Player::Player( const char * playerName,bool iscomputer/*=true*/,int numOfJokers/*=2*/,GameTypes type/*=NORMAL*/ )
{
	m_statistics=new PlayerStatistics(numOfJokers);
	m_playerType=type;
	int size=strlen(playerName);
	m_name=new char[size+1];
	m_decision=KEEP;//just init
	strcpy(m_name,playerName);//copy his name
	m_isHuman=!iscomputer;//only two options because aliens suck at cards
	srand((unsigned int)time(0));//for decision
}
//************************************
// Method:    makeDecision - makes a decision whether to throw or keep the card
// FullName:  Player::makeDecision
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool Player::makeDecision()
{
	if (m_isHuman)//ask user
	{
		UIs::UI::displayMessage("Enter t to throw or k to keep the card");
		char UserDecison=UIs::UI::getUserGameInput();
		while(UserDecison!='k' && UserDecison!='t')//input isn't valid
		{
			UIs::UI::clearInputLine();
			UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use t to throw card and k to keep it");
			UserDecison=UIs::UI::getUserGameInput();
		}
		UIs::UI::clearErrorMessage();
		if (UserDecison=='k')
		{
			m_decision=KEEP;
		} 
		else
		{
			m_decision=THROW;
		}
	} 
	else	//Computer player random
	{
		int randDecide=m_statistics->shouldSwitch(m_card);
		if (randDecide)
		{
			m_decision=THROW;
		}
		else
		{
			m_decision=KEEP;
		}
	}
	return m_decision;
}

//************************************
// Method:    printPlayerDetails - prints the current players name and card
// FullName:  Player::printPlayerDetails
// Access:    public 
// Returns:   void
// Qualifier: virtual
// Parameter: int x - the x  axis value of the cards whereabouts on the screen
// Parameter: int y - the y  axis value of the cards whereabouts on the screen
// Parameter: bool showCard - -if false a blank card is displayed otherwise the player card is to be displayed
//************************************
void Player::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	UIs::UI::gotoxy(x,y);
	cout<<m_name; //Print player's name
	UIs::UI::setConsoleColors(UIs::UI::WHITE_BACK);
	if (showCard)
	{
		m_card->printcard(x,y+1); //Print player's card
	}
	else
	{
		(UIs::UI::BLANK_CARD).printcard(x,y+1);//print blank card
	}
	UIs::UI::setConsoleColors();//restore to default coloring(Green)
}



void Player::updateUserAboutRound( int numOfThrows,int numberOfplayers,... )
{
	va_list cards;
	va_start(cards, numberOfplayers);
	const Card * curr;
	if (m_decision==THROW)
	{
		numOfThrows--;
	}
	for (int i=0; i<numOfThrows;i++)
	{
		m_statistics->updateStatistics();
	}
	
	for (int i=0;i<numberOfplayers-1; i++)//do not include current player
	{
		curr=va_arg(cards, const Card *);
		if (curr->getVal()!=Card::VNONE)//not blank
		{
			m_statistics->updateStatistics(curr);
		}
	}

}