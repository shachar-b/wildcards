#include "gambler.h"

Gambler::Gambler(const char * playerName,bool isComputer/*=true*/,int initMoney/*=500*/): Player(playerName,isComputer)
{
	m_money=initMoney;//define as initial value
}

void Gambler::printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const
{
	Player::printPlayerDetails(x,y,showCard);//print details
	UI::gotoxy(x,y+6);
	cout<<"balance: "<<m_money;
}

bool Gambler::makeDecision( UI * ui ) //Incorporate extra decisions that gambler needs to make
{
	return Player::makeDecision(ui);
}