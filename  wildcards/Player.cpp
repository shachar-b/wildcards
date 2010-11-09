



//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Monday 01/11/10
//Exercise: 2 Question:
//File name: Player.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Player.h"



Player::Player( const char * playerName,bool iscomputer/*='true'*/ )
{
	int size=strlen(playerName);
	name=new char[size+1];
	decision=KEEP;//just init
	strcpy(name,playerName);//copy his name
	isHuman=!iscomputer;//only two options because aliens suck at cards
	score=0;
	srand((unsigned int)time(0));//for decision


}
bool Player::makeDecision(UI * ui )
{
	if (isHuman)
	{
		char UserDecison=ui->getUserGameInput();
		while(UserDecison!='k' && UserDecison!='t')//input isnt valid
		{
			ui->clearInputLine();
			ui->displayErrorMassage("ERROR:the input you entered is invalid: use t to throw card and k to keep it");
			UserDecison=ui->getUserGameInput();
		}
		ui->clearErrorMassage();
		if (UserDecison=='k')
		{
			decision=KEEP;
		} 
		else
		{
			decision=THROW;
		}

	} 
	else	//Computer player
	{
		int randDecide=rand()%2;
		if (randDecide)
		{
			decision=KEEP;
		}
		else
		{
			decision=THROW;
		}
	}
	return decision;
}