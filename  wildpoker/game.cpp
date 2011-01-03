#include "game.h"
Deck Game::m_gameDeck=Deck(0);//only one game at a time therefore only one deck, and no jokers in this game
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
	while (!m_endGame && userInput=='c')//user asks to continue playing and game isnt over
	{
		//set current players order to reflect on UI
		UIs::UI::setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));
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
// Method:    newRound - play one round
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
	decideWinners();
	string announcement1="the winner is "+string(getPlayerAt(0)->getName());
	string announcement2="With "+Hand::getStringOfWinningRule(m_winningRule);
	UIs::UI::dispalyFlashingMessage(announcement1,announcement2);
	returnAllCardsToDeck();//allocation not lost
}

//************************************
// Method:    addPlayer -add a player to the game
// FullName:  Game::addPlayer
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: char * userName - non null c string
// Parameter: bool isHumen- true for human false for computer(default set to false)
// Parameter: int score- initial score(default set to zero)
//************************************
void Game::addPlayer( char* userName, bool isHumen/*=false*/,int score/*=0*/)
{
	Player * p=new Player(userName,!isHumen);
	m_players.push_back(p);
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
	for (int j=0; j<Hand::NUM_OF_CARDS_IN_COMUNITY; j++)
	{
		m_gameDeck.insertCardToEnd(const_cast<Card *>(m_comunityCards[j])); //Explicit "de-constization"
		m_comunityCards[j]=NULL;
	}

	for (unsigned int i=0; i<m_numberOfplayers; i++)//each user returns his cards
	{
		for (int j=1; j<=Hand::NUM_OF_CARDS_IN_HAND;j++)
		{
			if (getPlayerAt(i)->getCard(j)!=NULL && !(getPlayerAt(i)->getCard(j)->isBlank()))
				returnCardForUser(i,j);
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
// Parameter: int cardNumber- a card number from 1 to 3
//************************************
void Game::returnCardForUser(int userPlace, int cardNumber)
{
	m_gameDeck.insertCardToEnd(const_cast<Card *>(getPlayerAt(userPlace)->getCard(cardNumber))); //Explicit "de-constization"
	getPlayerAt(userPlace)->setCard(NULL,cardNumber);
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
		for(unsigned int j=1;j<=Hand::NUM_OF_CARDS_IN_HAND; j++)
			drawCardForUser(i,j);//uses game order
	}
}

//************************************
// Method:    drawCardForUser-draw a card for the userPlace player in the current round place it at slot cardNumber and show cards if it a human and !hidecard
// FullName:  Game::drawCardForUser
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int userPlace -a number between 0 and number of players -1
// Parameter: int cardNumber- the number of card
// Parameter: bool hideCard- only valid for humen players- false(default) to show true to hide
//************************************
void Game::drawCardForUser(int userPlace, int cardNumber,bool hideCard/*=false*/)
{
	Player* currPlayer=getPlayerAt(userPlace);
	currPlayer->setCard(m_gameDeck.takeCard(),cardNumber);;
	if (!hideCard && currPlayer->isHumanPlayer())
	{
		UIs::UI::printUserDetails(userPlace+1);//print the card if its the player's
	}
}

//************************************
// Method:    drawComunityCards - draw cards for the community
// FullName:  Game::drawComunityCards
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::drawComunityCards()
{
	for (int j=0; j<Hand::NUM_OF_CARDS_IN_COMUNITY; j++)
	{
		m_comunityCards[j]=m_gameDeck.takeCard();
		for (unsigned int i=0;i<m_numberOfplayers;i++)
		{
			getPlayerAt(i)->setComunityCard(m_comunityCards[j],j+1);
		}
		UIs::UI::updateComunityCards(m_comunityCards[j],j+1);
	}
}

//************************************
// Method:    initGame -initialize a new game
// FullName:  Game::initGame
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::initGame()
{
	m_endGame=false;
	m_numberOfRounds=0;
	int shuffleDepth;
	UIs::UI::plotWelcomeScreen();
	char* userName=NULL;
	int numOfJokers=UIs::UI::getMainScreenUserInput(m_numberOfplayers,shuffleDepth,userName);
	m_gameDeck.shuffle(shuffleDepth);
	addPlayer(userName,true);//add a human player
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
// Method:    initRound -initialize a new round
// FullName:  Game::initRound
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::initRound()
{
	m_numberOfRounds++;
	UIs::UI::plotGameScreen(m_numberOfplayers);
	drawComunityCards();
	char userInput='0';
	drawCardsForAllUsers();//non user cards are face down
}

//************************************
// Method:    getDecisions - get the players decisions
// FullName:  Game::getDecisions
// Access:    private 
// Returns:   void
// Qualifier:
//************************************
void Game::getDecisions()
{
	Player* currPlayer;
	for (unsigned int i=0; i<m_numberOfplayers; i++)
	{
		currPlayer=getPlayerAt(i);
		for (int j=1; j<=Hand::NUM_OF_CARDS_IN_HAND; j++)
		{
			currPlayer->makeDecision(j);
			UIs::UI::printPlayerDecision(i,j);//this way the user can see his predecessors decisions
			if (currPlayer->getDecision(j)==Player::THROW)
			{
				returnCardForUser(i,j);
				drawCardForUser(i,j,true);
			}
			Sleep(100);
		}
		if(currPlayer->isHumanPlayer())
		{
			UIs::UI::printUserDetails(i+1);//print the cards
		}
		Sleep(600);
	}
}

//************************************
// Method:    decideWinners- find out who won the current round and give him  points
// FullName:  Game::decideWinners
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: int givenPoints- the number of points to be given to the winner
//************************************
void Game::decideWinners( int givenPoints/*=1*/ )
{
	Player* currWinner=m_players[0];
	Hand* currWinnerHand=currWinner->getHand();
	Player* next;
	Hand* nextPlayerHand;
	m_lastWinner = 0;

	for (unsigned int i=1; i<m_players.size(); i++)
	{
		next=m_players[i];
		nextPlayerHand=next->getHand();
		if (currWinnerHand->HandCmp(nextPlayerHand,m_winningRule)==THIS_IS_SMALLER)
		{
			currWinner=next;
			currWinnerHand=currWinner->getHand();
			m_lastWinner=i;
		}
	}
	givePointsToPlayer(givenPoints,currWinner);
}

//************************************
// Method:    returnNameOfWinningPlayer -returns the name of the player who won the current round
// FullName:  Game::returnNameOfWinningPlayer
// Access:    private 
// Returns:   const char *
// Qualifier:
//************************************
const char * Game::returnNameOfWinningPlayer()
{
	Player * currPlayer=m_players[0];
	Player * next;
	for(unsigned int i=1;i<m_numberOfplayers; i++)
	{
		next=m_players[i];
		if(next->getScore()>currPlayer->getScore())
		{
			currPlayer=next;
		}
	}
	return currPlayer->getName();
}