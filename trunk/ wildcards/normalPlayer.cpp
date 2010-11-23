#define _CRT_SECURE_NO_WARNINGS //To suppress warning on strcpy
#include "NormalPlayer.h"

//************************************
// Method:    NormalPlayer - constructor for player
// FullName:  NormalPlayer::NormalPlayer
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: const char * playerName -a name to be given to the player
// Parameter: bool iscomputer- a boolean representing if the player is a computer (optional -true by default value)
//************************************
NormalPlayer::NormalPlayer( const char * playerName,bool iscomputer/*='true'*/ ):Player(playerName,iscomputer)
{
	m_score=0;
}

void NormalPlayer::printPlayerDetails( int x,int y,bool showCard/* =true */ )
{
	Player::printPlayerDetails(x,y,showCard);
	UI::gotoxy(x,y+5);
	cout<<"score: "<<m_score;

}

