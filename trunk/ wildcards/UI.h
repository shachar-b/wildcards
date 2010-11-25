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
class Game;
enum GameTypes{NORMAL,GAMBLING};
namespace UIs{
	class  UI
	{
	public: 
		class point
		{
		private:
			int m_x,m_y;
		public:
			point(int xCoordinate=0,int yCoordinate=0)
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
	protected:
		static int m_numberOfPlayers;
		static const int MAIN_SCREEN=0;
		static const int GAME_SCREEN=1;
		static const int NO_SCREEN=2;
		static const int GOODBYE_SCREEN=3;
		static int m_currScreen;
		static point m_currInputArea;
		static point m_currMessageArea;
		static point m_currErrorArea;
		static point m_playersCardsloc[4];
		static Player * m_players[4];
		
		static void clrscr();
		static void drawLineOfCharsAt(int line,int fromcol,char ch='#');
		static void drawColOfCharsAt( int col,int fromline,char ch='#' );
		static void drawGameFrame();
		static void jumpToInputArea();
		static void writeSomethingAt(const char * str,const point &place);
		static void clearLine(int lineNumber,int fromCol=2);
		static void printGameInstructions();//overide
		static void printPlayerTable();//overide


	public:
		static const WORD WHITE_BACK=BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE|BACKGROUND_INTENSITY;
		static const Card BLANK_CARD;
		static void gotoxy(int, int);
		static void setConsoleColors(WORD back=BACKGROUND_GREEN,WORD text=0);
		UI();
		static void setPlayers(Player * p1,Player * p2,Player * p3=NULL,Player * p4=NULL);
		static void displayMessage(const char * message);
		static void displayErrorMessage(char * message);
		static void plotGameScreen(int NumOfPlayers);//overide
		static void plotWelcomeScreen();
		static void plotGoodbyeScreen(int numOfRounds,const char* nameOfWinner);
		static void showAllCards();
		static void drawNewRoundOfCards();
		static char getUserGameInput();
		static void printPlayerDecision(int playerNumber);//overide
		static int  getMainScreenUserInput(unsigned int & numOfPlayers, int & shuffleDepth,char * &userName);
		static void clearMassage();
		static void clearErrorMessage();
		static void printUserDetails(int playerNumber,bool showCard=true);
		static char* getNameFromScreen(int maxNumOfChars);
		static void clearConsole();
		static void clearInputLine();
		static void dispalyFlashingMessage(const char * text,const char * text2,unsigned int timesToFlash=6,unsigned int delay=500);
	};

	class NormalUI:public UI
	{
	protected:
		void printGameInstructions();
		static void printPlayerTable();
		void printUserDetails(int playerNumber,bool showCard=true );
	};

	class GamblingUI:public UI
	{
		protected:
			static const point m_POT_AREA; 
			void printGameInstructions();
			static void printPlayerTable();
		public:
			GamblingUI();
			 static void plotGameScreen(int NumOfPlayers);
			 void printUserDetails(int playerNumber,bool showCard=true);
	};
}

#endif