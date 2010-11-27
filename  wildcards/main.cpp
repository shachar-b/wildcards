#include "main.h"

void main()
{
	chooseGame();
}

void chooseGame()
{
	unsigned int userChoice;
	normalGame* gType1;
	GamblingGame* gType2;
	cout << "Please enter type of game, where:" << endl;
	cout << "\t1 - Normal game." << endl;
	cout << "\t2 - Gambling game." << endl<<endl;
	cout << "Enter your selection: ";

	cin >> userChoice;
	cin.ignore(cin.rdbuf()->in_avail());

	switch (userChoice)
	{
	case Normal:
		gType1=new normalGame();
		gType1->play();
		delete gType1;
		break;
	case Gambling:
		gType2=new GamblingGame();
		gType2->play();
		delete gType2;
		break;
	default:
		cout << "Invalid game type, quitting now!" << endl;
		break;
	}

}