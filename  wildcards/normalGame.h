#ifndef ___NORMAL_GAME___H____
#define ___NORMAL_GAME___H____
//includes
#include <iostream> 
using namespace std;
#include "normalPlayer.h"
#include "UI.h"
#include "deck.h"
#include <deque>
#include <dos.h>
#include "game.h"

//classes
class normalGame: public Game
{
protected:
	NormalPlayer * getNormalPlayerAt(unsigned int place);
	Player * getPlayerAt(unsigned int place);
	void decideWinners();
	const char * returnNameOfWinningPlayer();

public:
};

#endif