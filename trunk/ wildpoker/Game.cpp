#include "Game.h"
Deck m_gameDeck=Deck(0);//only one game at a time therefor only one deck
Game::Game(void)
{
	initGame();
}

Game::~Game(void)
{
	destroyGame();
}
//************************************
// Method:    play - main function for game handles entire game play until user exits
// FullName:  Game::play
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void Game::play()
{
	char userInput='c';
	UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//set current players order to reflect on ui
	while (!m_endGame && userInput=='c')//user asks to continue playing and game isnt over
	{
		newRound();//play a game round
		if (m_endGame)
		{
			UI::displayMessage("Game over!! enter e to exit or n for new game");
		}
		else
		{
			UI::displayMessage("enter e to exit,c to continue or n for new game");
		}

		userInput=UI::getUserGameInput();
		while((userInput=='c'&& m_endGame )||(userInput!='e' && userInput!='c' && userInput!='n'))//input isn't valid
		{
			UI::clearInputLine();
			if (m_endGame)
			{
				UI::displayErrorMessage("ERROR:the input you entered is invalid: use n or e only!");
			}
			else
			{
				UI::displayErrorMessage("ERROR:the input you entered is invalid: use c n or e only!");
			}
			userInput=UI::getUserGameInput();
		}
		UI::clearConsole();
		if (userInput=='n')//new game
		{
			UI::plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());//summery
			destroyGame();  //Clear game settings
			initGame();		//initialize new game from user decisions
			play();			//Start anew
		}
		else if (userInput =='e')//exit
		{
			UI::plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());
			m_endGame=true;//ask to end game
		}
		else // must be c
		{
			UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//new order- winner starts
		}
	}//end main while
}
void Game::newRound()
{
	initRound();
	getDecisions();
	closeRound();	
}

//************************************
// Method:    closeRound - Used at end of round to show all cards, name the winner, and return them to the deck.
// FullName:  Game::closeRound
// Access:    virtual protected 
// Returns:   void
// Qualifier:
//************************************
void Game::closeRound()
{
	UI::showAllCards();
	UI::clearConsole();
	UI::dispalyFlashingMessage("the winner is ",getPlayerAt(0)->getName());
	returnAllCardsToDeck();//allocation not lost
}

void Game::addPlayer( char* userName, int score/*=0*/,bool isHumen/*=false*/)
{
	//
}


//************************************
// Method:    deletePlayer - Removes a player from the game and frees memory allocated.
// FullName:  Game::deletePlayer
// Access:    protected 
// Returns:   bool - returns false IFF no players left in the game.
// Qualifier:
//************************************
bool Game::deletePlayer()
{
	Player * curr;
	if (m_players.empty())
	{
		return false;
	}
	else
	{
		curr=m_players.front();
		m_players.pop_front();
		delete curr;
		return true;
	}
}


//************************************
// Method:    returnAllCardsToDeck - takes the card form each user and return it to the bottom of the deck (note that because the deck shuffles itself when all cards have been drawn the order is random)
// FullName:  Game::returnAllCardsToDeck
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void Game::returnAllCardsToDeck()
{

	for (unsigned int i=0; i<m_numberOfplayers; i++)//each user returns his cards
	{
		Card* currCard=getPlayerAt(i)->getCard();
		if (!currCard->isBlank())
		{
			returnCardForUser(i);
		}
	}
}

//************************************
// Method:    returnCardForUser - takes a player cards and return them to the bottom of the deck
// FullName:  Game::returnCardForUser
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int userPlace  -a number between 0 and number of players -1
//************************************
void Game::returnCardForUser(int userPlace)
{
	for (int j=1;j<=NUM_OF_CARDS_IN_HAND; j++)
	{
		m_gameDeck->insertCardToEnd(getPlayerAt(userPlace)->getCard(j));
		getPlayerAt(userPlace)->setCard(NULL,j);
	}	
}

//************************************
// Method:    getPlayerAt - returns a pointer to a player at position "place"
// FullName:  Game::getPlayerAt
// Access:    protected 
// Returns:   Player *
// Qualifier:
// Parameter: unsigned int place - position of the player
//************************************
Player * Game::getPlayerAt( unsigned int place )
{
	if (place>(m_players.size()-1))//no such place
	{
		return NULL;
	}
	else
	{
		return m_players[getUserPlace(place)];;
	}
}
//************************************
// Method:    givePointsToPlayer - adds to the player's score/money according to game type.
// FullName:  Game::givePointsToPlayer
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int numOfPoints - Integer denominating how many to add.
// Parameter: Player * p - pointer to the player.
//************************************
void Game::givePointsToPlayer( int numOfPoints,Player * p )
{
	
	p->addToScore(numOfPoints);
}
//************************************
// Method:    destroyGame- release all dynamic allocations
// FullName:  Game::destroyGame
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void Game::destroyGame()
{
	bool hasPlayers=true;
	while (hasPlayers=deletePlayer())
	{
		//No body - work done in deletePlayer()
	}
}
//************************************
// Method:    drawCardsForAllUsers -each user takes a card by game order
// FullName:  Game::drawCardsForAllUsers
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void Game::drawCardsForAllUsers()
{
	for (unsigned int i=0; i<m_numberOfplayers; i++)//each user takes a card
	{
		drawCardForUser(i);//uses game order
	}
}

//************************************
// Method:    drawCardForUser -draw a card for the userPlace player in the current round
// FullName:  Game::drawCardForUser
// Access:    protected
// Returns:   void
// Qualifier:
// Parameter: int userPlace -a number between 0 and number of players -1
//************************************
void Game::drawCardForUser(int userPlace)
{
	Player* currPlayer=getPlayerAt(userPlace);
	currPlayer->setCard(m_gameDeck->takeCard());;
	if (currPlayer->isHumanPlayer())
	{
		UIs::UI::printUserDetails(userPlace+1);//print the card if its the player
	}
}