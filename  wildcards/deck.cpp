#include "deck.h"

//************************************
// Method:    Deck - a deck constructor
// FullName:  Deck::Deck
// Access:    public 
// Returns:   creates a deck of size NUM_OF_SUITS*NUM_OF_VALS+numOfJokers
// Qualifier: :NUM_OF_SUITS(4),NUM_OF_VALS(13) //const
// Parameter: int numOfJokers - 2 or 3
//************************************
Deck::Deck( int numOfJokers ):NUM_OF_SUITS(4),NUM_OF_VALS(13)
{
	numberOfTakes=0;
	timesToShuffle=0;
	deckSize=NUM_OF_SUITS*NUM_OF_VALS+numOfJokers;
	for (Card::eVal val=Card::Two; val!=Card::VJoker ; val=Card::incriment(val))//add values (not joker)
	{
		for (Card::eSuit suit=Card::SPADE; suit!=Card::JOKER ;suit=Card::incriment(suit))//add suits(not joker)
		{
			dqDeck.push_back(new Card (val,suit));
		}
	}
	for (numOfJokers; numOfJokers>0; numOfJokers--)//add jokers
	{
		dqDeck.push_back(new Card(Card::VJoker,Card::JOKER));
	}
}

//************************************
// Method:    ~Deck   -deck destructor
// FullName:  Deck::~Deck
// Access:    public 
// Returns:   releases all dynamic allocations
// Qualifier:
//************************************
Deck::~Deck()
{
	while (!dqDeck.empty())//delete all cards from deck
	{
		delete dqDeck.front();
		dqDeck.pop_front();
	}
}

//************************************
// Method:    shuffle - shuffle the deck depth times
// FullName:  Deck::shuffle
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int depth - the number of times to shuffle the deck
//************************************
void Deck::shuffle(int depth)
{//Fisher–Yates shuffling algorithm
	timesToShuffle=depth;
	srand((unsigned int)time(0)); //Seed random numbers generator
	int j;

	for (int i=((int)dqDeck.size())-1; i>=1; i--)
	{
		j=rand()%(i+1); //Generate a number between 0 and i
		swapCards(dqDeck[i],dqDeck[j]);
	}
}

//************************************
// Method:    swapCards - helper function for shuffle- swaps two card pointers
// FullName:  Deck::swapCards
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Card *  & card1 - a reference to a card pointer
// Parameter: Card *  & card2 -a reference to a card pointer
//************************************
void Deck::swapCards(Card * &card1, Card * &card2)
{
	Card * temp=card1;
	card1=card2;
	card2=temp;
}

//************************************
// Method:    takeCard- take a card for the top of the deck
// FullName:  Deck::takeCard
// Access:    public 
// Returns:   Card*- the card at the top of the deck
// Qualifier:
//************************************
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

//************************************
// Method:    compareCards - compares two cards 
// FullName:  Deck::compareCards
// Access:    public 
// Returns:   int - a negative number if card1<card2 a postive number if card1>card2 or zero if card1==card2
// Qualifier:
// Parameter: const Card & card1- a refrence to an initilized card
// Parameter: const Card & card2-a refrence to an initilized card
//************************************
int Deck::compareCards(const Card &card1, const Card &card2 )
{
	int val1=card1.getVal();
	int val2=card2.getVal();

	if (val1==val2)
		return card1.getSuitVal() - card2.getSuitVal();//enum order defined as instructed
	else
		return val1 - val2;//enum order defined as instructed
}

//************************************
// Method:    insertCardToStart - adds a card to the beginning of the deck
// FullName:  Deck::insertCardToStart
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Card * card - a  non null pointer to a card(a valid card)
//************************************
void Deck::insertCardToStart(Card* card)
{
	dqDeck.push_front(card);
}

//************************************
// Method:    insertCardToEnd - adds a card to the end of the deck
// FullName:  Deck::insertCardToEnd
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Card * card - a non null pointer to a card \
//************************************
void Deck::insertCardToEnd(Card* card )
{
	dqDeck.push_back(card);
}