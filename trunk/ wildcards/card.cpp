//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise: 2 Question:N/A
//File name: card.cpp
#include "card.h"


//************************************
// Method:    Card -card constructor
// FullName:  Card::Card
// Access:    public 
// Returns:   
// Qualifier:
// Parameter: eVal cardVal-the card value
// Parameter: eSuit cardSuit- the card suit
//************************************
Card::Card(eVal cardVal, eSuit cardSuit)
{
	val=cardVal;
	suitVal=cardSuit;
	valChar=TranslateValToCardChar();
	suit=TranslateValToSuitChar();
}

//************************************
// Method:    TranslateValToCardChar- private method to translate card value name to its char
// FullName:  Card::TranslateValToCardChar
// Access:    private 
// Returns:   char - the char representing the value of the card
// Qualifier:
//************************************
char Card::TranslateValToCardChar()
{ 
	switch (val)
	{
		case VNONE : return '?';
		case Two: return '2';
		case Three : return '3';
		case Four: return '4';
		case Five : return '5';
		case Six: return '6';
		case Seven : return '7';
		case Eight: return '8';
		case Nine : return '9';
		case Ten: return 'T';
		case Jack : return 'J';
		case Queen: return 'Q';
		case King : return 'K';
		case Ace: return 'A';
		case VJoker : return '$';
	}
	return NONE;//not to be reached
}

//************************************
// Method:    TranslateValToSuitChar - private method to translate card suit name to its char
// FullName:  Card::TranslateValToSuitChar
// Access:    private 
// Returns:   char-the char representing the suit of the card
// Qualifier:
//************************************
char Card::TranslateValToSuitChar()
{
	switch (suitVal)
	{
	case NONE : return '?';
	case SPADE: return (char)(6);//draws spade
	case CLOVER : return (char)(5);//as above
	case DIEMOND: return (char)(4);//as above
	case HART : return (char)(3);//as above
	case JOKER: return 'J';
	}
	return NONE;//not to be reached
}

//************************************
// Method:    incriment - returns the next value(it is circular)
// FullName:  Card::incriment
// Access:    public 
// Returns:   Card::eVal
// Qualifier:
// Parameter: eVal currValue- a valid eVal as defined in the enum eVal
//************************************
Card::eVal Card::incriment( eVal currValue)
{
	switch (currValue)
	{
	case VNONE : return VNONE;
	case Two   : return Three;
	case Three : return Four;
	case Four  : return Five;
	case Five  : return Six;
	case Six   : return Seven;
	case Seven : return Eight;
	case Eight : return Nine;
	case Nine  : return Ten;
	case Ten   : return Jack;
	case Jack  : return Queen;
	case Queen : return King;
	case King  : return Ace;
	case Ace   : return VJoker;
	case VJoker: return VNONE;
	}
	return VNONE; //not to be reached


}
//************************************
// Method:    incriment - returns the next suit(it is circular)
// FullName:  Card::incriment
// Access:    public 
// Returns:   Card::eSuit
// Qualifier:
// Parameter: eSuit currValue- a valid eSuit as defined in the enum eSuit
//************************************
Card::eSuit Card::incriment( eSuit currSuit)
{
	switch (currSuit)
	{
	case NONE : return NONE;
	case SPADE: return CLOVER;
	case CLOVER : return DIEMOND;
	case DIEMOND: return HART;
	case HART : return JOKER;
	case JOKER: return NONE;
	}
	return NONE; //not to be reached

}

//************************************
// Method:    gotoxy-helper function to print card. moves cursor to the given location
// FullName:  Card::gotoxy
// Access:    private 
// Returns:   void
// Qualifier: const
// Parameter: int x -an non negative x coordinate within screen bounds
// Parameter: int y -an non negative y coordinate within screen bounds
//************************************
void Card::gotoxy( int x, int y) const
{//as given at exercises
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);

}

//************************************
// Method:    printcard- prints a white card at the given location
// FullName:  Card::printcard
// Access:    public 
// Returns:   void
// Qualifier: const
// Parameter: int xLoc -an non negative x coordinate within screen bounds
// Parameter: int yLoc -an non negative y coordinate within screen bounds
//************************************
void Card::printcard( int xLoc,int yLoc ) const
{
	gotoxy(xLoc,yLoc);
	cout << "+---+" << endl;
	gotoxy(xLoc,yLoc+1);
	cout << "|" << valChar << "  |"<<endl;
	gotoxy(xLoc,yLoc+2);
	cout << "|   |" << endl;
	gotoxy(xLoc,yLoc+3);
	cout << "|__" << suit << "|" << endl;
}