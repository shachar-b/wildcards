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
		Gambler(const char * playerName,bool isComputer=true,int initMoney=1,int numOfJokers=2);
		~Gambler();
		void printPlayerDetails( int x,int y,bool showCard/*=true*/ ) const;
		int getBalance()const{return m_money;}
		int getCurrBet()const{return m_currBet;}
		void withdrawFromBalance(int withdrawal)
		{
			m_money-=withdrawal;
			if (m_money<0)
			{
				cout << "HELP!!!";
			}
		}//i assume withdrawal>=m_money
		void addToBalance(int deposit){m_money+=deposit;}//assuming deposit>0
		void makeBet();
		bool isBroke() const {return m_money==0;}//return true iff Balance is 0
		void playOrFold(int betToMatch);


		static const bool PLAY=true;
		static const bool FOLD=false;
		
	private:
		int m_money;
		int m_currBet;
	};
	//function declaration
#endif