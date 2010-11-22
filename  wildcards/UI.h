#ifndef ___UI___H____
#define ___UI___H____
//includes
#include <iostream> 
using namespace std;
#include "card.h"
#include <windows.h>
#include <process.h>
#include "game.h"

//classes
class Player;
class Game;

class point
{
private:
	int m_x,m_y;
public:
	point(){}
	point(int xCoordinate,int yCoordinate)
	{
		m_x=xCoordinate;
		m_y=yCoordinate;
	}
	~point(){}
	int getx()const{return m_x;}
	void setx(int val){ m_x=val;}
	int gety()const{return m_y;}
	void sety(int val){ m_y=val;}
};

class UI
{
private:
	int m_numberOfPlayers;
	static const int MAIN_SCREEN=0;
	static const int GAME_SCREEN=1;
	static const int NO_SCREEN=2;
	static const int GOODBYE_SCREEN=3;
	int m_currScreen;
	point m_currInputArea;
	point m_currMessageArea;
	point m_currErrorArea;
	point m_playersCardsloc[4];
	Player * m_players[4];
	GameTypes m_gameType;
	
	void clrscr();
	void drawLineOfCharsAt(int line,int fromcol,char ch='#');
	void drawColOfCharsAt( int col,int fromline,char ch='#' );
	void jumpToInputArea() const;
	void writeSomethingAt(const char * str,const point &place) const;
	void clearLine(int lineNumber,int fromCol=2) const;


public:
	static const WORD WHITE_BACK=BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE|BACKGROUND_INTENSITY;
	static const Card BLANK_CARD;
	static void gotoxy(int, int);
	static void setConsoleColors(WORD back=BACKGROUND_GREEN,WORD text=0);
	UI(GameTypes gameType);
	void setPlayers(Player * p1,Player * p2,Player * p3=NULL,Player * p4=NULL);
	void displayMessage(const char * message)const;
	void displayErrorMessage(char * message);
	void plotGameScreen(int NumOfPlayers);
	void plotWelcomeScreen();
	void plotGoodbyeScreen(int numOfRounds,const char* nameOfWinner);
	void printGameInstructions();
	void showAllCards();
	void drawNewRoundOfCards();
	char getUserGameInput();
	void printPlayerDecision(int playerNumber);
	int  getMainScreenUserInput(unsigned int & numOfPlayers, int & shuffleDepth,char * &userName);
	void clearMassage() const;
	void clearErrorMessage() const;
	void printUserDetails(int playerNumber,bool showCard=true);
	char* getNameFromScreen(int maxNumOfChars);
	void clearConsole() const;
	void clearInputLine() const;
	void dispalyFlashingMessage(const char * text,const char * text2,unsigned int timesToFlash=6,unsigned int delay=500);
};

#endif