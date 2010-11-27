//student1:Name: Omer Shenhar	ID:038068953
//student2: Name: Shachar Butnaro ID:039339155
//Creation date:Thursday 18/11/10
//Exercise:  Question:
//File name: Player.h
#ifndef ___PLAYER___H____
	#define ___PLAYER___H____
	//includes
	#include <iostream> 
	using namespace std;
	#include "UI.h"
	using namespace UIs;
	#include <time.h>
	//defines
	
	//consts
	//classes
	class Player
	{
	private:
		bool m_isHuman;
		char * m_name;
		Card * m_card;
		bool m_decision;
		GameTypes m_playerType;
		


	public:
		static const bool KEEP=true;
		static const bool THROW=false;  
		Player(const char * playerName,bool iscomputer=true,GameTypes type=NORMAL);
		~Player(){delete m_name;}//release assigned space ()
		virtual bool makeDecision();
		virtual void printPlayerDetails(int x,int y,bool showCard=true) const;
		//setter and getters
		Card * getCard(){return m_card;}
		void setCard(Card * newCard){m_card=newCard;}
		const char * getName()const{return m_name;}
		bool isHumanPlayer()const{return m_isHuman;}
		bool getDecision(){return m_decision;}
		GameTypes getPlayerType()const{return m_playerType;}
		friend ostream& operator<<(ostream&out , const Player  * p);
		
	};
	//function declaration
#endif