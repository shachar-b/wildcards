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
// Parameter: int numOfJokers- the number of joker in the game(auto set to 0)
// Parameter: GameTypes type- players type(NORMAL by default) 
//************************************
Player::Player( const char * playerName,bool iscomputer/*=true*/,int numOfJokers/*=0*/)
{
	m_hand=new Hand();
	int size=strlen(playerName);
	m_name=new char[size+1];
	m_decision[0]=KEEP;//just init
	m_decision[1]=KEEP;//just init
	m_decision[2]=KEEP;//just init
	strcpy(m_name,playerName);//copy his name
	m_isHuman=!iscomputer;//only two options because aliens suck at cards
	m_score=0;
}

//************************************
// Method:    makeDecision - makes a decision whether to throw or keep the card in slot cardNumber
// FullName:  Player::makeDecision
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int cardNumber - a number from 1 to 3
//************************************
bool Player::makeDecision( int cardNumber )
{
	if (m_isHuman)//ask user
	{
		string buff="Enter t to throw or k to keep the card number ";
		buff+='0'+cardNumber;
		UIs::UI::displayMessage(buff);
		char UserDecison=UIs::UI::getUserGameInput();
		while(UserDecison!='k' && UserDecison!='t')//input isn't valid
		{
			UIs::UI::clearInputLine();
			buff="ERROR:invalid input for card ";
			buff+='0'+cardNumber;
			buff+=": use t to throw card and k to keep it ";
			UIs::UI::displayErrorMessage(buff);
			UserDecison=UIs::UI::getUserGameInput();
		}
		UIs::UI::clearErrorMessage();
		if (UserDecison=='k')
		{
			m_decision[cardNumber-1]=KEEP;
		} 
		else
		{
			m_decision[cardNumber-1]=THROW;
		}
	} 
	else	//Computer player random - srand() was called in deck initialization.
	{
		int randDecide=rand()%2;
		if (randDecide)
		{
			m_decision[cardNumber-1]=THROW;
		}
		else
		{
			m_decision[cardNumber-1]=KEEP;
		}
	}
	UIs::UI::clearConsole();
	return m_decision[cardNumber-1];
}

//************************************
// Method:    printPlayerDetails - prints the current players name and card
// FullName:  Player::printPlayerDetails
// Access:    public 
// Returns:   void
// Qualifier: virtual
// Parameter: int x - the x  axis value of the cards whereabouts on the screen
// Parameter: int y - the y  axis value of the cards whereabouts on the screen
// Parameter: bool showCards - -if false a blank card is displayed otherwise the player card is to be displayed
//************************************
void Player::printPlayerDetails( int x,int y,bool showCards/*=true*/ ) const
{
	UIs::UI::gotoxy(x,y);
	cout<<m_name; //Print player's name
	if (showCards)
	{
		m_hand->printHand(x,y+1); //Print player's cards
	}
	else
	{
		(UIs::UI::BLANK_CARD).printcard(x,y+1);//print blank card
	}
	UIs::UI::gotoxy(x,y+6);
	cout<<"score: "<<m_score;
}