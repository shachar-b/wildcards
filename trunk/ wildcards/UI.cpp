#include "UI.h"
#include "Player.h"

//************************************
// Method:    UI - Constructor for UI - also sets up a blank card used to hide the cards of other players.
// FullName:  UI::UI
// Access:    public 
// Returns:   
// Qualifier: :BLANK_CARD(Card(Card::VNONE,Card::NONE))
//************************************
UI::UI():BLANK_CARD(Card(Card::VNONE,Card::NONE))
{
	ShowWindow( GetConsoleWindow(), SW_MAXIMIZE); //To maximize window size
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	setConsoleColors(BACKGROUND_GREEN);
	currScreen=NO_SCREEN;
	numberOfPlayers=0;
	playersCardsloc[0]=point(7,1);
	playersCardsloc[1]=point(68,1);
	playersCardsloc[2]=point(68,10);
	playersCardsloc[3]=point(7,10);
}

//************************************
// Method:    setPlayers - Receives the players and puts them in the players' array.
// FullName:  UI::setPlayers
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Player * p1
// Parameter: Player * p2
// Parameter: Player * p3 - Default value is NULL
// Parameter: Player * p4 - Default value is NULL
//************************************
void UI::setPlayers( Player * p1,Player * p2,Player * p3/*=NULL*/,Player * p4/*=NULL*/ )
{
	players[0]=p1;
	players[1]=p2;
	players[2]=p3;
	players[3]=p4;
}

//************************************
// Method:    plotGameScreen- prints the game screen and informs user of actions available
// FullName:  UI::plotGameScreen
// Access:    public
// Returns:   void
// Qualifier: 
// Parameter: int NumOfPlayers - an integer denominating the number of players. between 2-4.
//************************************
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

//************************************
// Method:    plotWelcomeScreen- prints the welcome screen.
// FullName:  UI::plotWelcomeScreen
// Access:    public
// Returns:   void
// Qualifier: 
//************************************
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
	printGameInstructions();
	jumpToInputArea();
}

//************************************
// Method:    plotGoodbyeScreen- prints the game screen and informs user of actions available
// FullName:  UI::plotGoodbyeScreen
// Access:    public
// Returns:   void
// Qualifier: 
// Parameter: int NumOfRounds - an integer denominating the number of rounds played in last game. >0
// Parameter: int nameOfWinner - The name of a player which achieved the highest score in last game.
//************************************
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

//************************************
// Method:    printGameInstructions - Prints the rules and instructions to user at beginning of game.
// FullName:  UI::printGameInstructions
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void UI::printGameInstructions()
{
	writeSomethingAt("Welcome To WildCards!",point(28,2));
	writeSomethingAt("Game instructions:",point(2,4));
	writeSomethingAt("First, follow on-screen instructions to enter your name,",point(2,5));
	writeSomethingAt("the number of players, shuffle depth (how many times to shuffle),",point(2,6));
	writeSomethingAt("and the number of jokers. You can have either 2 or 3 jokers in the deck.",point(2,7));
	writeSomethingAt("Each player gets a card (which no other player can see),",point(2,9));
	writeSomethingAt("And can choose to keep it, or to throw it and get a new one.",point(2,10));
	writeSomethingAt("After all players have made their choices, all cards are shown",point(2,11));
	writeSomethingAt("and the player with the highest ranking card is declared the winner.",point(2,12));
	writeSomethingAt("Suit values are (lowest to highest): Spades, Clubs, Diamonds, Hearts.",point(2,13));	
	writeSomethingAt("Card values are (lowest to highest):",point(2,14));
	writeSomethingAt("2,3,4,5,6,7,8,9,T(10),J(Jack),Q(Queen),K(King),A(Ace),$(Joker).",point(8,15));
	writeSomethingAt("At the end of each round you will have the chance to:",point(2,17));
	writeSomethingAt("c- continue to next round, n- reset settings and start over, e- exit game.",point(2,18));
}

//************************************
// Method:    clrscr- Clears the screen.
// FullName:  UI::clrscr
// Access:    private
// Returns:   void
// Qualifier: 
//************************************
void UI::clrscr()
{
	system("cls");
}

//************************************
// Method:    gotoxy- moves the cursor to the poing (x,y) on screen.
// FullName:  UI::gotoxy
// Access:    private
// Returns:   void
// Qualifier: const
// Parameter: int x - width position on screen.
// Parameter: int x - height position on screen.
//************************************
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

//************************************
// Method:    jumpToInputArea- using gotoxy(), jumps to the current input area
// FullName:  UI::jumpToInputArea
// Access:    private
// Returns:   void
// Qualifier: const
//************************************
void UI::jumpToInputArea() const
{
	gotoxy(currInputArea.getx(),currInputArea.gety());
}

//************************************
// Method:    writeSomethingAt- writes a string to the screen at the requested place.
// FullName:  UI::writeSomethingAt
// Access:    private
// Returns:   void
// Qualifier: const
// Parameter: const char* str - text to write.
// Parameter: const point& place - the point at which to write.
//************************************
void UI::writeSomethingAt(const char * str,const point & place ) const
{
	gotoxy(place.getx(),place.gety());
	cout<<str;
}

//************************************
// Method:    displayMessage - writes a text to the current message area.
// FullName:  UI::displayMessage
// Access:    public
// Returns:   void
// Qualifier: const
// Parameter: const char* message - the text to write.
//************************************
void UI::displayMessage(const char * message) const
{	
	clearMassage();
	writeSomethingAt(message,currMessageArea);
	jumpToInputArea();
}

//************************************
// Method:    displayFlashingMessage - displays a flashing message by alternating between two messages.
// FullName:  UI::displayFlashingMessage
// Access:    public
// Returns:   void
// Qualifier: 
// Parameter: const char* text - first message to display
// Parameter: const char* text2 - second message to display
// Parameter: unsigned int timeToFlash - number of repetitions
// Parameter: unsigned int delay - time to show each message
//************************************
void UI::dispalyFlashingMessage( const char * text,const char * text2,unsigned int timesToFlash/*=6*/,unsigned int delay/*=500*/ )
{
	for (int i=0; i<6; i++)//flashing message
	{
		if (i%2==0)
		{
			setConsoleColors(BACKGROUND_RED,FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY );
			displayMessage(text);
		}
		else
		{
			setConsoleColors(BACKGROUND_RED,FOREGROUND_GREEN |FOREGROUND_INTENSITY);
			displayMessage(text2);
		}
		Sleep(delay);
	}
	setConsoleColors();
}

//************************************
// Method:    displayErrorMessage - writes a text to the current error message area.
// FullName:  UI::displayErrorMessage
// Access:    public
// Returns:   void
// Qualifier: 
// Parameter: char* message - the text to display
//************************************
void UI::displayErrorMessage( char * message )
{
	clearErrorMessage();
	writeSomethingAt(message,currErrorArea);
	jumpToInputArea();
}

//************************************
// Method:    clearLine - deletes a line of text.
// FullName:  UI::clearLine
// Access:    private
// Returns:   void
// Qualifier: const
// Parameter: int lineNumber - the height of the line to delete
// Parameter: int fromCol - where to start deleting
//************************************
void UI::clearLine( int lineNumber ,int fromCol/*=2*/) const
{
	gotoxy(fromCol,lineNumber);
	for (int i=fromCol;i<79; i++)
	{
		cout<<' ';
	}
	jumpToInputArea();
}

//************************************
// Method:    clearConsole - deletes the error,input and information messages on screen.
// FullName:  UI::clearConsole
// Access:    public 
// Returns:   void
// Qualifier: const
//************************************
void UI::clearConsole() const
{
	clearErrorMessage();
	clearMassage();
	clearInputLine();
}

//************************************
// Method:    clearInputLine - deletes the input line on screen
// FullName:  UI::clearInputLine
// Access:    public 
// Returns:   void
// Qualifier: const
//************************************
void UI::clearInputLine() const
{
	clearLine(currInputArea.gety(),currInputArea.getx());
}

//************************************
// Method:    clearMassage - deletes the information message line on screen
// FullName:  UI::clearMassage
// Access:    public 
// Returns:   void
// Qualifier: const
//************************************
void UI::clearMassage() const
{
	clearLine(currMessageArea.gety(),currMessageArea.getx());
}

//************************************
// Method:    clearErrorMessage - deletes the erro message line on screen.
// FullName:  UI::clearErrorMessage
// Access:    public 
// Returns:   void
// Qualifier: const
//************************************
void UI::clearErrorMessage()const
{
	clearLine(currErrorArea.gety(),currErrorArea.getx());
}

//************************************
// Method:    printUserDetails - prints the details of the user (card,name,score) to the screen.
// FullName:  UI::printUserDetails
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const Card & myCard - the card in the user's hand.
// Parameter: int playerNumber - Number of player in players array.
//************************************
void UI::printUserDetails( const Card & myCard,int playerNumber )
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMessage("ERROR: can only draw cards at game screen");
		return;
	}
	else if (playerNumber>numberOfPlayers || playerNumber<1)
	{
		displayErrorMessage("ERROR: illegal player number");
		return;
	}
	point start=playersCardsloc[playerNumber-1];
	gotoxy(start.getx(),start.gety());
	cout<<players[playerNumber-1]->getName(); //Print player's name
	setConsoleColors(WHITE_BACK);
	myCard.printcard(start.getx(),start.gety()+1); //Print player's card
	setConsoleColors();//restore to default coloring(Green)
	gotoxy(start.getx(),start.gety()+5);
	cout<<"score:"<<players[playerNumber-1]->getScore(); //Print player's score
	jumpToInputArea();
}

//************************************
// Method:    drawLineOfCharsAt - draws a line of chars until the end of the line
// FullName:  UI::drawLineOfCharsAt
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int line - height value of line to print
// Parameter: int fromcol - width position to start
// Parameter: char ch - the char to print - default value is '#'
//************************************
void UI::drawLineOfCharsAt( int line,int fromcol,char ch )
{
	for (int i=fromcol;i<80; i++)
	{
		gotoxy(i,line);
		cout<<ch;
	}
}

//************************************
// Method:    drawColOfCharsAt - draws a column of chars until the end of the column
// FullName:  UI::drawColOfCharsAt
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int col - width value of column to print
// Parameter: int fromline - height position to start
// Parameter: char ch - the char to print - default value is '#'
//************************************
void UI::drawColOfCharsAt( int col,int fromline,char ch )
{
	for (int i=fromline;i<25; i++)
	{
		gotoxy(col,i);
		cout<<ch;
	}
}

//************************************
// Method:    getUserGameInput - Receives input from the user and returns it.
// FullName:  UI::getUserGameInput
// Access:    public 
// Returns:   char
// Qualifier:
//************************************
char UI::getUserGameInput()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMessage("ERROR: getUserGameInput called out of game screen");
		return '?';
	}
	char junk;
	char input;
	cin.get(input);
	cin.get(junk);
	jumpToInputArea();
	return input;
}

//************************************
// Method:    getNameFromScreen - Reads user name from screen up to maxNumOfChars chars,
//								  discards the last chars and returns a legit string.
// FullName:  UI::getNameFromScreen
// Access:    public 
// Returns:   char*
// Qualifier:
// Parameter: int maxNumOfChars - Max length of name
//************************************
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

//************************************
// Method:    getMainScreenUserInput - Prompts the user for game settings - name,players, etc.
// FullName:  UI::getMainScreenUserInput
// Access:    public 
// Returns:   int - Returns the number of jokers in the deck
// Qualifier:
// Parameter: int & numOfPlayers - output parameter for number of players.
// Parameter: int & shuffleDepth - output parameter for number of times to shuffle.
// Parameter: char *  & userName - output parameter the name of the user.
//************************************
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
		displayErrorMessage("illegal input please enter Number of players(2-4):");
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
		displayErrorMessage("illegal input please enter shuffle depth you want(1 or larger):");
		cin>>shuffleDepth;	
	}
	clearConsole();
	displayMessage("please enter Number of jokers you want(2-3):");
	cin >> numOfJokers;
	while(numOfJokers<2|| numOfJokers>3)
	{
		clearInputLine();
		displayErrorMessage("illegal input please enter Number of jokers you want(2-3):");
		cin >> numOfJokers;
	}
	clearConsole();
	cin.get(junk);//clear /n
	return numOfJokers;
}

//************************************
// Method:    showAllCards - Reveals the cards for all users.
// FullName:  UI::showAllCards
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void UI::showAllCards()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMessage("ERROR: showAllCards called out of game screen");
		return ;
	}
	for (int i=0; i<numberOfPlayers;i++)
	{
		printUserDetails(*players[i]->getCard(),i+1);
	}
	jumpToInputArea();
}

//************************************
// Method:    drawNewRoundOfCards - Prints the details for all users.
//									Computer controlled players' cards are "turned over".
// FullName:  UI::drawNewRoundOfCards
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void UI::drawNewRoundOfCards()
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMessage("ERROR: drawNewRoundOfCards called out of game screen");
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

//************************************
// Method:    printPlayerDecision - Prints the decision the player has made (throw/keep)
// FullName:  UI::printPlayerDecision
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int playerNumber - Number of player in players array
//************************************
void UI::printPlayerDecision(int playerNumber)
{
	if (currScreen!=GAME_SCREEN)
	{
		displayErrorMessage("ERROR: printAllDecisions called out of game screen");
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

//************************************
// Method:    setConsoleColors - Sets the colors for background and foreground in console window.
// FullName:  UI::setConsoleColors
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: WORD back - Value for background color - default is green.
// Parameter: WORD text - Value for foreground color - default is black.
//************************************
void UI::setConsoleColors(WORD back/*GREEN*/,WORD text/*BLACK*/)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,back |text);//color screen with given colors
}