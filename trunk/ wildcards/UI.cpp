//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise:  Question:
//File name: UI.cpp
#include "UI.h"
#include "Player.h"


UI::UI():BLANK_CARD(Card(Card::VNONE,Card::NONE))

{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		BACKGROUND_GREEN);
	currScreen=NO_SCREEN;
	numberOfPlayers=0;
	playersCardsloc[0]=point(7,1);
	playersCardsloc[1]=point(68,1);
	playersCardsloc[2]=point(68,10);
	playersCardsloc[3]=point(7,10);
}

void UI::setPlayers( Player * p1,Player * p2,Player * p3/*=NULL*/,Player * p4/*=NULL*/ )
{
	players[0]=p1;
	players[1]=p2;
	players[2]=p3;
	players[3]=p4;

}
void UI::plotGameScreen( int NumOfPlayers)
{
	currScreen=GAME_SCREEN;
	currErrorArea=point(3,20);
	currMessageArea=point(3,21);
	currInputArea=point(24,22);
	clrscr();
	drawLineOfCharsAt(0,0);
	drawColOfCharsAt(0,1);
	drawLineOfCharsAt(24,1);
	drawLineOfCharsAt(19,1);
	drawColOfCharsAt(79,1);
	displayMessage("Enter t to throw or k to keep the card");
	gotoxy(2,22);
	cout<<"enter your selection:  ";
	drawNewRoundOfCards();
	jumpToInputArea();
}

void UI::plotWelcomeScreen()
{
	currScreen=GAME_SCREEN;
	currErrorArea=point(3,20);
	currMessageArea=point(3,21);
	currInputArea=point(3,22);
	clrscr();
	drawLineOfCharsAt(0,0);
	drawColOfCharsAt(0,1);
	drawLineOfCharsAt(24,1);
	drawLineOfCharsAt(19,1);
	drawColOfCharsAt(79,1);
	gotoxy(10,10);
	cout<<"Welcome To WildCards!  ";
	jumpToInputArea();
}

void UI::plotGoodbyeScreen( int numOfRounds,const char* nameOfWinner)
{
	currScreen=GOODBYE_SCREEN;
	clrscr();
	cout << "Game results:"<< endl;
	cout << "Number of rounds played in recent game: " << numOfRounds << endl;
	for (int i=0; i<numberOfPlayers; i++)
	{
		cout<< players[i]->getName() << "'s score: " << players[i]->getScore() << endl;
	}
	cout << "Game winner is: " << nameOfWinner << " !!!!!" << endl;
	gotoxy(0,12);
	cout << "Thank you for playing WildCards by Omer Shenhar and Shachar Butnaro!" << endl;
	system("PAUSE");
}

void UI::clrscr()
{
	system("cls");
}

void UI::gotoxy( int x, int y) const
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}


void UI::jumpToInputArea() const
{
	gotoxy(currInputArea.getx(),currInputArea.gety());
}

void UI::writeSomthingAt(const char * str,const point & place ) const
{
	gotoxy(place.getx(),place.gety());
	cout<<str;
}

void UI::displayMessage(const char * message) const
{	
	clearMassage();
	writeSomthingAt(message,currMessageArea);
	jumpToInputArea();
}
void UI::displayErrorMassage( char * message )
{
	clearErrorMassage();
	writeSomthingAt(message,currErrorArea);
	jumpToInputArea();
}

void UI::clearLine( int lineNumber ,int fromCol/*=2*/) const
{
	gotoxy(fromCol,lineNumber);
	for (int i=fromCol;i<79; i++)
	{
		cout<<' ';
	}
	jumpToInputArea();
}
void UI::clearConsole() const
{
	clearErrorMassage();
	clearMassage();
	clearInputLine();
}
void UI::clearInputLine() const
{
	clearLine(currInputArea.gety(),currInputArea.getx());
}
void UI::clearMassage() const
{
	clearLine(currMessageArea.gety(),currMessageArea.getx());
}

void UI::clearErrorMassage()const
{
	clearLine(currErrorArea.gety(),currErrorArea.getx());
}

void UI::printUserDetails( const Card & myCard,int playerNumber )
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMassage("ERROR: can only draw cards at game screen");
		return;
	}
	else if (playerNumber>numberOfPlayers || playerNumber<1)
	{
		displayErrorMassage("ERROR: iligal player number");
		return;
	}
	point start=playersCardsloc[playerNumber-1];
	gotoxy(start.getx(),start.gety());
	cout<<players[playerNumber-1]->getName();
	myCard.printcard(start.getx(),start.gety()+1);
	gotoxy(start.getx(),start.gety()+5);
	cout<<"score:"<<players[playerNumber-1]->getScore();
	jumpToInputArea();
}

void UI::drawLineOfCharsAt( int line,int fromcol,char ch )
{
	for (int i=fromcol;i<80; i++)
	{
		gotoxy(i,line);
		cout<<ch;
	}
}

void UI::drawColOfCharsAt( int col,int fromline,char ch )
{
	for (int i=fromline;i<25; i++)
	{
		gotoxy(col,i);
		cout<<ch;
	}
}

char UI::getUserGameInput()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMassage("ERROR: getUserGameInput called out of game screen");
		return '?';
	}
	char junk;
	char input;
	cin.get(input);
	cin.get(junk);
	jumpToInputArea();
	return input;
}

char* UI::getNameFromScreen(int maxNumOfChars)
{
	int i=0;
	char* result= new char[maxNumOfChars+1];
	char curr;
	cin.get(curr);
	for (i; i<maxNumOfChars && curr!='\n'; i++)
	{
		result[i]=curr;
		cin.get(curr);
	}
	while(curr!='\n')
	{
		cin.get(curr);
	}
	result[i]='\0';
	return result;
}

int UI::getMainScreenUserInput(int & numOfPlayers, int & shuffleDepth,char * &userName)
{
	int numOfJokers;
	char junk;
	displayMessage("please enter your name(up to 10 chars): ");
	userName=getNameFromScreen(10);
	clearConsole();
	jumpToInputArea();
	displayMessage("please enter Number of players(2-4):");
	cin >> numOfPlayers;
	while(numOfPlayers<2|| numOfPlayers>4)
	{
		clearInputLine();
		displayErrorMassage("illegal input please enter Number of players(2-4):");
		cin >> numOfPlayers;
	}
	numberOfPlayers=numOfPlayers;
	clearConsole();
	jumpToInputArea();
	displayMessage("Please enter shuffle depth:");
	cin>>shuffleDepth;			
	while(shuffleDepth<=0)
	{
		clearInputLine();
		displayErrorMassage("illegal input please enter shuffle depth you want(1 or larger):");
		cin>>shuffleDepth;	
	}
	clearConsole();
	displayMessage("please enter Number of jokers you want(2-3):");
	cin >> numOfJokers;
	while(numOfJokers<2|| numOfJokers>3)
	{
		clearInputLine();
		displayErrorMassage("illegal input please enter Number of jokers you want(2-3):");
		cin >> numOfJokers;
	}
	clearConsole();
	cin.get(junk);//clear /n
	return numOfJokers;
}

void UI::setPlayer( int userNumer,Player * player )
{
	if (userNumer>numberOfPlayers || userNumer<1)
	{
		displayErrorMassage("ERROR: illegal player number");
		return;
	}
	players[userNumer-1]=player;
}

void UI::showAllCards()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMassage("ERROR: showAllCards called out of game screen");
		return ;
	}
	for (int i=0; i<numberOfPlayers;i++)
	{
		printUserDetails(*players[i]->getCard(),i+1);
	}
	jumpToInputArea();
}

void UI::drawNewRoundOfCards()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMassage("ERROR: drawNewRoundOfCards called out of game screen");
		return ;
	}
	for (int i=0; i<numberOfPlayers;i++)
	{
		if (players[i]->isHumanPlayer())
		{
			printUserDetails(*players[i]->getCard(),i+1);
		}
		else
		{
			printUserDetails(BLANK_CARD,i+1);
		}
	}
	jumpToInputArea();
}

void UI::printPlayerDecision(int playerNumber)
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMassage("ERROR: printAllDecitions called out of game screen");
		return ;
	}
	point start;	
	start=playersCardsloc[playerNumber];
	gotoxy(start.getx(),start.gety()+6);
	if(players[playerNumber]->getDecision()==Player::KEEP)
		{
			cout<<"Keeps card";
		}
		else
		{
			cout<<"Throws card";
		}
	jumpToInputArea();
}