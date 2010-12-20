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
	//getter for data members
	char getSuit()const {return m_suit;}
	char getValue()const {return m_valChar;}
	eSuit getSuitVal()const {return m_suitVal;}
	eVal getVal()const {return m_val;}
	bool isBlank()const{return m_val==VNONE;}
	bool operator<(const Card& otherCard) const;
	bool operator>(const Card& otherCard) const;
	bool operator==(const Card& otherCard) const;
	

private:
	eVal m_val;
	char m_valChar;
	eSuit m_suitVal;
	char m_suit;
	char TranslateValToCardChar();
	char TranslateValToSuitChar();


};

//function declaration
#endif