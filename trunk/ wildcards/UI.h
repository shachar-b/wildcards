//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise:  Question:
//File name: UI.h
#ifndef ___UI___H____
#define ___UI___H____
//includes
#include <iostream> 
using namespace std;
#include "card.h"
#include <windows.h>
#include <process.h>

//defines

//consts
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
	int currScreen;
	point currInputArea;
	point currMessageArea;
	point currErrorArea;
	point playersCardsloc[4];
	Player * players[4];
	void gotoxy(int, int) const;
	void clrscr();
	void drawLineOfCharsAt(int line,int fromcol,char ch='#');
	void drawColOfCharsAt( int col,int fromline,char ch='#' );
	void jumpToInputArea() const;
	void writeSomthingAt(const char * str,const point &place) const;
	void clearLine(int lineNumber,int fromCol=2) const;



public:
	Card BLANK_CARD;
	UI::UI();
	void setPlayers(Player * p1,Player * p2,Player * p3=NULL,Player * p4=NULL);
	void displayMessage(const char * message)const;
	void displayErrorMassage(char * message);
	void plotGameScreen(int NumOfPlayers);
	void plotWelcomeScreen();
	void plotGoodbyeScreen(int numOfRounds,const char* nameOfWinner);
	void showAllCards();
	void drawNewRoundOfCards();
	char getUserGameInput();
	void printPlayerDecision(int playerNumber);
	void setPlayer( int userNumer,Player * player );
	int  getMainScreenUserInput(int & numOfPlayers, int & shuffleDepth,char * &userName);
	void clearMassage() const;
	void clearErrorMassage() const;
	void printUserDetails(const Card & card,int playerNumber);
	char* getNameFromScreen(int maxNumOfChars);
	void clearConsole() const;
	void clearInputLine() const;
};




//function declaration
#endif