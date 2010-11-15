#include "game.h"

//************************************
// Method:    Game - a Game constructor
// FullName:  Game::Game
// Access:    public 
// Returns:   an initialized game object
// Qualifier:
//************************************
Game::Game()
{
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
	m_ui=new UI();
	m_ui->plotWelcomeScreen();
	char* userName=NULL;
	m_gameDeck = new Deck(m_ui->getMainScreenUserInput(m_numberOfplayers,shuffleDepth,userName));
	m_gameDeck->shuffle(shuffleDepth);
	m_players.push_back(new Player(userName,false));//add a human player
	delete []userName;//a copy is made in player- release the allocation
	char name[6]="comp";
	name[5]='\0';
	for (int i=1; i<m_numberOfplayers; i++)//define computer players
	{
		name[4]='0'+i;
		m_players.push_back(new Player(name,true));
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
	delete m_ui;
	delete m_gameDeck;
	while (!m_players.empty())
	{//delete all players
		delete m_players.front();
		m_players.pop_front();
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
	m_ui->setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//set current players order to reflect on ui
	while (userInput=='c')//user asks to continue playing
	{
		newRound();//play a game round
		m_ui->displayMessage("enter e to exit,c to continue or n for new game");
		userInput=m_ui->getUserGameInput();
		while(userInput!='e' && userInput!='c' && userInput!='n')//input isn't valid
		{
			m_ui->clearInputLine();
			m_ui->displayErrorMessage("ERROR:the input you entered is invalid: use c,n or e only!");
			userInput=m_ui->getUserGameInput();
		}
		m_ui->clearConsole();
		if (userInput=='n')//new game
		{
			m_ui->plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());//summery
			destroyGame();  //Clear game settings
			initGame();		//initialize new game from user decisions
			play();			//Start anew
		}
		else if (userInput =='e')//exit
		{
			m_ui->plotGoodbyeScreen(m_numberOfRounds,returnNameOfWinningPlayer());
			return;
		}
		m_ui->setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));//new order- winner starts
	}//end main while
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
	m_numberOfRounds++;
	Player* currPlayer;
	char userInput='0';
	drawCardsForAllUsers();//non user cards are upside down
	m_ui->plotGameScreen(m_numberOfplayers);
	for (unsigned int i=0; i<m_players.size(); i++)
	{
		currPlayer=getPlayerAt(i);
		currPlayer->makeDecision(m_ui);
		m_ui->printPlayerDecision(i);//this way the user can see his predecessors decisions
		if (currPlayer->getDecision()==Player::THROW)
		{
			returnCardForUser(i);
			drawCardForUser(i);
		}
		Sleep(1500);
	}
	decideWinners();//if more then one winner picks the last one
	m_ui->showAllCards();
	m_ui->clearConsole();
	m_ui->dispalyFlashingMessage("the winner is ",getPlayerAt(0)->getName());

	returnAllCardsToDeck();//allocation not lost
}

//************************************
// Method:    getPlayerAt - returns a pointer the place player in the current game order or null if no such place
// FullName:  Game::getPlayerAt
// Access:    private 
// Returns:   Player *-a pointer the place player in the current game order NULL if no such place
// Qualifier:
// Parameter: unsigned int place- a number from 0 to the number of players -1
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
// Method:    drawCardsForAllUsers -each user takes a card by game order
// FullName:  Game::drawCardsForAllUsers
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::drawCardsForAllUsers()
{

	for (unsigned int i=0; i<m_players.size(); i++)//each user takes a card
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
		m_ui->printUserDetails(userPlace+1);//print the card if its the player
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
	for (unsigned int i=0; i<m_players.size(); i++)//each user returns his card
	{
		returnCardForUser(i);
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
// Method:    decideWinners - decide who is the winner of the current round and give him a point(if more then one joker last one is the winner and all jokers get a point) 
// FullName:  Game::decideWinners
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::decideWinners()
{
	Player * currWinner;
	Player * next;
	int numOfJokers=0;
	for (unsigned int i=0; i<m_players.size(); i++)//more then one winner
	{
		next=m_players[i];
		if (next->getCard()->getSuitVal()==Card::JOKER)//give a point to all jokers
		{
			numOfJokers++;
			next->addToScore(1);
			m_lastWinner=i;
		} 
	}//last one is considered winner of the round
	if (numOfJokers==0)//one winner
	{
		currWinner=m_players[0];
		m_lastWinner=0;
		for (unsigned int i=1; i<m_players.size(); i++)
		{
			next=m_players[i];
			if (m_gameDeck->compareCards(*(currWinner->getCard()) , *(next->getCard()))<0)
			{
				currWinner=next; //otherwise do nothing
				m_lastWinner=i;
			}
		}
		currWinner->addToScore(1);
	}
}

//************************************
// Method:    returnNameOfWinningPlayer - returns the name of the player with the highest score(or the last one if more then one)
// FullName:  Game::returnNameOfWinningPlayer
// Access:    private 
// Returns:   const char * - the name of the player with the highest score
// Qualifier:
//************************************
const char * Game::returnNameOfWinningPlayer()
{
	Player * currPlayer=m_players[0];
	Player * next;
	for(int i=1;i<m_numberOfplayers; i++)
	{
		next=m_players[i];
		if(next->getScore()>currPlayer->getScore())
		{
			currPlayer=next;
		}
	}
	return currPlayer->getName();
}