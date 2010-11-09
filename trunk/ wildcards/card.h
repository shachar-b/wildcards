



//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise: 2 Question:N/A
//File name: card.h
#ifndef ___CARD___H____
#define ___CARD___H____
//includes
#include <iostream> 
using namespace std;
#include <Windows.h>

//defines

//classes

class Card
{
public:
	enum eSuit
	{
		NONE,
		SPADE,
		CLOVER,
		DIEMOND,
		HART,
		JOKER
	};//add later
	enum eVal
	{
		VNONE,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace,
		VJoker
	};
	static eVal incriment(eVal currValue);
	static eSuit incriment(eSuit currSuit) ;
	Card(eVal val, eSuit cardSuit);
	~Card(){}
	char getSuit()const {return suit;}
	char getValue()const {return valChar;}
	eSuit getSuitVal()const {return suitVal;}
	eVal getVal()const {return val;}
	void printcard(int xLoc,int yLoc)const;
	
	

private:
	eVal val;
	char valChar;
	eSuit suitVal;
	char suit;
	void gotoxy( int x, int y) const;
	char TranslateValToCardChar();
	char TranslateValToSuitChar();


};

//function declaration
#endif