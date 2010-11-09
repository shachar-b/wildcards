//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 28/10/10
//Exercise:  Question:
//File name: deck.cpp
#include "deck.h"

Deck::Deck( int numOfJokers ):NUM_OF_SUITS(4),NUM_OF_VALS(13)
{
	numberOfTakes=0;
	deckSize=NUM_OF_SUITS*NUM_OF_VALS+numOfJokers;
	for (Card::eVal val=Card::Two; val!=Card::VJoker ; val=Card::incriment(val))
	{
		for (Card::eSuit suit=Card::SPADE; suit!=Card::JOKER ;suit=Card::incriment(suit))
		{
			dqDeck.push_back(new Card (val,suit));
		}
	}
	for (numOfJokers; numOfJokers>0; numOfJokers--)
	{
		dqDeck.push_back(new Card(Card::VJoker,Card::JOKER));
	}
}

Deck::~Deck()
{
	while (!dqDeck.empty())
	{
		delete dqDeck.front();
		dqDeck.pop_front();
	}
}

void Deck::shuffle(int depth)
{
	timesToShuffle=depth;
	srand((unsigned int)time(0)); //Seed random numbers generator
	int j;

	for (int i=((int)dqDeck.size())-1; i>=1; i--)
	{
		j=rand()%(i+1); //Generate a number between 0 and i
		swapCards(dqDeck[i],dqDeck[j]);
	}
}

void Deck::swapCards(Card * &card1, Card * &card2)
{
	Card * temp=card1;
	card1=card2;
	card2=temp;
}

Card* Deck::takeCard()
{
	Card* pCard=NULL;
	if (!dqDeck.empty())
	{
		if (numberOfTakes!=0 && ShouldShuffle())//first shuffle is done by user
		{
			shuffle(timesToShuffle);
		}
		pCard=dqDeck.front();
		dqDeck.pop_front();//Remove card so that no other user can get it.
		numberOfTakes++;
	}
	return pCard;//Someone will hold the result so that no allocated memory gets "lost"
}

//Function compareCards returns a positive integer if the current card
//is greater than the compared card, a negative if else or a 0
//if the cards are of equal value (can only happen with jokers)
int Deck::compareCards(const Card &card1, const Card &card2 )
{
	int val1=card1.getVal();
	int val2=card2.getVal();

	if (val1==val2)
		return card1.getSuitVal() - card2.getSuitVal();
	else
		return val1 - val2;
}

void Deck::insertCardToStart(Card* card)
{
	dqDeck.push_front(card);
}

void Deck::insertCardToEnd(Card* card )
{
	dqDeck.push_back(card);
}

//Function fetchWinner
//will send the cards pointed to by two players
//and return the winning player.
//remember : if card1 wins over card2 - result of compare will be >0
//			 if card1 loses to card2 - result of compare will be <0
//			 else - result will be 0 - only jokers