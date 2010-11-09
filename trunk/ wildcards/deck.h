//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise:  Question:
//File name: deck.h
#ifndef ___DECK___H____
#define ___DECK___H____
//includes
#include <iostream> 
using namespace std;
#include "card.h"
#include <cstdlib>
#include <ctime>
#include <deque>
//defines

//consts

//classes
class Deck
{
private:
	int numberOfTakes;//to be used for shuffling
	int timesToShuffle;
	int deckSize;
	deque<Card*> dqDeck;
	const int NUM_OF_SUITS;
	const int NUM_OF_VALS;
	bool ShouldShuffle(){if(numberOfTakes%dqDeck.size()==0) return true; else return false;}//if all cards have been taken

public:
	Deck(int numOfJokers);
	~Deck();
	int getSize(){return deckSize;}
	void shuffle(int depth);
	void swapCards(Card * &card1, Card * &card2);
	Card* takeCard();
	int compareCards(const Card &card1,const Card &card2 );
	void insertCardToStart(Card* card);
	void insertCardToEnd(Card* card);
};
//function declaration
#endif