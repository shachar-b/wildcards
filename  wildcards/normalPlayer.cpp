#define _CRT_SECURE_NO_WARNINGS //To suppress warning on strcpy
#include "NormalPlayer.h"

//************************************
// Method:    NormalPlayer- constructor for player
// FullName:  NormalPlayer::NormalPlayer
// Access:    public 
// Returns:   
// Qualifier: :Player(playerName,iscomputer)
// Parameter: const char * playerName -a name to be given to the player
// Parameter: bool iscomputer- a boolean representing if the player is a computer (optional -true by default value)
// Parameter: int numOfJokers - the amount Jokers in this game
//************************************
NormalPlayer::NormalPlayer( const char * playerName,bool iscomputer/*='true'*/ ,int numOfJokers/*=2*/):Player(playerName,iscomputer,numOfJokers)
{
	m_score=0;
}

//************************************
// Method:    printPlayerDetails - prints the current players name and score
// FullName:  NormalPlayer::printPlayerDetails
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int x - the x  axis value of the cards whereabouts on the screen
// Parameter: int y - the y axis value of the cards whereabouts on the screen
// Parameter: bool showCard -if false a blank card is displayed otherwise the player card is to be displayed
//************************************
void NormalPlayer::printPlayerDetails( int x,int y,bool showCard/* =true */ )
{
	Player::printPlayerDetails(x,y,showCard);
	UIs::UI::gotoxy(x,y+5);
	cout<<"score: "<<m_score;
}