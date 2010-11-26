#include "game.h"


//************************************
// Method:    Game - a Game constructor
// FullName:  Game::Game
// Access:    public 
// Returns:   an initialized game object
// Qualifier:
//************************************
Game::Game(GameTypes type/*=NORMAL*/)
{
	m_gameType=type;
	initGame();//moved to external function (to be used in new game)
}

//************************************
// Method:    initGame - initialize the game object 
// FullName:  Game::initGame
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::initGame()
{
	m_numberOfRounds=0;
	int shuffleDepth;
	UIs::UI::UI();
	UIs::UI::plotWelcomeScreen();
	char* userName=NULL;
	m_gameDeck = new Deck(UIs::UI::getMainScreenUserInput(m_numberOfplayers,shuffleDepth,userName));
	m_gameDeck->shuffle(shuffleDepth);
	addPlayer(userName,false);//add a human player
	delete []userName;//a copy is made in player- release the allocation
	char name[6]="comp";
	name[5]='\0';
	for (unsigned int i=1; i<m_numberOfplayers; i++)//define computer players
	{
		name[4]='0'+i;
		addPlayer(name); //Add a computer player
	}
	m_lastWinner=rand()%m_numberOfplayers;//decide who starts(since there is only one human player he starts at a random place and the computer order doesn't count)
}

//************************************
// Method:    ~Game - destructor for game, release all dynamic allocations
// FullName:  Game::~Game
// Access:    public 
// Returns:   
// Qualifier:
//************************************
Game::~Game()
{
	destroyGame();//moved to external function
}

//************************************
// Method:    destroyGame- release all dynamic allocations
// FullName:  Game::destroyGame
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::destroyGame()
{
	delete m_gameDeck;
	bool hasPlayers=true;
	while (hasPlayers=deletePlayer())
	{
		//No body - work done in deletePlayer()
	}
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
	UIs::UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//set current players order to reflect on ui
	while (userInput=='c')//user asks to continue playing
	{
		newRound();//play a game round
		UIs::UI::displayMessage("enter e to exit,c to continue or n for new game");
		userInput=UIs::UI::getUserGameInput();
		while(userInput!='e' && userInput!='c' && userInput!='n')//input isn't valid
		{
			UIs::UI::clearInputLine();
			UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use c,n or e only!");
			userInput=UIs::UI::getUserGameInput();
		}
		UIs::UI::clearConsole();
		if (userInput=='n')//new game
		{
			UIs::UI::plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());//summery
			destroyGame();  //Clear game settings
			initGame();		//initialize new game from user decisions
			play();			//Start anew
		}
		else if (userInput =='e')//exit
		{
			UIs::UI::plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());
			return;
		}
		UIs::UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//new order- winner starts
	}//end main while
}



//************************************
// Method:    drawCardsForAllUsers -each user takes a card by game order
// FullName:  Game::drawCardsForAllUsers
// Access:    private 
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
// Access:    private 
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

//************************************
// Method:    returnAllCardsToDeck - takes the card form each user and return it to the bottom of the deck (note that because the deck shuffles itself when all cards have been drawn the order is random)
// FullName:  Game::returnAllCardsToDeck
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::returnAllCardsToDeck()
{
	for (unsigned int i=0; i<m_numberOfplayers; i++)//each user returns his card
	{
		Card* currCard=getPlayerAt(i)->getCard();
		if (*currCard>UIs::UI::BLANK_CARD)
		{
			returnCardForUser(i);
		}
	}
}

//************************************
// Method:    returnCardForUser - takes a player card and return it to the bottom of the deck
// FullName:  Game::returnCardForUser
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int userPlace  -a number between 0 and number of players -1
//************************************
void Game::returnCardForUser(int userPlace)
{
	m_gameDeck->insertCardToEnd(getPlayerAt(userPlace)->getCard());
	getPlayerAt(userPlace)->setCard(NULL);
}

//************************************
// Method:    newRound -handles one round of game play
// FullName:  Game::newRound
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::newRound()
{
	initRound();
	getDecisions();
	closeRound();
	
}

void Game::initRound()
{
	m_numberOfRounds++;
	char userInput='0';
	drawCardsForAllUsers();//non user cards are upside down

}

void Game::getDecisions()
{
	Player* currPlayer;
	for (unsigned int i=0; i<m_numberOfplayers; i++)
	{
		currPlayer=getPlayerAt(i);
		currPlayer->makeDecision();
		UIs::UI::printPlayerDecision(i);//this way the user can see his predecessors decisions
		if (currPlayer->getDecision()==Player::THROW)
		{
			returnCardForUser(i);
			drawCardForUser(i);
		}
		Sleep(1500);
	}
}

void Game::closeRound()
{
	decideWinners();//if more then one winner picks the last one
	UIs::UI::showAllCards();
	UIs::UI::clearConsole();
	UIs::UI::dispalyFlashingMessage("the winner is ",getPlayerAt(0)->getName());
	returnAllCardsToDeck();//allocation not lost

}

void Game::addPlayer( char* userName, bool isComputer/*=true*/, int balance/*=0*/ )
{
	switch (m_gameType)
	{
		case NORMAL: m_players.push_back(new NormalPlayer(userName, isComputer));
		break;
		case GAMBLING:m_players.push_back(new Gambler(userName, isComputer,balance));
	}
	

}

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
// Method:    countPlayerJokers - counts the number of jokers currently held by players
// FullName:  Game::countPlayerJokers
// Access:    protected 
// Returns:   int
// Qualifier: const
//************************************
int Game::countPlayerJokers() const
{
	int result=0;
	Card joker = Card(Card::VJoker,Card::JOKER);
	for (unsigned int i=0; i<m_numberOfplayers; i++)
		if (*(m_players[i]->getCard())==joker)
		{
			result++;
		}
	return result;
}