#ifndef ___UI___H____
#define ___UI___H____
//includes
#include <iostream> 
using namespace std;
#include "card.h"
#include <windows.h>
#include <process.h>

//classes
class Player;

class point
{
private:
	int x,y;
public:
	point(){}
	point(int xCoordinate,int yCoordinate)
	{
		x=xCoordinate;
		y=yCoordinate;
	}
	~point(){}
	int getx()const{return x;}
	void setx(int val){ x=val;}
	int gety()const{return y;}
	void sety(int val){ y=val;}
};

class UI
{
private:
	int numberOfPlayers;
	static const int MAIN_SCREEN=0;
	static const int GAME_SCREEN=1;
	static const int NO_SCREEN=2;
	static const int GOODBYE_SCREEN=3;
	static const WORD WHITE_BACK=BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE|BACKGROUND_INTENSITY;
	int currScreen;
	point currInputArea;
	point currMessageArea;
	point currErrorArea;
	point playersCardsloc[4];
	Player * players[4];
	
	void clrscr();
	void drawLineOfCharsAt(int line,int fromcol,char ch='#');
	void drawColOfCharsAt( int col,int fromline,char ch='#' );
	void jumpToInputArea() const;
	void writeSomethingAt(const char * str,const point &place) const;
	void clearLine(int lineNumber,int fromCol=2) const;
	void UI::setConsoleColors(WORD back=BACKGROUND_GREEN,WORD text=0);


public:
	const Card BLANK_CARD;
	static void gotoxy(int, int);
	UI::UI();
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
	int  getMainScreenUserInput(int & numOfPlayers, int & shuffleDepth,char * &userName);
	void clearMassage() const;
	void clearErrorMessage() const;
	void printUserDetails(const Card & card,int playerNumber);
	char* getNameFromScreen(int maxNumOfChars);
	void clearConsole() const;
	void clearInputLine() const;
	void dispalyFlashingMessage(const char * text,const char * text2,unsigned int timesToFlash=6,unsigned int delay=500);
};

#endif