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
	m_numberOfTakes=0;
	m_timesToShuffle=0;
	m_deckSize=NUM_OF_SUITS*NUM_OF_VALS+numOfJokers;
	for (Card::eVal val=Card::Two; val!=Card::VJoker ; val=Card::incriment(val))//add values (not joker)
	{
		for (Card::eSuit suit=Card::SPADE; suit!=Card::JOKER ;suit=Card::incriment(suit))//add suits(not joker)
		{
			m_dqDeck.push_back(new Card (val,suit));
		}
	}
	for (numOfJokers; numOfJokers>0; numOfJokers--)//add jokers
	{
		m_dqDeck.push_back(new Card(Card::VJoker,Card::JOKER));
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
	while (!m_dqDeck.empty())//delete all cards from deck
	{
		delete m_dqDeck.front();
		m_dqDeck.pop_front();
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
	m_timesToShuffle=depth;
	srand((unsigned int)time(0)); //Seed random numbers generator
	int j;

	for (int i=((int)m_dqDeck.size())-1; i>=1; i--)
	{
		j=rand()%(i+1); //Generate a number between 0 and i
		swapCards(m_dqDeck[i],m_dqDeck[j]);
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
	if (!m_dqDeck.empty())
	{
		if (m_numberOfTakes!=0 && ShouldShuffle())//first shuffle is done by user
		{
			shuffle(m_timesToShuffle);
		}
		pCard=m_dqDeck.front();
		m_dqDeck.pop_front();//Remove card so that no other user can get it.
		m_numberOfTakes++;
	}
	return pCard;//Someone will hold the result so that no allocated memory gets "lost"
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
	m_dqDeck.push_front(card);
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
	m_dqDeck.push_back(card);
}