#include "game.h"

//************************************
// Method:    Game - a Game constructor
// FullName:  Game::Game
// Access:    public 
// Returns:   an initialized game object
// Qualifier:
// Parameter: GameTypes type
//************************************
Game::Game(GameTypes type/*=NORMAL*/)
{
	m_gameType=type;
	initGame();//moved to external function (to be used in new game)
}

//************************************
// Method:    initGame - initialize the game object 
// FullName:  Game::initGame
// Access:    virtual protected 
// Returns:   void
// Qualifier:
//************************************
void Game::initGame()
{
	m_endGame=false;
	m_numberOfRounds=0;
	int shuffleDepth;
	UIs::GamblingUI::GamblingUI();
	UIs::UI::plotWelcomeScreen();
	char* userName=NULL;
	int numOfJokers=UIs::UI::getMainScreenUserInput(m_numberOfplayers,shuffleDepth,userName);
	m_gameDeck = new Deck(numOfJokers);
	m_gameDeck->shuffle(shuffleDepth);
	addPlayer(userName,numOfJokers,false);//add a human player
	delete []userName;//a copy is made in player- release the allocation
	char name[6]="comp";
	name[5]='\0';
	for (unsigned int i=1; i<m_numberOfplayers; i++)//define computer players
	{
		name[4]='0'+i;
		addPlayer(name,numOfJokers); //Add a computer player
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
// Access:    protected 
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
	while (!m_endGame && userInput=='c')//user asks to continue playing and game isnt over
	{
		newRound();//play a game round
		if (m_endGame)
		{
			UIs::UI::displayMessage("Game over!! enter e to exit or n for new game");
		}
		else
		{
			UIs::UI::displayMessage("enter e to exit,c to continue or n for new game");
		}
		
		userInput=UIs::UI::getUserGameInput();
		while((userInput=='c'&& m_endGame )||(userInput!='e' && userInput!='c' && userInput!='n'))//input isn't valid
		{
			UIs::UI::clearInputLine();
			if (m_endGame)
			{
				UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use n or e only!");
			}
			else
			{
				UIs::UI::displayErrorMessage("ERROR:the input you entered is invalid: use c n or e only!");
			}
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
			m_endGame=true;//ask to end game
		}
		else // must be c
		{
			UIs::UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//new order- winner starts
		}
	}//end main while
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

//************************************
// Method:    returnAllCardsToDeck - takes the card form each user and return it to the bottom of the deck (note that because the deck shuffles itself when all cards have been drawn the order is random)
// FullName:  Game::returnAllCardsToDeck
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void Game::returnAllCardsToDeck()
{
	
	for (unsigned int i=0; i<m_numberOfplayers; i++)//each user returns his card
	{
		getPlayerAt(i)->updateUserAboutRound(m_numOfThrows,m_numberOfplayers,
			(getPlayerAt((i+1)%m_numberOfplayers)->getCard()),
			(getPlayerAt((i+2)%m_numberOfplayers)->getCard()),
			(getPlayerAt((i+3)%m_numberOfplayers)->getCard()));
	}
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
// Access:    protected 
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
// Access:    virtual protected
// Returns:   void
// Qualifier:
//************************************
void Game::newRound()
{
	initRound();
	getDecisions();
	closeRound();	
}

//************************************
// Method:    initRound - Used to setup a new round.
// FullName:  Game::initRound
// Access:    virtual protected 
// Returns:   void
// Qualifier:
//************************************
void Game::initRound()
{
	m_numOfThrows=0;
	m_numberOfRounds++;
	char userInput='0';
	drawCardsForAllUsers();//non user cards are upside down
}

//************************************
// Method:    getDecisions - Gets the throw/keep decisions from each player.
// FullName:  Game::getDecisions
// Access:    protected 
// Returns:   void
// Qualifier:
//************************************
void Game::getDecisions()
{
	Player* currPlayer;
	for (unsigned int i=0; i<m_numberOfplayers; i++)
	{
		currPlayer=getPlayerAt(i);
		if (*(currPlayer->getCard())>Card(Card::VNONE,Card::NONE))//has a card
		{
			currPlayer->makeDecision();
			UIs::UI::printPlayerDecision(i);//this way the user can see his predecessors decisions
			if (currPlayer->getDecision()==Player::THROW)
			{
				m_numOfThrows++;
				returnCardForUser(i);
				drawCardForUser(i);
			}
			Sleep(1500);
		}
	}
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
	UIs::UI::showAllCards();
	UIs::UI::clearConsole();
	UIs::UI::dispalyFlashingMessage("the winner is ",getPlayerAt(0)->getName());
	returnAllCardsToDeck();//allocation not lost
}

//************************************
// Method:    addPlayer - Adds a player to the game, chooses a player by game type.
// FullName:  Game::addPlayer
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: char * userName - name of the user.
// Parameter: bool isComputer - boolean to signify human/computer.
// Parameter: int balance - The amount of money the player has.
// Parameter: int numOfJokers - the number of jokers
//************************************
void Game::addPlayer( char* userName,int numOfJokers, bool isComputer/*=true*/, int balance/*=0*/ )
{
	switch (m_gameType)
	{
		case NORMAL: m_players.push_back(new NormalPlayer(userName, isComputer,numOfJokers));
		break;
		case GAMBLING:m_players.push_back(new Gambler(userName, isComputer,balance,numOfJokers));
	}
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
	Gambler * pG=(Gambler *)p;
	NormalPlayer * pN=(NormalPlayer *)p;
	switch(m_gameType)
	{
		case NORMAL: pN->addToScore(numOfPoints);
			break;
		case GAMBLING: pG->addToBalance(numOfPoints);
			break;
	}
}

//************************************
// Method:    decideWinners - Adds points to the winner and updates data member m_lastWinner
							//Works by differentiating between a situation where there is only one winner
							//or multiple winners (When 2 or more players have jokers).
							//NOTE: as an implementation decision - we chose to round up when splitting the pot.
// FullName:  Game::decideWinners
// Access:    protected 
// Returns:   void
// Qualifier:
// Parameter: int pot
//************************************
void Game::decideWinners(int pot/*=1*/)
{
	Player * currWinner;
	Player * next;
	int numOfJokers=countPlayerJokers();
	if (numOfJokers>1)//more then one winner
		for (unsigned int i=0; i<m_players.size(); i++)
		{
			next=m_players[i];
			if (*(next->getCard())==Card(Card::VJoker,Card::JOKER))//give a point to all jokers
			{
				givePointsToPlayer(((pot/numOfJokers)+1),next);
				m_lastWinner=i;
			} 
		}//last one is considered winner of the round
	else//one winner
	{
		currWinner=m_players[0];
		m_lastWinner=0;
		for (unsigned int i=1; i<m_players.size(); i++)
		{
			next=m_players[i];
			if (*(currWinner->getCard())<*(next->getCard()))
			{
				currWinner=next; //otherwise do nothing
				m_lastWinner=i;
			}
		}
		givePointsToPlayer(pot,currWinner);
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