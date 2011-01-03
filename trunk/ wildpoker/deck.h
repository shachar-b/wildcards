#ifndef ___DECK___H____
#define ___DECK___H____
//includes
#include <iostream> 
using namespace std;
#include "card.h"
#include <cstdlib>
#include <ctime>
#include <deque>

//classes
class Deck
{
private:
	int m_numberOfTakes;//to be used for shuffling decision
	int m_timesToShuffle;
	int m_deckSize;
	deque<Card*> m_dqDeck;
	const int NUM_OF_SUITS;
	const int NUM_OF_VALS;
	bool ShouldShuffle(){if(m_numberOfTakes%m_dqDeck.size()==0) return true; else return false;}//if all cards have been taken-shuffle

public:
	Deck(int numOfJokers);
	~Deck();
	int getSize(){return m_deckSize;}
	void shuffle(int depth);
	void swapCards(Card * &card1, Card * &card2);
	Card* takeCard();
	void insertCardToStart(Card* card);
	void insertCardToEnd(Card* card);
};
#endif