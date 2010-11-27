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