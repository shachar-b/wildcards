#ifndef ___GAMBLER___H____
	#define ___GAMBLER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "Player.h"
	//defines
	
	//consts
	//classes
	class Gambler:public Player
	{
	public:
		Gambler(const char * playerName,bool isComputer=true);
		~Gambler();
		void printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const;
		
	private:
		int m_money;
	};
	//function declaration
#endif