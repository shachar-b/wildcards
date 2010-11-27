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
//************************************
Player::Player( const char * playerName,bool iscomputer/*='true'*/,GameTypes type /*=NORMAL*/ )
{
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
		int randDecide=rand()%2;
		if (randDecide)
		{
			m_decision=KEEP;
		}
		else
		{
			m_decision=THROW;
		}
	}
	return m_decision;
}

//************************************
// Method:    printPlayerDetails
// FullName:  Player::printPlayerDetails
// Access:    public 
// Returns:   void
// Qualifier: virtual
// Parameter: int x
// Parameter: int y
// Parameter: bool showCard
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
