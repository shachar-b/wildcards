#include "main.h"

void main()
{
	chooseGame();
}

//************************************
// Method:    chooseGame - chooses a game from available game type
// FullName:  chooseGame
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void chooseGame()
{
	unsigned int userChoice;
	Game * game=NULL;
	cout << "Please enter type of game, where:" << endl;
	cout << "\t1 - Normal game." << endl;
	cout << "\t2 - Gambling game." << endl<<endl;
	cout << "Enter your selection: ";

	cin >> userChoice;
	cin.ignore(cin.rdbuf()->in_avail());

	switch (userChoice)
	{
	case Normal:
		game=new normalGame();
		break;
	case Gambling:
		game=new GamblingGame();
		break;
	default:
		cout << "Invalid game type, quitting now!" << endl;
		return;
	}
	game->play();
	delete game;

}