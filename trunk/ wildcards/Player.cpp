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

//************************************
// Method:    makeDecision - makes a decision whether to throw or keep the card
// FullName:  Player::makeDecision
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: UI * ui - a poiner to a ui in game screen from which to get input
//************************************
bool Player::makeDecision(UI * ui )
{
	if (isHuman)//ask user
	{
		char UserDecison=ui->getUserGameInput();
		while(UserDecison!='k' && UserDecison!='t')//input isn't valid
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
	else	//Computer player random
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