#include "gambler.h"

Gambler::Gambler(const char * playerName,bool isComputer/*=true*/): Player(playerName,isComputer)
{
	m_money=500;//define as initial value
}

void Gambler::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	Player::printPlayerDetails(x,y,showCard);//print details
	UI::gotoxy(x,y+6);
	cout<<"balance: "<<m_money;


}