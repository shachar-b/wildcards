



//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise: 2 Question:N/A
//File name: card.cpp
#include "card.h"


Card::Card(eVal cardVal, eSuit cardSuit)
{
	val=cardVal;
	suitVal=cardSuit;
	valChar=TranslateValToCardChar();
	suit=TranslateValToSuitChar();
}

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

char Card::TranslateValToSuitChar()
{
	switch (suitVal)
	{
	case NONE : return '?';
	case SPADE: return 'S';
	case CLOVER : return 'C';
	case DIEMOND: return 'D';
	case HART : return 'H';
	case JOKER: return '$';
	}
	return NONE;//not to be reached
}

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
void Card::gotoxy( int x, int y) const
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);

}

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

void Card::printcard( int xLoc,int yLoc ) const
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,
		BACKGROUND_RED | 
		BACKGROUND_GREEN | 
		BACKGROUND_BLUE |
		BACKGROUND_INTENSITY);

	gotoxy(xLoc,yLoc);
	cout << "+---+" << endl;
	gotoxy(xLoc,yLoc+1);
	cout << "|" << valChar << "  |"<<endl;
	gotoxy(xLoc,yLoc+2);
	cout << "|   |" << endl;
	gotoxy(xLoc,yLoc+3);
	cout << "|__" << suit << "|" << endl;
	SetConsoleTextAttribute(hOut,
		BACKGROUND_GREEN );
}