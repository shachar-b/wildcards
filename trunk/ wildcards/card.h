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
	enum eSuit//suits in the order defined in the exercise
	{
		NONE,
		SPADE,
		CLOVER,
		DIEMOND,
		HART,
		JOKER
	};
	enum eVal //values in the order defined in the exercise
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
	~Card(){}//nothing to do here
	void printcard(int xLoc,int yLoc)const;
	//getters for data members:
	char getSuit()const {return suit;}
	char getValue()const {return valChar;}
	eSuit getSuitVal()const {return suitVal;}
	eVal getVal()const {return val;}
	

private:
	eVal val;
	char valChar;
	eSuit suitVal;
	char suit;
	void gotoxy( int x, int y) const;
	char TranslateValToCardChar();
	char TranslateValToSuitChar();
};
#endif