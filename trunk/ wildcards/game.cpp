//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Saturday 30/10/10
//Exercise: 2 Question:
//File name: game.cpp
#include "game.h"

Game::Game()
{
	initGame();
}

void Game::initGame()
{
	numberOfRounds=0;
	int shuffleDepth;
	ui=new UI();
	ui->plotWelcomeScreen();
	char* userName=NULL;
	gameDeck = new Deck(ui->getMainScreenUserInput(numberOfplayers,shuffleDepth,userName));
	gameDeck->shuffle(shuffleDepth);
	players.push_back(new Player(userName,false));
	delete []userName;
	char name[6]="comp";
	name[5]='\0';
	for (int i=1; i<numberOfplayers; i++)
	{
		name[4]='0'+i;
		players.push_back(new Player(name,true));
	}
	lastWinner=rand()%numberOfplayers;
}

Game::~Game()
{
	destroyGame();
}

void Game::destroyGame()
{
	delete ui;
	delete gameDeck;
	while (!players.empty())
	{
		delete players.front();
		players.pop_front();
	}
}

void Game::play()
{
	char userInput='c';
	ui->setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));
	while (userInput=='c')
	{
		newRound();
		ui->displayMessage("enter e to exit,c to continue or n for new game");
		userInput=ui->getUserGameInput();
		while(userInput!='e' && userInput!='c' && userInput!='n')//input isn't valid
		{
			ui->clearInputLine();
			ui->displayErrorMassage("ERROR:the input you entered is invalid: use c,n or e only!");
			userInput=ui->getUserGameInput();
			
		}
		ui->clearConsole();
		if (userInput=='n')
		{
			ui->plotGoodbyeScreen(numberOfRounds,returnNameOfWinningPlayer());
			destroyGame();  //Clear game settings
			initGame();		//initialize new game from user decisions
			play();			//Start anew
		}
		else if (userInput =='e')
		{
			ui->plotGoodbyeScreen(numberOfRounds,returnNameOfWinningPlayer());
			return;
		}
		ui->setPlayers(getPlayerAt(0),getPlayerAt(1),getPlayerAt(2),getPlayerAt(3));
	}
}



void Game::newRound()
{
	numberOfRounds++;
	Player* currPlayer;
	char userInput='0';
	drawCardsForAllUsers();
	ui->plotGameScreen(numberOfplayers);
	for (unsigned int i=0; i<players.size(); i++)
	{
		currPlayer=getPlayerAt(i);
		currPlayer->makeDecision(ui);
		ui->printPlayerDecision(i);
		if (currPlayer->getDecision()==Player::THROW)
		{
			returnCardForUser(i);
			drawCardForUser(i);
		}
		Sleep(1500);
	}
	decideWinners();
	ui->showAllCards();
	ui->clearConsole();
	for (int i=0; i<6; i++)
	{
		if (i%2==0)
		{
			ui->displayMessage("The winner is: ");
		}
		else
		{
			ui->displayMessage(getPlayerAt(0)->getName());
		}
		Sleep(500);
	}
	returnAllCardsToDeck();
}

Player * Game::getPlayerAt( unsigned int place )
{
	if (place>(players.size()-1))//no such place
	{
		return NULL;//todo- define as not found
	}
	else
	{
		return players[getUserPlace(place)];;
	}

}

void Game::drawCardsForAllUsers()
{

	for (unsigned int i=0; i<players.size(); i++)//each user takes a card
	{
		drawCardForUser(i);
	}
}

void Game::drawCardForUser(int userPlace)
{
	Player* currPlayer=getPlayerAt(userPlace);
	currPlayer->setCard(gameDeck->takeCard());;
	if (currPlayer->isHumanPlayer())
	{
		ui->printUserDetails(*(currPlayer->getCard()),userPlace+1);
	}
}

void Game::returnAllCardsToDeck()
{
	for (unsigned int i=0; i<players.size(); i++)//each user returns his card
	{
		returnCardForUser(i);
	}
}

void Game::returnCardForUser(int userPlace)
{
	gameDeck->insertCardToEnd(getPlayerAt(userPlace)->getCard());
	getPlayerAt(userPlace)->setCard(NULL);
}

void Game::decideWinners()
{
	Player * currWinner;
	Player * next;
	int numOfJokers=0;
	for (unsigned int i=0; i<players.size(); i++)
	{
		next=players[i];
		if (next->getCard()->getSuit()==Card::JOKER)
		{
			numOfJokers++;
			next->addToScore(1);
			lastWinner=i;
		} 
	}
	if (numOfJokers==0)//one winner
	{
		currWinner=players[0];
		lastWinner=0;
		for (unsigned int i=1; i<players.size(); i++)
		{
			next=players[i];
			if (gameDeck->compareCards(*(currWinner->getCard()) , *(next->getCard()))<0)
			{
				currWinner=next; //otherwise do nothing
				lastWinner=i;
			}
		}
		currWinner->addToScore(1);
	}
}

const char * Game::returnNameOfWinningPlayer()
{
	Player * currPlayer=players[0];
	Player * next;
	for(int i=1;i<numberOfplayers; i++)
	{
		next=players[i];
		if(next->getScore()>currPlayer->getScore())
		{
			currPlayer=next;
		}
	}
	return currPlayer->getName();
}