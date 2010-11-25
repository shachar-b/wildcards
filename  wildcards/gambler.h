#ifndef ___GAMBLER___H____
	#define ___GAMBLER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "UI.h"
	using namespace UIs;
	#include "Player.h" 
	//defines
	
	//consts
	//classes
	class Gambler:public Player
	{
	public:
		Gambler(const char * playerName,bool isComputer=true,int initMoney=500);
		~Gambler();
		void printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const;
		bool makeDecision();
		int getBalance()const{return m_money;}
		void withdrawFromBalance(int withdrawal){ m_money-=withdrawal;}//i assume withdrawal>=m_money
		void addToBalance(int deposit){m_money+=deposit;}//assuming deposit>0 

		static const bool PLAY=true;
		static const bool FOLD=false;
		
	private:
		int m_money;
	};
	//function declaration
#endif