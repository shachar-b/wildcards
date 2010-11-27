#ifndef ___NORMALPLAYER___H____
#define ___NORMALPLAYER___H____
//includes
#include <iostream> 
using namespace std;
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include "UI.h"

//classes
class NormalPlayer:public Player
{
private:
	int m_score;
public:
	
	NormalPlayer(const char * playerName,bool iscomputer=true);
	~NormalPlayer(){;}
	void printPlayerDetails(int x,int y,bool showCard=true);
	//setter and getters
	int getScore(){return m_score;}
	void addToScore(int num){m_score+=num;}//assuming num>0
};

#endif